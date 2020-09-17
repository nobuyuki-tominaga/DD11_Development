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

    void getPhotoComposition();
    //QGraphicsScene previewImgMaker(QGraphicsScene Scene1, QGraphicsScene Scene2);
    int graphicCreate(QGraphicsScene *Scene, QString strEmpNum, int Side, bool fSave, QString strFilePath);
    void createBcardFront(EMPLOYEE_INFO *info);
    void createBcardBack(EMPLOYEE_INFO *info);

private:
    //QGraphicsScene Scene1, Scene2;

};
#endif // IMGMAKER_H
