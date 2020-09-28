#include <stdio.h>
#include <stdlib.h>
#include <QString>
#include <QDebug>
#include <QDir>

#include "SbcMakerCommon.h"
#include "MakePemFile.h"

using namespace std;         //  名前空間指定

/*
 * Constructor
 */
CPemMaker::CPemMaker()
{
}

/*
 * Destructor
 */
CPemMaker::~CPemMaker()
{
}

/*
 * Main Process
 */
int CPemMaker::makePemFile(const QString p12Path, const QString passwd, QString *number)
{
    int i;
    int pos1=0, pos2=0;
    QString no; //社員番号
    //QString pemFileName = "./.security/204046_key.pem";
    QString pemFileName;

    //社員番号を抽出する
    if((pos1 = p12Path.lastIndexOf("/")) > 0){
        if((pos2 = p12Path.indexOf(".p12")) > 0){
            no = p12Path.mid(pos1+1, pos2-pos1-1);
            *number = no;
            qDebug("no:%s", no.toStdString().c_str());
        }
    }

    if ((fp = fopen(p12Path.toStdString().c_str(), "rb")) == Q_NULLPTR) {
        fprintf(stderr, "nullptr .p12\n");
        return FAILURE;
    }

    p12 = d2i_PKCS12_fp(fp, Q_NULLPTR);
    fclose(fp);

    if (p12 == Q_NULLPTR) {
        fprintf(stderr, "Error reading PKCS#12 file\n");
        ERR_print_errors_fp(stderr);
        return FAILURE;
    }

    if (!PKCS12_parse(p12, passwd.toStdString().c_str(), &pkey, &cert, &ca)) {
        fprintf(stderr, "Error parsing PKCS#12 file\n");
        ERR_print_errors_fp(stderr);
        return FAILURE;
    }

    //pemファイルを格納するフォルダ(.security)を作成する
    QString basedir = "./";
    QDir dir(basedir);
    if(!dir.exists(QString(SBC_PEM_FILE_PATH))){
        dir.mkdir(QString(SBC_PEM_FILE_PATH));
    }

    //pemファイルの名前を生成する
    pemFileName = QString(SBC_PEM_FILE_PATH) + no + QString(SBC_PEM_FILE);
    qDebug("pemFileName:%s", pemFileName.toStdString().c_str());

    PKCS12_free(p12);
    if ((fp = fopen(pemFileName.toStdString().c_str(), "w+")) == Q_NULLPTR) {
        fprintf(stderr, "nullptr.pem\n");
        return FAILURE;
    }

    if (pkey != Q_NULLPTR) {
        fprintf(fp, "***Private Key***\n");
        PEM_write_PrivateKey(fp, pkey, Q_NULLPTR, Q_NULLPTR, 0, Q_NULLPTR, Q_NULLPTR);
    }

    if (cert != Q_NULLPTR) {
        fprintf(fp, "***User Certificate***\n");
        PEM_write_X509_AUX(fp, cert);
    }

    if (ca != Q_NULLPTR && sk_X509_num(ca) > 0) {
        fprintf(fp, "***Other Certificates***\n");
        for (i = 0; i < sk_X509_num(ca); i++)
            PEM_write_X509_AUX(fp, sk_X509_value(ca, i));
    }

    fclose(fp);
    return SUCCESS;
}
