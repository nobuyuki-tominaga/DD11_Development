#include <QDebug>
#include "PasswdSettingDialog.h"
#include "ui_PasswdSettingDialog.h"

CPasswd::CPasswd(QWidget *parent, CSettings *settings) :
    QDialog(parent),
    ui(new Ui::CPasswd)
{
    ui->setupUi(this);

    m_pSettings = settings;
}

CPasswd::~CPasswd()
{
    delete ui;
}

void CPasswd::on_buttonBox_clicked(QAbstractButton *button)
{
    QString numStr;
    QMessageBox msgBox(this);

    msgBox.setWindowTitle(tr("メッセージ"));
    if(ui->buttonBox->standardButton(button) == QDialogButtonBox::Ok){
        qDebug("PW:%s", qPrintable(ui->pwLineEdit->text()));
//        if(makePemFile(m_pSettings->getCertP12File(), ui->pwLineEdit->text(), &numStr) == 0){
        if(1){
            m_pSettings->setEmployeeNum(numStr);
            m_pSettings->setExistenceFlg(true);
            msgBox.setText(tr("PEMファイル作成成功"));
        }
        else{
            m_pSettings->setExistenceFlg(false);
            msgBox.setText(tr("PEMファイル作成失敗"));
        }
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        this->close();
    }
    else {
        qDebug("キャンセル");
        this->close();
    }
}
