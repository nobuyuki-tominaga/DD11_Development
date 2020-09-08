#ifndef PASSWDSETTINGDIALOG_H
#define PASSWDSETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class CPasswd;
}

class CPasswd : public QDialog
{
    Q_OBJECT

public:
    explicit CPasswd(QWidget *parent = 0);
    ~CPasswd();

private:
    Ui::CPasswd *ui;
};

#endif // PASSWDSETTINGDIALOG_H
