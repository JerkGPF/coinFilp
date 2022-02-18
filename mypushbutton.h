#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = nullptr);

    //normalImg代表显示的图片，pressImg代表按下显示的图片
    MyPushButton(QString normalImg,QString pressImg = "");

    QString normalImgPath;
    QString pressImgPath;

    //向下弹起
    void zoom1();
    //向上弹起
    void zoom2();

    //重写鼠标事件
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
signals:

};

#endif // MYPUSHBUTTON_H
