#ifndef OPTIONSETTINGWINDOW_H
#define OPTIONSETTINGWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include "Settings.h"

namespace Ui {
class COptionSetting;
}

class COptionSetting : public QDialog
{
    Q_OBJECT

public:
    explicit COptionSetting(QWidget *parent = 0, CSettings *settings = NULL);
    ~COptionSetting();

private slots:

    void on_buttonBox_clicked(QAbstractButton *button);

    void on_saveDirToolButton_clicked();
    
    void on_certFileToolButton_clicked();
    
private:
    Ui::COptionSetting *ui;

    CSettings *m_pSettings;
};

#endif // OPTIONSETTINGWINDOW_H
