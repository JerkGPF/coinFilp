#ifndef MYICON_H
#define MYICON_H

#include <QPushButton>

class MyIcon : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyIcon(QWidget *parent = nullptr);

    //默认显示图片路径
    MyIcon(QString imgPath);

    //x坐标
    int posX;
    //y坐标
    int posY;
    //正反标识
    bool flag;
    void changeFlag();//改变标识，执行翻转效果
    QTimer *timer1;//正面翻转反面定时器
    QTimer *timer2;//反面翻转正面定时器
    int min = 1;//最小图片
    int max = 8;//最大图片
    bool isAnimation = false;//翻转动画的标志
    //重写鼠标按下事件
    void mousePressEvent(QMouseEvent *e);
    bool isWin = false;
signals:

};

#endif // MYICON_H
