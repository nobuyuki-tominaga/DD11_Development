#include <QMessageBox>
#include <QTranslator>
#include <QLibraryInfo>
#include "SbcMakerMainWindow.h"
#include "ui_SbcMakerMainWindow.h"
#include "OptionSettingDialog.h"

CSbcMakerMain::CSbcMakerMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CSbcMakerMain)
{
    ui->setupUi(this);
    // 「社員番号入力欄」を入力不可
    ui->employeeNumLineEdit->setDisabled(true);
//    ui->employeeNumLineEdit->setReadOnly(true);
    // 「プレビュー」ボタンをグレーアウト(押下不可)
    ui->previewPushButton->setDisabled(true);
    // 「作成」ボタンをグレーアウト(押下不可)
    ui->imgGenPushButton->setDisabled(true);

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
    COptionSetting setWindow(this);
    setWindow.exec(); // ダイアログが閉じるまで待機

}

void CSbcMakerMain::on_previewPushButton_clicked()
{

}

void CSbcMakerMain::on_imgGenPushButton_clicked()
{

}

void CSbcMakerMain::on_finishPushButton_clicked()
{
    this->close();
}
