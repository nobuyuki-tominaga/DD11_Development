#ifndef PASSWDSETTINGDIALOG_H
#define PASSWDSETTINGDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "Settings.h"

namespace Ui {
class CPasswd;
}

class CPasswd : public QDialog
{
    Q_OBJECT

public:
    explicit CPasswd(QWidget *parent = 0, CSettings *settings = NULL);
    ~CPasswd();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::CPasswd *ui;

    CSettings *m_pSettings;
};

#endif // PASSWDSETTINGDIALOG_H
