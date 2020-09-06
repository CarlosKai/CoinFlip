#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include"mycoin.h"
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit PlayScene(QWidget *parent = nullptr);

    PlayScene(int index);
    //记录本关的关卡号
    int levelIndex;
    void paintEvent(QPaintEvent *);

    //游戏中二维数组,维护金币与银币
    int gameArray[4][4];

    MyCoin *coinBtn[4][4];
    //是否胜利
    bool isWin;

signals:
    void chooseSceneBack();

public slots:
};

#endif // PLAYSCENE_H
