﻿//#include <QMessageBox>
//#include <QTranslator>
//#include <QLibraryInfo>

#include <QPainter>
#include <QImage>
//#include <QtGui>
#include <QString>
#include <QGraphicsScene>
//#include <QGraphicsView>
//#include <QDebug>

#include "SbcMakerCommon.h"
#include "imgmaker.h"

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

int ImgMaker::graphicCreate(QGraphicsScene *Scene, QString strEmpNum, int Side, bool fSave, QString strFilePath)
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
    QImage *image = new QImage();
    image->load( "./tmp/");

    // graphicsViewにSceneを設定。
    // SCene設定はMainWindowで行ってもらう
    //ui->FrontGraphicsView->setScene(&Scene1);
    //ui->BackGraphicsView->setScene(&Scene2);

    //Scene_をクリア
    Scene->clear();

    //Scene_に登録するpixmapを作成
    QPixmap pmap = QPixmap::fromImage(*image);
    //Scene_に画像を登録
    Scene->addPixmap(pmap);

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
    QImage *image = new QImage();
    image->load( "./.data/omote.jpg");
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
    image->save("./tmp/output.jpg");
}

void ImgMaker::createBcardBack(EMPLOYEE_INFO *info) //名刺裏面作成
{
    QImage *image = new QImage();
    image->load( "./.data/omote.jpg");
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
    image->save("./tmp/output.jpg");
}
void ImgMaker::getPhotoComposition() //名刺表面に顔写真を貼り付け
{
    QImage *image = new QImage();
    image->load( "./tmp/");
    QPainter painter(image);

    painter.drawImage(55, 220, QImage("./.data/")); //gifファイル
    image->save("./tmp/");
}
