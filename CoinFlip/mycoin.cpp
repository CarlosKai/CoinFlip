#include "mycoin.h"
#include<QPixmap>
#include<QMessageBox>
#include<QTimer>
MyCoin::MyCoin(QString CoinImg){
    QPixmap pix;
    bool ret=pix.load(CoinImg);
    if(!ret){
        QString str=QString("图片加载失败 %1 ").arg(CoinImg);
        QMessageBox::critical(this,"加载失败",str);
        return;
    }
    this->setFixedSize(pix.width(),pix.height());//按钮的大小
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);//放置具体显示的内容
    this->setIconSize(QSize(pix.width(),pix.height()));

    timer1=new QTimer(this);
    timer2=new QTimer(this);

    this->isAnimation=false;
    this->isWin=false;

    //监听定时器
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/res/Coin000%1.png").arg(this->min++);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());//按钮的大小
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);//放置具体显示的内容
        this->setIconSize(QSize(pix.width(),pix.height()));

        if(this->min>this->max)
        {
            this->min=1;
            this->isAnimation=false;
            timer1->stop();
        }

    });
    //银币翻金币
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/res/Coin000%1.png").arg(this->max--);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());//按钮的大小
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);//放置具体显示的内容
        this->setIconSize(QSize(pix.width(),pix.height()));

        if(this->max<this->min)
        {
            this->max=8;
            this->isAnimation=false;
            timer2->stop();
        }

    });

}

void MyCoin::changeFlag(){
    if(this->flag){//当前是正面
        //开启正面翻反面定时器
        timer1->start(30);
        //同步标志
        this->isAnimation=true;
        this->flag=false;
    }
    else{
        timer2->start(30);
        //同步标志
        this->isAnimation=true;
        this->flag=true;
    }
}
void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation ||this->isWin)
    {
        return;
    }
    else
    {
        return QPushButton::mousePressEvent(e);
    }
}
