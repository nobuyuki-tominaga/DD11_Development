#include <iostream>
#include <fstream>
#include <vector>
#include <iconv.h>
#include <stdlib.h>

#include <QString>
#include <QStringList>
#include <QDebug>

#include "SbcMakerCommon.h"
#include "GetEmployeeInfo.h"

using namespace std;

#define POSITION	"post=30\">"
#define DPT         "sec_id=984\">"
#define UNIT		"sec_id=994\">" 
#define TEAM		"sec_id=1003\">" 
#define MAIL_ADDR	"e=link&ml_to="
//#define NAME1		"<td class=\"note\" colspan=\"2\">"
#define NAME1		"<h2>"
#define NAME2		"<td class=\"note\" width=\"140\" colspan=\"2\">"

#define URL_BASE    "https://inside.sobal.co.jp/antenna/property.cgi?target="
//#define PEM_FILE    "./.security/204046_key.pem"

size_t onReceive(char* ptr, size_t size, size_t nmemb, QString* stream)
{
    int realsize = size * nmemb;
    stream->append(ptr);
    return realsize;
}

/*
 * Constructor
 */
CEmployeeInfo::CEmployeeInfo()
{
	// CURL Initial
	curl = curl_easy_init();
}

/*
 * Destructor
 */
CEmployeeInfo::~CEmployeeInfo()
{
    // Clean up
    curl_easy_cleanup(curl);
}

/*
 * Main Process
 */
int CEmployeeInfo::getEmployeeInfo(EMPLOYEE_INFO *info, QString EmployeeNo)
{
    QString url = QString(URL_BASE) + EmployeeNo;
    QString pem = QString(SBC_PEM_FILE_PATH) + EmployeeNo + QString(SBC_PEM_FILE);

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
        int start_pos, end_pos, len;
        for (i = strList.begin(); i != strList.end(); ++i){
            line = *i;
            //職位を抽出する
            if((start_pos = line.indexOf(POSITION)) >= 0){
                end_pos = line.indexOf("</a>");
                len = strlen(POSITION);
                body = line.mid(start_pos+len, end_pos-(start_pos+len));
                info->strPosition = body;
                //qDebug("position:%s", body.toStdString().c_str());
            }

            //部を抽出する
            if((start_pos = line.indexOf(DPT)) >= 0){
                end_pos = line.indexOf("</a>");
                len = strlen(DPT);
                body = line.mid(start_pos+len, end_pos-(start_pos+len));
                info->strDept = body;
                //qDebug("Dept:%s", body.toStdString().c_str());
            }

            //ユニットを抽出する
            if((start_pos = line.indexOf(UNIT)) >= 0){
                end_pos = line.indexOf("</a>");
                len = strlen(UNIT);
                body = line.mid(start_pos+len, end_pos-(start_pos+len));
                info->strUnit = body;
                //qDebug("Unit:%s", body.toStdString().c_str());
            }

            //チームを抽出する
            if((start_pos = line.indexOf(TEAM)) >= 0){
                if(line.indexOf("<img border=") < 0){
                    end_pos = line.indexOf("</a>");
                    len = strlen(TEAM);
                    body = line.mid(start_pos+len, end_pos-(start_pos+len));
                    info->strTeam = body;
                    //qDebug("team:%s", body.toStdString().c_str());
                }
            }

            //メールアドレスを抽出する
            if((start_pos = line.indexOf(MAIL_ADDR)) >= 0){
                end_pos = line.indexOf("\">");
                len = strlen(MAIL_ADDR);
                body = line.mid(start_pos+len, end_pos-(start_pos+len));
                info->strMail = body;
                qDebug("mail:%s", body.toStdString().c_str());
            }

#if 0
            //氏名を抽出する
            if((start_pos = line.indexOf(NAME1)) >= 0){
                end_pos = line.indexOf("さん");
                len = strlen(NAME1);
                body = line.mid(start_pos+len, end_pos-(start_pos+len));
                qDebug("氏名:%s", body.toStdString().c_str());
            }

            //氏名を抽出する
            if((start_pos = line.indexOf(NAME2)) >= 0){
                if(shimei == 1)
                   next_shimei = 1;
                else if(romaji == 1)
                   next_romaji = 1;
            }

            if(line.indexOf("氏名") >= 0){
                shimei = 1;
                qDebug("氏名を発見\n");
            }

            if(line.indexOf("ローマ字") >= 0){
                romaji = 1;
                qDebug("ローマ字を発見\n");
            }
#endif
        }
        return SUCCESS;
    }else{
        return FAILURE;
    }
}
