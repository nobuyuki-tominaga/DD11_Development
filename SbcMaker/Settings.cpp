#include <QDebug>
#include <QTextCodec>
#include "Settings.h"
#include "SbcMakerCommon.h"

CSettings::CSettings()
{
}

// INIファイル読み出し
void CSettings::loadIniFile()
{
    qDebug("load ini file");

    QSettings qset("sbc_settings.ini", QSettings::IniFormat);
    qset.setIniCodec(QTextCodec::codecForName("UTF-8"));

    m_employeeNum    = qset.value("employeeNum"   , ""                     ).toString();
    m_adminFlg       = qset.value("adminFlg"      , false                  ).toBool();
    m_saveDir        = qset.value("saveDir"       , SBC_DEFAULT_FILE_PATH()).toString();
    m_p12CertP12File = qset.value("p12CertP12File", ""                     ).toString();
    m_saveFmt        = qset.value("saveFmt"       , fType_jpg              ).toUInt();
    m_existenceFlg   = qset.value("existenceFlg"  , false                  ).toBool();
   qDebug("Status:%d", qset.status());
}

// INIファイル書き込み
void CSettings::saveIniFile()
{
    qDebug("save ini file");

    QSettings qset("sbc_settings.ini", QSettings::IniFormat);
    qset.setIniCodec(QTextCodec::codecForName("UTF-8"));

    qset.setValue("employeeNum"   , m_employeeNum);
    qset.setValue("adminFlg"      , m_adminFlg);
    qset.setValue("saveDir"       , m_saveDir);
    qset.setValue("p12CertP12File", m_p12CertP12File);
    qset.setValue("saveFmt"       , m_saveFmt);
    qset.setValue("existenceFlg"  , m_existenceFlg);
    qset.sync();
}

// 社員番号設定
void CSettings::setEmployeeNum(QString numStr)
{
    m_employeeNum = numStr;
}

// 社員番号取得
QString CSettings::getEmployeeNum()
{
    return m_employeeNum;
}

// 管理者権限設定
void CSettings::setAdminFilg(bool flg)
{
    m_adminFlg = flg;
}

// 管理者権限取得
bool CSettings::setAdminFilg()
{
    return m_adminFlg;
}

// 保存先設定
void CSettings::setSaveDir(QString DirPath)
{
    m_saveDir = DirPath;
}

// 保存先取得
QString CSettings::getSaveDir()
{
    return m_saveDir;
}

// 証明書ファイル設定
void CSettings::setCertP12File(QString filePath)
{
    m_p12CertP12File = filePath;
}

// 証明書ファイル取得
QString CSettings::getCertP12File()
{
    return m_p12CertP12File;
}

// 保存形式設定
void CSettings::setSaveImgFmt(uint fmtNum)
{
    m_saveFmt = fmtNum;
}

// 保存形式取得
uint CSettings::getSaveImgFmt()
{
    return m_saveFmt;
}

// pemファイルの有無設定
void CSettings::setExistenceFlg(bool flg)
{
    m_existenceFlg = flg;
}

// pemファイルの有無取得
bool CSettings::getExistenceFlg()
{
    return m_existenceFlg;
}
