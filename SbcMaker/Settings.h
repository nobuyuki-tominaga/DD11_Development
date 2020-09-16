#ifndef CSETTINGS_H
#define CSETTINGS_H


#include <QSettings>
#include <QString>

class CSettings
{
private:
    QString m_employeeNum;    // 社員番号
    bool    m_adminFlg;       // 管理者権限フラグ
    QString m_saveDir;        // 保存先
    QString m_p12CertP12File; // 証明書ファイル
    uint    m_saveFmt;        // 保存形式
    bool    m_existenceFlg;   // pemファイルの有無

public:
    CSettings();

    // INIファイル読み出し
    void loadIniFile();
    // INIファイル書き込み
    void saveIniFile();

    // 社員番号設定
    void setEmployeeNum(QString numStr);
    // 社員番号取得
    QString getEmployeeNum();
    // 管理者権限設定
    void setAdminFilg(bool flg);
    // 管理者権限取得
    bool setAdminFilg();
    // 保存先設定
    void setSaveDir(QString DirPath);
    // 保存先取得
    QString getSaveDir();
    // 証明書ファイル設定
    void setCertP12File(QString filePath);
    // 証明書ファイル取得
    QString getCertP12File();
    // 保存形式設定
    void setSaveImgFmt(uint fmtNum);
    // 保存形式取得
    unsigned int getSaveImgFmt();
    // pemファイルの有無設定
    void setExistenceFlg(bool flg);
    // pemファイルの有無取得
    bool getExistenceFlg();
};

#endif // CSETTINGS_H
