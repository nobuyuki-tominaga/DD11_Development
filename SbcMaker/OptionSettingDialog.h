#ifndef OPTIONSETTINGWINDOW_H
#define OPTIONSETTINGWINDOW_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class COptionSetting;
}

class COptionSetting : public QDialog
{
    Q_OBJECT

public:
    explicit COptionSetting(QWidget *parent = 0);
    ~COptionSetting();

private slots:

    void on_buttonBox_clicked(QAbstractButton *button);

    void on_saveDirToolButton_clicked();
    
    void on_certFileToolButton_clicked();
    
private:
    Ui::COptionSetting *ui;
};

#endif // OPTIONSETTINGWINDOW_H
