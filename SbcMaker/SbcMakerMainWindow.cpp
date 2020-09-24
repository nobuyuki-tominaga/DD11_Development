#include <QDebug>
#include <QMessageBox>
#include <QTranslator>
#include <QLibraryInfo>
#include "SbcMakerCommon.h"
#include "SbcMakerMainWindow.h"
#include "ui_SbcMakerMainWindow.h"
#include "OptionSettingDialog.h"

#include <QGraphicsScene>

#include "imgmaker.h"

CSbcMakerMain::CSbcMakerMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CSbcMakerMain)
{
    ui->setupUi(this);
    sbcSettings.loadIniFile();

    if(sbcSettings.getAdminFlg() == true){
        // 「社員番号入力欄」を入力可
      ui->employeeNumLineEdit->setDisabled(false);
    }
    else{
        // 「社員番号入力欄」を入力不可
      ui->employeeNumLineEdit->setDisabled(true);
    }

    if(sbcSettings.getExistenceFlg() == true){
        // 「プレビュー」ボタンをグレーアウト(押下可)
        ui->previewPushButton->setDisabled(false);
        // 「作成」ボタンをグレーアウト(押下可)
        ui->imgGenPushButton->setDisabled(false);
    }
    else{
        // 「プレビュー」ボタンをグレーアウト(押下不可)
        ui->previewPushButton->setDisabled(true);
        // 「作成」ボタンをグレーアウト(押下不可)
        ui->imgGenPushButton->setDisabled(true);
    }
    ui->employeeNumLineEdit->setText(sbcSettings.getEmployeeNum());

    // 未実装
    //+++++++++++++++++++++
    // 名刺画像描画処理
    // 作成済みのが画像がある場合はその画像(表)を表示
    // ない場合はサンプリ画像(表)を表示
    //+++++++++++++++++++++

}

CSbcMakerMain::~CSbcMakerMain()
{
    delete ui;
}

void CSbcMakerMain::on_settingPushButton_clicked()
{
    QTranslator translator;
    translator.load("qt_ja_JP", QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    qApp->installTranslator(&translator);
    // 設定画面をモーダルダイアログとして表示
    COptionSetting setWindow(this, &sbcSettings);
    setWindow.exec(); // ダイアログが閉じるまで待機
    if(sbcSettings.getExistenceFlg() == true){
        // 「プレビュー」ボタンをグレーアウト(押下可)
        ui->previewPushButton->setDisabled(false);
        // 「作成」ボタンをグレーアウト(押下可)
        ui->imgGenPushButton->setDisabled(false);
    }
    else{
        // 「プレビュー」ボタンをグレーアウト(押下不可)
        ui->previewPushButton->setDisabled(true);
        // 「作成」ボタンをグレーアウト(押下不可)
        ui->imgGenPushButton->setDisabled(true);
    }
    ui->employeeNumLineEdit->setText(sbcSettings.getEmployeeNum());
}

void CSbcMakerMain::on_previewPushButton_clicked()
{
    QString strEmpNum = sbcSettings.getEmployeeNum();
    QString strFilePath = sbcSettings.getSaveDir();

    ImgMaker *cImg = new(ImgMaker);
    cImg->createGraphic(&m_scene, strEmpNum, sides_front, false, strFilePath);

    ui->FrontGraphicsView->setScene(&m_scene);
    ui->FrontGraphicsView->fitInView(m_scene.itemsBoundingRect(),Qt::KeepAspectRatio);
}

void CSbcMakerMain::on_imgGenPushButton_clicked()
{
    QString strEmpNum = sbcSettings.getEmployeeNum();
    QString strFilePath = sbcSettings.getSaveDir();

    ImgMaker *cImg = new(ImgMaker);
    cImg->createGraphic(&m_scene, strEmpNum, sides_front, true, strFilePath);

    ui->FrontGraphicsView->setScene(&m_scene);
    ui->FrontGraphicsView->fitInView(m_scene.itemsBoundingRect(),Qt::KeepAspectRatio);
}

void CSbcMakerMain::on_finishPushButton_clicked()
{
    this->close();
}

void CSbcMakerMain::on_viewTabWidget_tabBarClicked(int index)
{
    qDebug("Active Tab Number : %d", index);
    QString strEmpNum = sbcSettings.getEmployeeNum();
    QString strFilePath = sbcSettings.getSaveDir();

    //表面
    if(index == 0){
        ImgMaker *cImg = new(ImgMaker);
        cImg->createGraphic(&m_scene, strEmpNum, sides_front, false, strFilePath);

        ui->FrontGraphicsView->setScene(&m_scene);
        ui->FrontGraphicsView->fitInView(m_scene.itemsBoundingRect(),Qt::KeepAspectRatio);

    }
    //裏面
    else{
        ImgMaker *cImg = new(ImgMaker);
        cImg->createGraphic(&m_scene, strEmpNum, sides_back, false, strFilePath);

        ui->BackGraphicsView->setScene(&m_scene);
        ui->BackGraphicsView->fitInView(m_scene.itemsBoundingRect(),Qt::KeepAspectRatio);
    }
}
