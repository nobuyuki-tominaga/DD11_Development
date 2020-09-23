#include <QDebug>
#include <QTranslator>
#include <QLibraryInfo>
#include <QFileDialog>
#include <QStandardPaths>
#include "SbcMakerCommon.h"
#include "OptionSettingDialog.h"
#include "ui_OptionSettingDialog.h"
#include "PasswdSettingDialog.h"


COptionSetting::COptionSetting(QWidget *parent, CSettings *settings) :
    QDialog(parent),
    ui(new Ui::COptionSetting)
{
    ui->setupUi(this);

    m_pSettings = settings;
    // ** 初期状態を設定 **
    // - 管理者権限チェックボックス(グレーアウト(未実装))
    ui->adminCheckBox->setDisabled(true);
    // - 保存先テキスト領域
    ui->saveDirLineEdit->setText(m_pSettings->getSaveDir());
    // - 証明書ファイルパステキスト領域
    ui->certFileLineEdit->setText(m_pSettings->getCertP12File());
    // - 保存画像フォーマット選択
    ui->saveFmtComboBox->setCurrentIndex(m_pSettings->getSaveImgFmt());

}

COptionSetting::~COptionSetting()
{
    delete ui;
}

void COptionSetting::on_buttonBox_clicked(QAbstractButton *button)
{
    bool saveFlg = false;
    int  msgboxRet = 0;

    // 「保存」ボタン処理
    if(ui->buttonBox->standardButton(button) == QDialogButtonBox::Save){
        saveFlg = true;
    }
    //「キャンセル」ボタン処理
    else {
        //保存しなくてよいかの確認メッセージを表示
        QMessageBox msgBox(this);
        msgBox.setWindowTitle(tr("メッセージ"));
        msgBox.setText(tr("変更を保存しますか？"));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setButtonText(QMessageBox::Yes, tr("はい"));
        msgBox.setButtonText(QMessageBox::No, tr("いいえ"));
        msgBox.setDefaultButton(QMessageBox::No);
        msgboxRet = msgBox.exec();
        if(msgboxRet == QMessageBox::Yes){
            saveFlg = true;
        }
        else{
            saveFlg = false;
        }
    }
    if(saveFlg == true){
        // INIファイルへ保存
        m_pSettings->setSaveDir(ui->saveDirLineEdit->text());
        m_pSettings->setSaveImgFmt(ui->saveFmtComboBox->currentIndex());
        m_pSettings->setCertP12File(ui->certFileLineEdit->text());
        // pemファイルの有無を確認
        if((m_pSettings->getExistenceFlg() == false) || (ui->updateCheckBox->checkState() == Qt::Checked)){
            QTranslator translator;
            translator.load("qt_ja_JP", QLibraryInfo::location(QLibraryInfo::TranslationsPath));
            qApp->installTranslator(&translator);
            // パスワード入力画面をモーダルダイアログとして表示
            CPasswd pwWindow(this, m_pSettings);
            pwWindow.exec(); // ダイアログが閉じるまで待機
        }
        m_pSettings->saveIniFile();
    }
    this->close();
}

void COptionSetting::on_saveDirToolButton_clicked()
{
    QTranslator translator;
    translator.load("qt_ja_JP", QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    qApp->installTranslator(&translator);
    QFileDialog::Options options = QFileDialog::ShowDirsOnly |
                                   QFileDialog::HideNameFilterDetails |
                                   QFileDialog::DontUseCustomDirectoryIcons;

    QString dirName = QFileDialog::getExistingDirectory(this, tr("フォルダ選択"), m_pSettings->getSaveDir(), options);

    if(!dirName.isEmpty()){
        ui->saveDirLineEdit->setText(dirName);
    }
}

void COptionSetting::on_certFileToolButton_clicked()
{
    QTranslator translator;
    translator.load("qt_ja_JP", QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    qApp->installTranslator(&translator);

    QString filename = QFileDialog::getOpenFileName(this, tr("証明書選択"), m_pSettings->getCertP12File(), tr("P12 FIle(*.p12);;ALL Files(*.*)"));

    if(!filename.isEmpty()){
        ui->certFileLineEdit->setText(filename);
    }
}
