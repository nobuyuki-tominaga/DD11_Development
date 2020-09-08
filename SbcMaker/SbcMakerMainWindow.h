#ifndef SBCMAKERMAINWINDOW_H
#define SBCMAKERMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class CSbcMakerMain;
}

class CSbcMakerMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit CSbcMakerMain(QWidget *parent = 0);
    ~CSbcMakerMain();

private:
    Ui::CSbcMakerMain *ui;
};

#endif // SBCMAKERMAINWINDOW_H
