#ifndef MYCOIN_H
#define MYCOIN_H
#include<QPushButton>
#include <QWidget>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    explicit MyCoin(QWidget *parent = nullptr);

    MyCoin(QString CoinImg);

    int posX; //x坐标
    int posY; //y坐标
    bool flag; //正反标志
    bool isWin;//是否胜利

    void changeFlag();
    QTimer *timer1;
    QTimer *timer2;
    int min=1;
    int max=8;
    //是否执行动画
    bool isAnimation ; //做翻转动画的标志

//    //鼠标按下事件重写
    void mousePressEvent(QMouseEvent *e);

signals:

public slots:
};

#endif // MYCOIN_H
