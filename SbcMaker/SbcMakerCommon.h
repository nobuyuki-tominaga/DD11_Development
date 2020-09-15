#ifndef SBCMAKERCOMMON_H
#define SBCMAKERCOMMON_H

#include <QString>

// プロジェクト内共通定義
#if defined (Q_OS_LINUX)
  #define SBC_DEFAULT_FILE_PATH() (qgetenv("HOME").constData())
#elif defined (Q_OS_WIN32)
  #define SBC_DEFAULT_FILE_PATH() (qgetenv("HOMEPATH").constData())
#endif

#define SBC_F_FILE      "Front."        // 社員番号_日付Front.拡張子
#define SBC_B_FILE      "Back."         // 社員番号_日付Back.拡張子
#define SBC_VIEW_F_FILE "ImgViewFront." // ImgViewFront.拡張子
#define SBC_VIEW_B_FILE "ImgViewBack."  // ImgViewBack.拡張子
#define SBC_PEM_FILE    "_key.pem"      // 社員番号_key.pem

// pem置き場
#define SBC_PEM_FILE_PATH  "./.security/"

// ViewFile、その他一時ファイル置き場
#define SBC_TMP_FILE_PATH  "./tmp/"

// 必要なデータ画像置き場
#define SBC_DATA_FILE_PATH "./.data/"

// Error
enum sbcErrorType {
  SUCCESS = 0,
  FAILURE = 1,
};

// FileType
enum sbcFileType{
  fType_jpg = 0,
  fType_png,
  MAX_FILETYPE,
};
#if 0
// FileType Charactor
QString strExtension[] = {
  "jpg",
  "png",
  "jpg"
};
#endif

typedef struct {
  QString strName;    // 氏名
  QString strHoffice; // 部門（システム本部、管理本部...）
  QString strDept;    // 部
  QString strUnit;    // 所属ユニット
  QString strTeam;    // 所属チーム
  QString strPosition;// 職位
  QString strMail;    // メールアドレス
  QString strMobile;  // 携帯番号

  QString strEngName;     // 氏名（英）
  QString strEngPosition; // 職位（英）
} EMPLOYEE_INFO;

#endif // SBCMAKERCOMMON_H
