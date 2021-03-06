#include <iostream>
#include <fstream>
#include <vector>
#include <iconv.h>
#include <stdlib.h>

#include <QString>
#include <QStringList>
#include <QDebug>
#include <QTextCodec>
#include <QFile>
#include <QTextStream>
#include <QImage>
#include <QDir>

#include "SbcMakerCommon.h"
#include "GetEmployeeInfo.h"

using namespace std;

#define POSITION	"cgi?post="
#define SECID       "sec_id="
#define SECID_SPLIT "\">"
#define SECID_END   "</a>"

#define MAIL_ADDR	"e=link&ml_to="
#define NAME1		"<td class=\"note\" colspan=\"2\">" //氏名・携帯番号用
#define NAME2       "<td class=\"note\" width=\"140\" colspan=\"2\">" //ローマ字用

#define URL_BASE    "https://inside.sobal.co.jp/antenna/property.cgi?target="
#define FACE_PICTURE "https://inside.sobal.co.jp/portrait/"

size_t onReceive(char* ptr, size_t size, size_t nmemb, QString* stream)
{
    int realsize = size * nmemb;
    QTextCodec *codec =QTextCodec::codecForName("EUC-JP");
    stream->append(codec->toUnicode(ptr));
    return realsize;
}

/*
 * Constructor
 */
CEmployeeInfo::CEmployeeInfo()
{
}

/*
 * Destructor
 */
CEmployeeInfo::~CEmployeeInfo()
{
}

QString CEmployeeInfo::searchHofficeInfo(QString dept)
{
    QString hoffice = Q_NULLPTR;
    QFile csv("./.data/Department.csv");
    csv.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&csv);
    in.setCodec(QTextCodec::codecForName("UTF-8"));
    while(!in.atEnd()){
        QString line = in.readLine();
        QStringList list = line.split(",");
        if(list[0].compare(dept) == 0){
            if(list[1].compare("なし") == 0){
                hoffice = "";
            }
            else {
                hoffice = list[1];
            }
            qDebug("%s  %s", qPrintable(hoffice), qPrintable(list[0]));
            break;
        }
    }
    csv.close();
    return hoffice;
}

QString CEmployeeInfo::setEngPositionInfo(QString position)
{
    QString engPosition = Q_NULLPTR;
    QFile csv("./.data/position.csv");
    csv.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&csv);
    in.setCodec(QTextCodec::codecForName("UTF-8"));
    while(!in.atEnd()){
        QString line = in.readLine();
        QStringList list = line.split(",");
        if(list[0].compare(position) == 0){
            if(list[1].compare("なし") == 0){
                engPosition = "";
            }
            else {
                engPosition = list[1];
            }
            qDebug("%s  %s", qPrintable(engPosition), qPrintable(list[0]));
            break;
        }
    }
    csv.close();
    return engPosition;
}

/*
 * Main Process
 */
