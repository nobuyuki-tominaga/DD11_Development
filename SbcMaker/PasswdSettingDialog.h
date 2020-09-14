#ifndef PASSWDSETTINGDIALOG_H
#define PASSWDSETTINGDIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class CPasswd;
}

class CPasswd : public QDialog
{
    Q_OBJECT

public:
    explicit CPasswd(QWidget *parent = 0);
    ~CPasswd();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::CPasswd *ui;
};

#endif // PASSWDSETTINGDIALOG_H
