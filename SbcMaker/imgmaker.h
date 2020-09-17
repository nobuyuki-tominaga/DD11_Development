#ifndef IMGMAKER_H
#define IMGMAKER_H
#include "SbcMakerCommon.h"
#include <QString>
#include <QGraphicsScene>


class ImgMaker
{
public:

    //  コンストラクタ
    ImgMaker();
    //  デストラクタ
    ~ImgMaker();

    void getPhotoComposition();
    QGraphicsScene previewImgMaker(QGraphicsScene Scene1, QGraphicsScene Scene2);
    void createBcardFront(EMPLOYEE_INFO *info);
    void createBcardBack(EMPLOYEE_INFO *info);

private:
    QGraphicsScene Scene1, Scene2;

};
void getEmployeeInfo(EMPLOYEE_INFO *info);　//社員情報取得　動作確認用


#endif // IMGMAKER_H
