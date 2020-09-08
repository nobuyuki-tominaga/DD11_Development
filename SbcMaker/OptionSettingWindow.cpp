#include "OptionSettingWindow.h"
#include "ui_OptionSettingWindow.h"

COptionSetting::COptionSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::COptionSetting)
{
    ui->setupUi(this);
}

COptionSetting::~COptionSetting()
{
    delete ui;
}
