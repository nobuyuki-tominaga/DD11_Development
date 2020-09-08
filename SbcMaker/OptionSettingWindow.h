#ifndef OPTIONSETTINGWINDOW_H
#define OPTIONSETTINGWINDOW_H

#include <QWidget>

namespace Ui {
class COptionSetting;
}

class COptionSetting : public QWidget
{
    Q_OBJECT

public:
    explicit COptionSetting(QWidget *parent = 0);
    ~COptionSetting();

private:
    Ui::COptionSetting *ui;
};

#endif // OPTIONSETTINGWINDOW_H
