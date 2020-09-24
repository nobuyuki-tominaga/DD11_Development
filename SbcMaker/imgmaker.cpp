#include <QPainter>
#include <QImage>
#include <QString>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QDateTime>
#include <QFile>

#include "SbcMakerCommon.h"
#include "GetEmployeeInfo.h"
#include "imgmaker.h"


QString strFileType[MAX_FILETYPE] = {
  "jpg",
  "png",
};


ImgMaker::ImgMaker()
{
}

ImgMaker::~ImgMaker()
{
}

int ImgMaker::createGraphic(QString strEmpNum, int fileType, bool fSave, QString strFilePath)
{
    EMPLOYEE_INFO info;
    CEmployeeInfo ins;

    if (ins.getEmployeeInfo(&info, strEmpNum) != SUCCESS) {
        return FAILURE;
    }

    createBcardFront(&info);
    createBcardBack(&info);
    getPhotoComposition();

    if (fSave == true) {
        // 本画像保存処理
        //日付取得
        QDateTime tm = QDateTime().currentDateTime();
        QString now = tm.toString("yyyyMMdd");

        //名刺表面を保存
        QString f_strViewPath = SBC_TMP_FILE_PATH;
        f_strViewPath += SBC_VIEW_F_FILE;
        QImage *save_f_image = new QImage();
        save_f_image->load(f_strViewPath);
        QString f_strFilePath = strFilePath;
        f_strFilePath += "/" + strEmpNum + "_" + now + SBC_F_FILE + strFileType[fileType];
        save_f_image->save(f_strFilePath);
        //名刺裏面を保存
        QString b_strViewPath = SBC_TMP_FILE_PATH;
        b_strViewPath += SBC_VIEW_B_FILE;
        QImage *save_b_image = new QImage();
        save_b_image->load(b_strViewPath);
        QString b_strFilePath = strFilePath;
        b_strFilePath += "/" + strEmpNum + "_" + now + SBC_B_FILE + strFileType[fileType];
        save_b_image->save(b_strFilePath);
    }

    return SUCCESS;
}

int ImgMaker::genViewGraphic(QGraphicsScene *scene, int Side)
{
    // image
    QString strViewPath = SBC_TMP_FILE_PATH;
    if (Side == sides_front) {
        strViewPath += SBC_VIEW_F_FILE;
    }
    else {
        strViewPath += SBC_VIEW_B_FILE;
    }

    if (!QFile::exists(strViewPath)) {
        strViewPath  = SBC_DATA_FILE_PATH;
        if (Side == sides_front) {
            strViewPath += "sample_front.jpg";
        }
        else {
            strViewPath += "sample_back.jpg";
        }
    }

    QImage image(strViewPath);
    QGraphicsPixmapItem *image_item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    scene->addItem(image_item);

    return SUCCESS;
}

void ImgMaker::createBcardFront(EMPLOYEE_INFO *info)  //名刺表面作成
{
    QString strViewPath = SBC_TMP_FILE_PATH;
    QString strDataPath = SBC_DATA_FILE_PATH;

    QImage *image = new QImage();

    strDataPath += "front.jpg";
    image->load(strDataPath);
    QPainter painter(image);

    painter.setPen(QPen(Qt::black));
    painter.setFont(QFont("MS UI Gothic", 6));
    painter.drawText(250,155, info->strHoffice); //座標は左下
    painter.drawText(250,185, info->strDept); //座標は左下
    painter.drawText(250,215, info->strUnit); //座標は左下
    painter.drawText(250,245, info->strTeam); //座標は左下
    painter.setFont(QFont("MS UI Gothic", 6));
    painter.drawText(250,320, info->strPosition); //座標は左下
    painter.setFont(QFont("MS UI Gothic", 11));
    painter.drawText(250,370, info->strName); //座標は左下
    painter.setFont(QFont("MS UI Gothic", 6));
    painter.drawText(330,390,700,35, Qt::AlignRight, info->strMail);//右端に合わせる
    painter.setFont(QFont("MS UI Gothic", 5, QFont::Bold));
    painter.drawText(475,593, "Mobile " + info->strMobile); //座標は左下

    strViewPath += SBC_VIEW_F_FILE;
    image->save(strViewPath);
}

void ImgMaker::createBcardBack(EMPLOYEE_INFO *info) //名刺裏面作成
{
    QString strViewPath = SBC_TMP_FILE_PATH;
    QString strDataPath = SBC_DATA_FILE_PATH;

    QImage *image = new QImage();
    strDataPath += "back.jpg";
    image->load(strDataPath);
    QPainter painter(image);

    painter.setPen(QPen(Qt::black));
    painter.setFont(QFont("MS UI Gothic", 6));
    painter.drawText(250,320, info->strEngPosition); //座標は左下
    painter.setFont(QFont("MS UI Gothic", 11));
    painter.drawText(250,370, info->strEngName); //座標は左下
    painter.setFont(QFont("MS UI Gothic", 6));
    painter.drawText(330,390,700,35, Qt::AlignRight,info->strMail);//右端に合わせる
    painter.setFont(QFont("MS UI Gothic", 6));
    painter.drawText(500,585, "Mobile " + info->strEngMobile); //座標は左下

    strViewPath += SBC_VIEW_B_FILE;
    image->save(strViewPath);
}
void ImgMaker::getPhotoComposition() //名刺表面に顔写真を貼り付け
{
    QImage *image = new QImage();
    QString strViewPath = SBC_TMP_FILE_PATH;
    strViewPath += SBC_VIEW_F_FILE;

    image->load(strViewPath);
    QPainter painter(image);

    QString strDataPath = SBC_DATA_FILE_PATH;
    strDataPath += "face.gif";
    painter.drawImage(55, 220, QImage(strDataPath)); //gifファイル
    image->save(strViewPath);
}
