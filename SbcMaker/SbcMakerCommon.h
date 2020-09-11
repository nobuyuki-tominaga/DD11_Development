#ifndef SBCMAKERCOMMON_H
#define SBCMAKERCOMMON_H

// プロジェクト内共通定義
#ifdef Q_OS_LINUX
#define SBC_DEFAULT_FILE_PATH	"~/"
#elif Q_OS_WIN32
#define SBC_DEFAULT_FILE_PATH	"c:\\"
#endif

#define SBC_F_FILE_NAME "%S_%d%dFront.%s"
#define SBC_B_FILE_NAME "%S_%d%dBack.%s"
#define SBC_VIEW_F_FILE_NAME "ImgViewFront.%s"
#define SBC_VIEW_B_FILE_NAME "ImgViewBack.%s"
#define SBC_PEM_FILE_NAME  "%s_key.pem"

#define SBC_PEM_FILE_PATH  "./.security/"
#define SBC_TMP_FILE_PATH  "./tmp/"
#define SBC_DATA_FILE_PATH "./.data/"

enum sbcFileType{
  fType_jpg = 0,
  fType_png,
  MAX_FILETYPE,
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