int CEmployeeInfo::getEmployeeInfo(EMPLOYEE_INFO *info, QString EmployeeNo)
{
    CURL     *curl;
    CURLcode res;
    QString  url = QString(URL_BASE) + EmployeeNo;
    QString  pem = QString(SBC_PEM_FILE_PATH) + EmployeeNo + QString(SBC_PEM_FILE);
    QString chunk;  // レスポンスデータの格納先

    curl = curl_easy_init();

    //CURL設定
    curl_easy_setopt(curl, CURLOPT_BUFFERSIZE, 102400L);
    curl_easy_setopt(curl, CURLOPT_URL, url.toStdString().c_str());
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.68.0");
    curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
    curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, (long)CURL_HTTP_VERSION_2TLS);
    curl_easy_setopt(curl, CURLOPT_SSLCERT, pem.toStdString().c_str());
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
    // レスポンスのコールバック
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, onReceive);
    // 書き込みバッファを指定
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (QString*)&chunk);

	// cURL リクエスト実行
    res = curl_easy_perform(curl);

    // リクエスト処理 OK 時
    if (res == CURLE_OK) {
        QList<QString>  strList = chunk.split("\n");
        // イテレータの取得
        QList<QString>::const_iterator i;
        QString line;
        QString body;
        int start_pos, end_pos, len, tmp;
        int name = 0, engname = 0, mobile = 0;
        int next_name = 0, next_engname = 0, next_mobile = 0;
        int mobile_cnt = 0;
        for (i = strList.begin(); i != strList.end(); ++i){
            line = *i;
            line.replace( "\t", "" );   //TABを削除

            //職位を抽出する
 #if 0
            QRegExp r2("cgi\?post=.*>(.*)</a>");
            if(r2.indexIn(line) > 0){
                QStringList l = r2.capturedTexts();
                info->strPosition = l[1];
            }
#else
            if((start_pos = line.indexOf(POSITION)) >= 0){
                if((tmp = line.indexOf(SECID_SPLIT)) >= 0){
                    start_pos = tmp + strlen(SECID_SPLIT);
                    end_pos = line.indexOf(SECID_END);
                    len = end_pos - start_pos;
                    body = line.mid(start_pos, len);
                    info->strPosition = body;
                }
            }
#endif
            //部・ユニット名・チーム名を抽出する
            QRegExp r("sec_id=.*>(.*)</a>");
            if(r.indexIn(line) > 0){
                QStringList l = r.capturedTexts();
                if((l[1].indexOf("部")) >= 0){
                    info->strDept = l[1];
                }else if((l[1].indexOf("ユニット")) >= 0){
                    info->strUnit = l[1];
                }else if((l[1].indexOf("チーム")) >= 0){
                    info->strTeam = l[1];
                }
            }

            //メールアドレスを抽出する
            if((start_pos = line.indexOf(MAIL_ADDR)) >= 0){
                end_pos = line.indexOf(SECID_SPLIT);
                len = strlen(MAIL_ADDR);
                body = line.mid(start_pos+len, end_pos-(start_pos+len));
                info->strMail = body;
            }

            //氏名・ローマ字・携帯番号を検索する
            if(line.indexOf("氏名") >= 0){
                name = 1;
            }else if(line.indexOf("ローマ字") >= 0){
                engname = 1;
            }else if(line.indexOf("携帯番号（会社）") >= 0){
                mobile = 1;
            }

            //氏名・ローマ字・携帯番号を抽出する
            if(next_name != 0){
                name = 0;
                next_name = 0;
                // 文字の間に半角スペースを追加する
                int loop;
                int loopend = ( line.length() - 1 ) * 2;
                for(loop = 0; loop < loopend; loop+=2){
                    line.insert(loop+1," ");
                }
                info->strName = line;
            }else if(next_engname != 0){
                engname = 0;
                next_engname = 0;

                //姓と名を分離して、入れ替える
                {
                    QString name1;
                    QString name2;
                    int sp_pos;
                    int size = strlen(line.toStdString().c_str());

                    if((sp_pos = line.indexOf(" ")) >= 0){
                        name1 = line.mid(0, sp_pos);
                        name2 = line.mid(sp_pos+1, size);
                        info->strEngName = name2 + " " + name1;
                    }
                }
            }else if(next_mobile != 0){
                //一行空行が入る対応が必要
                mobile_cnt++;
                if(mobile_cnt > 1){
                    mobile = 0;
                    next_mobile = 0;
                    if(line.indexOf("--") < 0){
                        info->strMobile = line;
                        info->strEngMobile = line.replace(0, 1, "+81-");
                    }else{
                        //携帯番号が--の場合
                        info->strMobile = "";
                        info->strEngMobile = "";
                    }
                }
            }

            //氏名・ローマ字・携帯番号の2次検索
            if((start_pos = line.indexOf(NAME1)) >= 0){
                if(name != 0){
                   next_name = 1;
                }else if(mobile != 0){
                    next_mobile = 1;
                }
            }else if((start_pos = line.indexOf(NAME2)) >= 0){
                if(engname != 0){
                   next_engname = 1;
                }
            }
        }

        //本部を設定する
        info->strHoffice = searchHofficeInfo(info->strDept);

        //英語名の役職を設定する
        info->strEngPosition = setEngPositionInfo(info->strPosition);

        //顔写真ファイルを格納するフォルダ(tmp)を作成する
        QString basedir = "./";
        QDir dir(basedir);
        if(!dir.exists(QString(SBC_TMP_FILE_PATH))){
            dir.mkdir(QString(SBC_TMP_FILE_PATH));
        }

        // Clean up
        curl_easy_cleanup(curl);

        //写真のダウンロード
        QString strPicture = QString(FACE_PICTURE) + EmployeeNo + ".gif";
        QString strFileName = SBC_TMP_FILE_PATH + EmployeeNo + ".gif";
        qDebug("%s", strPicture.toStdString().c_str());

        FILE *fp = fopen(strFileName.toStdString().c_str(), "wb");

        curl = curl_easy_init();
        curl_easy_setopt(curl,CURLOPT_URL, strPicture.toStdString().c_str());

        curl_easy_setopt(curl, CURLOPT_SSLCERT, pem.toStdString().c_str());
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);

        long http_code=0;
        curl_easy_getinfo(curl,CURLINFO_RESPONSE_CODE, &http_code);

        fclose(fp);

        // Clean up
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            return FAILURE;
        }

        return SUCCESS;
    }else{
        return FAILURE;
    }
}
