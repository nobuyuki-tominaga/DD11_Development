#ifndef IMGMAKER_H
#define IMGMAKER_H

#include <QString>
#include <QGraphicsScene>

#include "SbcMakerCommon.h"

class ImgMaker
{
public:
    //  コンストラクタ
    ImgMaker();
    //  デストラクタ
    ~ImgMaker();

    void getPhotoComposition(QString strEmpNum);
    int createGraphic(QString strEmpNum, int fileType, bool fSave, QString strFilePath);
    int genViewGraphic(QGraphicsScene *scene, int Side);
    void createBcardFront(EMPLOYEE_INFO *info);
    void createBcardBack(EMPLOYEE_INFO *info);

private:
    //QGraphicsScene Scene1, Scene2;

};
#endif // IMGMAKER_H
