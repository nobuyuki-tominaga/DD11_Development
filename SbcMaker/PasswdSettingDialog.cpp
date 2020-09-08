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
