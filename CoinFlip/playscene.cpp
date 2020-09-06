#include "playscene.h"
#include<QDebug>
#include<QMenuBar>
#include<QPainter>
#include"mypushbutton.h"
#include<QTimer>
#include<QLabel>
#include<QFont>
#include"mycoin.h"
#include"dataconfig.h"
#include<QPropertyAnimation>
#include<QSound>
//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}

PlayScene::PlayScene(int index){
    //    qDebug()<<"打开了"<<index<<"关";
    this->levelIndex=index;
    this->setFixedSize(320,588);
    this->setWindowTitle("翻金币场景");
    //设置图片
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    //创建菜单栏
    QMenuBar *bar=menuBar();
    this->setMenuBar(bar);
    QMenu * startMenu = bar->addMenu("开始");
    QAction *quitMenu= startMenu->addAction("退出");

    connect(quitMenu,&QAction::triggered,this,&PlayScene::close);

    this->isWin=false;

    //翻金币音效
    QSound *flipSound = new QSound(":/res/ConFlipSound.wav",this);
    //胜利按钮音效
    QSound *winSound = new QSound(":/res/LevelWinSound.wav",this);

    //返回按钮音效
    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);
    //返回按钮
    MyPushButton *backBtn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    connect(backBtn,&MyPushButton::clicked,this,[=](){
        //隐藏自身
        //延时发送信号
        //播放返回音效
        backSound->play();
        QTimer::singleShot(200,this,[=](){
            emit this->chooseSceneBack();
        });
    });




    //显示具体关卡号
    QLabel *label=new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    label->setFont(font);
    QString str=QString("Level %1 ").arg(levelIndex);
    label->setText(str);
    label->setGeometry(QRect(30,this->height()-50,120,50));//长120，宽50的矩形，前两位为坐标


    //初始化本关二维数组
    dataConfig data;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            this->gameArray[i][j]=data.mData[this->levelIndex][i][j];
        }
    }

    //创建胜利效果的图片
    QLabel *winLabel=new QLabel;
    QPixmap pix;
    pix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(QRect(0,0,pix.width(),pix.height()));
    winLabel->setParent(this);
    winLabel->setPixmap(pix);
    winLabel->move((this->width()-pix.width())*0.5,-pix.height());

    //创建金币背景图片
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            //Qlabel显示图片
            QLabel *bg=new QLabel(this);
            QPixmap pix;
            pix.load(":/res/BoardNode(1).png");
            bg->setGeometry(0,0,pix.width(),pix.height());
            bg->setPixmap(pix);
            bg->move(57+i*50,200+j*50);


            //创建金币
            QString str;
            if(this->gameArray[i][j]==1){
                str=":/res/Coin0001.png";
            }
            else{
                str=":/res/Coin0008.png";
            }

            MyCoin *coin=new MyCoin(str);
            coin->posX=i;
            coin->posY=j;
            coin->flag=gameArray[i][j];

            coin->setParent(this);
            coin->move(59+i*50,204+j*50);

            //将Coin放入维护金币的二维数组中
            coinBtn[i][j]=coin;

            connect(coin,&MyCoin::clicked,[=](){
                //点击后，禁用其他按钮
                flipSound->play();
                for(int i=0;i<4;i++){
                    for(int j=0;j<4;j++){

                        this->coinBtn[i][j]->isWin=true;
                    }
                }
            });

            connect(coin,&MyCoin::clicked,[=](){
                coin->changeFlag();
                gameArray[i][j]=gameArray[i][j]==0?1:0;

                //继续翻动周围的硬币
                QTimer::singleShot(300,this,[=](){
                    if(coin->posX+1<=3){
                        coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        gameArray[coin->posX+1][coin->posY]=gameArray[coin->posX+1][coin->posY]==0?1:0;
                    }
                    if(coin->posX-1>=0){
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        gameArray[coin->posX-1][coin->posY] = gameArray[coin->posX-1][coin->posY]== 0 ? 1 : 0;
                    }
                    if(coin->posY+1<=3){
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        gameArray[coin->posX][coin->posY+1] = gameArray[coin->posX+1][coin->posY]== 0 ? 1 : 0;
                    }
                    if(coin->posY-1>=0){
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        gameArray[coin->posX][coin->posY-1] = gameArray[coin->posX+1][coin->posY]== 0 ? 1 : 0;
                    }




                    //点击后，解禁用
                    for(int i=0;i<4;i++){
                        for(int j=0;j<4;j++){

                            this->coinBtn[i][j]->isWin=false;
                        }
                    }
                    this->isWin=true;
                    for(int i=0;i<4;i++){
                        for(int j=0;j<4;j++){
                            //qDebug()<<coinBtn[i][j]->flag;
                            if(coinBtn[i][j]->flag==false){
                                this->isWin=false;
                                break;
                            }
                        }
                    }
                    //翻完硬币判断是否全都是金币

                    if(this->isWin==true){
                        // qDebug()<<"游戏胜利";
                        //播放胜利音效
                        winSound->play();
                        for(int i=0;i<4;i++){
                            for(int j=0;j<4;j++){
                                coinBtn[i][j]->isWin=true;
                            }

                        }

                        //显示胜利图片
                        QPropertyAnimation *animation=new QPropertyAnimation(winLabel,"geometry");
                        animation->setDuration(1000);
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        animation->start();
                    }

                });
                //边界检测



            });


        }
    }


}

void PlayScene::paintEvent(QPaintEvent *){
    //绘制背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //绘制标题
    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);//一定要加pix=pix.scaled，否则pix缩放好了往哪儿放？
    painter.drawPixmap( 10,30,pix);


}
