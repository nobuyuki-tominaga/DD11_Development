#ifndef SBCMAKERMAINWINDOW_H
#define SBCMAKERMAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "Settings.h"

namespace Ui {
class CSbcMakerMain;
}

class CSbcMakerMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit CSbcMakerMain(QWidget *parent = 0);
    ~CSbcMakerMain();

private slots:
    void on_settingPushButton_clicked();

    void on_previewPushButton_clicked();

    void on_imgGenPushButton_clicked();

    void on_finishPushButton_clicked();

    void on_viewTabWidget_tabBarClicked(int index);

private:
    Ui::CSbcMakerMain *ui;
    CSettings sbcSettings;

    QGraphicsScene m_scene;
};

#endif // SBCMAKERMAINWINDOW_H
