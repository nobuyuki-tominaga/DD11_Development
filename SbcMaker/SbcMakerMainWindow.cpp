#include "SbcMakerMainWindow.h"
#include "ui_SbcMakerMainWindow.h"

CSbcMakerMain::CSbcMakerMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CSbcMakerMain)
{
    ui->setupUi(this);
}

CSbcMakerMain::~CSbcMakerMain()
{
    delete ui;
}
