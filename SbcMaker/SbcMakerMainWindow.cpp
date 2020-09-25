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
    ImgMaker *cImg = new(ImgMaker);
    cImg->genViewGraphic(&m_scene, sides_front);   // 表示用(sceneの生成関数)
    ui->FrontGraphicsView->setScene(&m_scene);
    ui->FrontGraphicsView->fitInView(m_scene.itemsBoundingRect(),Qt::KeepAspectRatio);
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
    int fileType = sbcSettings.getSaveImgFmt();

    ImgMaker *cImg = new(ImgMaker);
    // プレビュー画像(保存画像)の作成関数
    if(cImg->createGraphic(strEmpNum, fileType, false, strFilePath) == SUCCESS){
        //アクティブなタブ(面)の表示
        if(ui->viewTabWidget->currentIndex() == sides_front){
            cImg->genViewGraphic(&m_scene, sides_front);   // 表示用(sceneの生成関数)
            ui->FrontGraphicsView->setScene(&m_scene);
            ui->FrontGraphicsView->fitInView(m_scene.itemsBoundingRect(),Qt::KeepAspectRatio);
        }
        else{
            cImg->genViewGraphic(&m_scene, sides_back);
            ui->BackGraphicsView->setScene(&m_scene);
            ui->BackGraphicsView->fitInView(m_scene.itemsBoundingRect(),Qt::KeepAspectRatio);
         }
    }
    else{
        // 画像作成に失敗した際にダイアログを表示する
        QMessageBox msgBox(this);
        msgBox.setText(tr("プレビュー画像作成失敗"));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
}

void CSbcMakerMain::on_imgGenPushButton_clicked()
{
    QString strEmpNum = sbcSettings.getEmployeeNum();
    QString strFilePath = sbcSettings.getSaveDir();
    int fileType = sbcSettings.getSaveImgFmt();

    ImgMaker *cImg = new(ImgMaker);
    // プレビュー画像(保存画像)の作成関数
    if(cImg->createGraphic(strEmpNum, fileType, true, strFilePath) == SUCCESS){
        //アクティブなタブ(面)の表示
        if(ui->viewTabWidget->currentIndex() == sides_front){
            cImg->genViewGraphic(&m_scene, sides_front);   // 表示用(sceneの生成関数)
            ui->FrontGraphicsView->setScene(&m_scene);
            ui->FrontGraphicsView->fitInView(m_scene.itemsBoundingRect(),Qt::KeepAspectRatio);
        }
        else{
            cImg->genViewGraphic(&m_scene, sides_back);
            ui->BackGraphicsView->setScene(&m_scene);
            ui->BackGraphicsView->fitInView(m_scene.itemsBoundingRect(),Qt::KeepAspectRatio);
         }
    }
    else{
        // 画像作成に失敗した際にダイアログを表示する
        QMessageBox msgBox(this);
        msgBox.setText(tr("画像作成失敗"));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
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
    int fileType = sbcSettings.getSaveImgFmt();

    //表面
    if(index == 0){
        ImgMaker *cImg = new(ImgMaker);
        cImg->createGraphic(strEmpNum, fileType, false, strFilePath);
        cImg->genViewGraphic(&m_scene, sides_front);

        ui->FrontGraphicsView->setScene(&m_scene);
        ui->FrontGraphicsView->fitInView(m_scene.itemsBoundingRect(),Qt::KeepAspectRatio);

    }
    //裏面
    else{
        ImgMaker *cImg = new(ImgMaker);
        cImg->createGraphic(strEmpNum, fileType, false, strFilePath);
        cImg->genViewGraphic(&m_scene, sides_back);

        ui->BackGraphicsView->setScene(&m_scene);
        ui->BackGraphicsView->fitInView(m_scene.itemsBoundingRect(),Qt::KeepAspectRatio);
    }
}
