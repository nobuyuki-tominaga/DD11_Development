#ifndef SBCMAKERCOMMON_H
#define SBCMAKERCOMMON_H

#include <QString>

// プロジェクト内共通定義
#ifdef Q_OS_LINUX
#define SBC_DEFAULT_FILE_PATH	"~/"
#elif Q_OS_WIN32
#define SBC_DEFAULT_FILE_PATH	"c:\\"
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

// FileType
enum sbcFileType{
  fType_jpg = 0,
  fType_png,
  MAX_FILETYPE,
};
// FileType Charactor
QString strExtension[] = {
  "jpg",
  "png",
  "jpg"
};

typedef struct {
  QString strName;
  QString strDept;
  QString strUnit;
  QString strTeam;
  QString strPosition;
  QString strMail;

  QString strEngName;
  QString strEngPosition;
} EMPLOYEE_INFO;

#endif // SBCMAKERCOMMON_H
