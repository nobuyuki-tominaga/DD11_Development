#include <QPainter>
#include <QImage>
#include <QString>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include "SbcMakerCommon.h"
#include "imgmaker.h"

QString strFileType[MAX_FILETYPE] = {
  "jpg",
  "png",
};
static void _getEmployeeInfo(EMPLOYEE_INFO *info); //社員情報取得　動作確認用

ImgMaker::ImgMaker()
{
}

ImgMaker::~ImgMaker()
{
}

static void _getEmployeeInfo(EMPLOYEE_INFO *info) //社員情報取得　動作確認用
{
    info->strName = "ソーバル 太郎";
    info->strHoffice = "システム本部";
    info->strDept = "デジタルプロダクト部";
    info->strUnit = "****ユニット";
    info->strTeam = "****チーム";
    info->strPosition = "役職";
    info->strMail = "taro_sobal@sobal.co.jp";
    info->strMobile = "080-****-****";

    info->strEngName = "Taro Sobal";
    info->strEngPosition = "Position";
    info->strEngMobile = "+81-80-****-****";
}

int ImgMaker::createGraphic(QGraphicsScene *scene, QString strEmpNum, int Side, bool fSave, QString strFilePath)
{
    // debug
    EMPLOYEE_INFO info;
    _getEmployeeInfo(&info);
#if 0
    _createBcard(&info, Side);
#else
    if (Side == sides_front) {
        createBcardFront(&info);
    }
    else {
        createBcardBack(&info);
    }
#endif
    getPhotoComposition();

    if (fSave == true) {
        // 本画像保存処理
    }

    // image
    QString strViewPath = SBC_TMP_FILE_PATH;
    if (Side == sides_front) {
        strViewPath += SBC_VIEW_F_FILE;
    }
    else {
        strViewPath += SBC_VIEW_B_FILE;
    }

    QImage image(strViewPath);
    QGraphicsPixmapItem *image_item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    scene->addItem(image_item);

    return SUCCESS;
}
#if 0
QGraphicsScene ImgMaker::previewImgMaker(QGraphicsScene Scene1, QGraphicsScene Scene2) //プレビュー表示
{
    EMPLOYEE_INFO info;
    _getEmployeeInfo(&info);
    createBcardFront(&info);
    //createBcardBack(&info);
    getPhotoComposition();
    QImage *image1 = new QImage();
    QImage *image2 = new QImage();
    image1->load( "./tmp/");
    image2->load( "./tmp/");
    //graphicsViewにSceneを設定。
    //ui->FrontGraphicsView->setScene(&Scene1);
    //ui->BackGraphicsView->setScene(&Scene2);
    //Scene_をクリア
     Scene1.clear();
     Scene2.clear();
     //Scene_に登録するpixmapを作成
     QPixmap pmap1=QPixmap::fromImage(*image1);
     QPixmap pmap2=QPixmap::fromImage(*image2);
     //Scene_に画像を登録
     Scene1.addPixmap(pmap1);
     Scene2.addPixmap(pmap2);

     //画像をリサイズ
     //ui->FrontGraphicsView->fitInView(Scene1.itemsBoundingRect(),Qt::KeepAspectRatio);
     //ui->BackGraphicsView->fitInView(Scene2.itemsBoundingRect(),Qt::KeepAspectRatio);
}
#endif

void ImgMaker::createBcardFront(EMPLOYEE_INFO *info)  //名刺表面作成
{
    QString strViewPath = SBC_TMP_FILE_PATH;
    QString strDataPath = SBC_DATA_FILE_PATH;

    QImage *image = new QImage();
    // debug
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
    painter.drawText(475,593, "携帯 " + info->strMobile); //座標は左下

    strViewPath += SBC_VIEW_F_FILE;
    image->save(strViewPath);
}

void ImgMaker::createBcardBack(EMPLOYEE_INFO *info) //名刺裏面作成
{
    QString strViewPath = SBC_TMP_FILE_PATH;
    QString strDataPath = SBC_DATA_FILE_PATH;

    QImage *image = new QImage();
    // debug
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
