#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H
#include<QPushButton>
#include <QWidget>
#include <QDebug>
class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
   // explicit MyPushButton(QWidget *parent = nullptr);

    MyPushButton(QString normalImg,QString pressImg="");
    QString normalImgPath;  //默认显示图片路径
    QString pressedImgPath; //按下后显示图片路径

    //跳跃
    void Zoom1();
    void Zoom2();
    //按下，释放
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);


signals:

public slots:
};

#endif // MYPUSHBUTTON_H
