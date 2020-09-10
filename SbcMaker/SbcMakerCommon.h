#ifndef SBCMAKERCOMMON_H
#define SBCMAKERCOMMON_H

// プロジェクト内共通定義
#define SBC_VIEW_FILE_NAME "ImgView.%s"
#define SBC_PEM_FILE_NAME  "%s_key.pem"

#define SBC_PEM_FILE_PATH  "./.security/"
#define SBC_TMP_FILE_PATH  "./tmp/"
#define SBC_DATA_FILE_PATH "./.data/"

enum sbc_filetype{
  jpg = 0,
  png,
  MAX_FILETYPE,
};

typedef struct {
  //unsigned int nNumber;
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
