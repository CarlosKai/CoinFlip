#include "mainscene.h"
#include "ui_mainscene.h"
#include<QPainter>
#include"mypushbutton.h"
#include"chooselevelscene.h"
#include<QTimer>
#include<QSound>
MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);
    connect(ui->actionquit,&QAction::triggered,this,[=](){
        this->close();
    });
    this->setFixedSize(320,588);
    this->setWindowTitle("CoinFlip");
    //设置图片
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));


    //开始按钮创建
    MyPushButton *startbtn=new MyPushButton(":/res/MenuSceneStartButton.png");
    startbtn->setParent(this);
    startbtn->move(this->width()*0.5-startbtn->width()*0.5,this->height()*0.7);

    //开始按钮音效
    QSound *startSound=new QSound(":/res/TapButtonSound.wav",this);
    //startSound->setLoops(2);//设置循环次数，设置-1无限循环

    //场景二
    chooseScene=new ChooseLevelScene;

    //监听第二个场景返回信号
    connect(chooseScene,&ChooseLevelScene::chooseSceneBack,this,[=](){
       chooseScene->hide();
       //自身位置同步
       this->setGeometry(chooseScene->geometry());
        this->show();
    });

    connect(startbtn,&MyPushButton::clicked,[=](){
        startSound->play();
    });

    connect(startbtn,&MyPushButton::clicked,this,[=](){
       startbtn->Zoom1();
       startbtn->Zoom2();
       //进入下一个场景,隐藏自身,延时进入到第二个场景
       QTimer::singleShot(500,this,[=](){
           this->hide();
           //设置选择关卡场景的位置
           chooseScene->setGeometry(this->geometry());
           chooseScene->show();
       });//延时时间

    });


}

void MainScene::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    //画背景图片
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //画标题图片
    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);
}

MainScene::~MainScene()
{
    delete ui;
}
