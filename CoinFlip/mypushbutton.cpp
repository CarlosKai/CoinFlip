#include "mypushbutton.h"
#include<QPropertyAnimation>
#include<QDebug>
//MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
//{
//}
//上面注释的这个是之前的构造函数，现在要自己重新写一个构造函数
MyPushButton::MyPushButton(QString normalImg, QString pressImg){
    this->normalImgPath=normalImg;
    this->pressedImgPath=pressImg;
    QPixmap pix;
    bool ret=pix.load(this->normalImgPath);
    if(!ret){
        QString str=QString("%1 图片加载失败").arg(this->normalImgPath);
        qDebug() << str;
        return;
    }
    //设置按钮的大小
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet( "QPushButton{border:0px;}" );
    //设置图片大小
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
}
void MyPushButton::Zoom1(){
    QPropertyAnimation * animation =new QPropertyAnimation(this,"geometry");
    //设定时间间隔
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}
void MyPushButton::Zoom2(){
    QPropertyAnimation * animation =new QPropertyAnimation(this,"geometry");
    //设定时间间隔
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}

void MyPushButton::mousePressEvent(QMouseEvent *e){//你只做该做的事情，其他事情传参给上级操作
    if(this->pressedImgPath!=""){
        QPixmap pix;
        bool ret=pix.load(this->pressedImgPath);
        if(!ret){
            qDebug()<<"图片下载失败";
            return;
        }
        //设置按钮的大小
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet( "QPushButton{border:0px;}" );
        //设置图片大小
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
    }//路径不为空，切换

    //其他事情交给上级处理
    QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e){
    if(this->pressedImgPath!=""){
        QPixmap pix;
        bool ret=pix.load(this->normalImgPath);
        if(!ret){
            qDebug()<<"图片下载失败";
            return;
        }
        //设置按钮的大小
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet( "QPushButton{border:0px;}" );
        //设置图片大小
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
    }//路径不为空，切换

    //其他事情交给上级处理
    QPushButton::mouseReleaseEvent(e);
}

