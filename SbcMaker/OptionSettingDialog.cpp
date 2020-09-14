#include <QDebug>
#include <QTranslator>
#include <QLibraryInfo>
#include <QFileDialog>
#include <QStandardPaths>
#include "SbcMakerCommon.h"
#include "OptionSettingDialog.h"
#include "ui_OptionSettingDialog.h"
#include "PasswdSettingDialog.h"

COptionSetting::COptionSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::COptionSetting)
{
    ui->setupUi(this);
    ui->adminCheckBox->setDisabled(true);
    ui->saveDirLineEdit->setText(tr(qgetenv("HOME").constData()));
    ui->certFileLineEdit->setText(tr(""));

}

COptionSetting::~COptionSetting()
{
    delete ui;
}

void COptionSetting::on_buttonBox_clicked(QAbstractButton *button)
{
    if(ui->buttonBox->standardButton(button) == QDialogButtonBox::Save){
        QTranslator translator;
        translator.load("qt_ja_JP", QLibraryInfo::location(QLibraryInfo::TranslationsPath));
        qApp->installTranslator(&translator);
        // パスワード入力画面をモーダルダイアログとして表示
        CPasswd pwWindow(this);
        pwWindow.exec(); // ダイアログが閉じるまで待機
        this->close();
    }
    else {
        qDebug("キャンセル");
        this->close();
    }
}

void COptionSetting::on_saveDirToolButton_clicked()
{
    QTranslator translator;
    translator.load("qt_ja_JP", QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    qApp->installTranslator(&translator);
    QFileDialog::Options options = QFileDialog::ShowDirsOnly |
                                   QFileDialog::HideNameFilterDetails |
                                   QFileDialog::DontUseCustomDirectoryIcons;

    QString dirName = QFileDialog::getExistingDirectory(this, tr("フォルダ選択"), tr(qgetenv("HOME").constData()), options);

    ui->saveDirLineEdit->setText(dirName);

}

void COptionSetting::on_certFileToolButton_clicked()
{
    QTranslator translator;
    translator.load("qt_ja_JP", QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    qApp->installTranslator(&translator);

    QString filename = QFileDialog::getOpenFileName(this, tr("証明書選択"), tr(qgetenv("HOME").constData()), tr("P12 FIle(*.p12);;ALL Files(*.*)"));

    ui->certFileLineEdit->setText(filename);
}
