#include "chooselevelscene.h"
#include<QMenuBar>
#include<QPainter>
#include<mypushbutton.h>
#include<QTimer>
#include<QLabel>
#include<QSound>
ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(320,588);
    this->setWindowTitle("选关");
    //设置图片
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    //创建菜单栏
    QMenuBar *bar=menuBar();
    this->setMenuBar(bar);
    QMenu * startMenu = bar->addMenu("开始");
    QAction *quitMenu= startMenu->addAction("退出");
    connect(quitMenu,&QAction::triggered,this,&ChooseLevelScene::close);

    //选择关卡音效
    QSound *chooseSound=new QSound(":/res/TapButtonSound.wav",this);

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
        QTimer::singleShot(400,this,[=](){
              emit this->chooseSceneBack();
        });
    });



    playScene=NULL;



    //选择关卡按钮
    for(int i=0;i<20;i++){
        MyPushButton *menuBtn=new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25+(i%4)*70,130+(i/4)*70);

        connect(menuBtn,&MyPushButton::clicked,[=](){
//            QString str=QString("您选择的是第 %1 关").arg(i+1);
//            qDebug()<<str;

            chooseSound->play();

            //进入游戏场景
            this->hide();
            playScene=new PlayScene(i+1);

            //游戏场景位置同步
            playScene->setGeometry(this->geometry());

            playScene->show();
            connect(playScene,&PlayScene::chooseSceneBack,this,[=](){
                //游戏场景隐藏
                this->setGeometry(playScene->geometry());

                playScene->close();
                delete playScene;
                playScene=NULL;
                //设置选择关卡场景的位置为游戏场景返回位置

                this->show();
            });
        });
        //字可能覆盖在按钮之上可能会造成拦截
        //不规则按钮不用settext显示文字
        QLabel *label=new QLabel(this);
        //设置标签大小
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        //设置显示的内容
        label->setText(QString::number(i+1));
        label->move(25+(i%4)*70,130+(i/4)*70);
        //设置居中
        label->setAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
        //设置鼠标穿透
        label->setAttribute(Qt::WA_TransparentForMouseEvents);//51号穿透属性
    }

}

void ChooseLevelScene::paintEvent(QPaintEvent *){
    QPainter painter(this);
        QPixmap pix;
        pix.load(":/res/OtherSceneBg.png");
        painter.drawPixmap(0,0,this->width(),this->height(),pix);

         //加载标题
        pix.load(":/res/Title.png");
        painter.drawPixmap( (this->width() - pix.width())*0.5,30,pix.width(),pix.height(),pix);
    }


