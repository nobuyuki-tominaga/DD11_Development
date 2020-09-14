#include <QDebug>
#include "PasswdSettingDialog.h"
#include "ui_PasswdSettingDialog.h"

CPasswd::CPasswd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CPasswd)
{
    ui->setupUi(this);
}

CPasswd::~CPasswd()
{
    delete ui;
}

void CPasswd::on_buttonBox_clicked(QAbstractButton *button)
{
    if(ui->buttonBox->standardButton(button) == QDialogButtonBox::Ok){
        qDebug("PW:%s", ui->pwLineEdit->text().toUtf8().constData());
        this->close();
    }
    else {
        qDebug("キャンセル");
        this->close();
    }
}
