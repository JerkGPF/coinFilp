#include "myicon.h"
#include <QDebug>
#include <QTimer>
//MyIcon::MyIcon(QWidget *parent) : QWidget(parent)
//{

//}

MyIcon::MyIcon(QString imgPath)
{
    QPixmap pix;
    bool ret = pix.load(imgPath);
    if(!ret)
    {
        qDebug()<<"图片加载失败"<<imgPath;
        return;
    }

    pix = pix.scaled(pix.width()*2,pix.height()*2);//图片进行缩放
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    //创建两个定时器
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);
    //监听两个定时器的信号
    //金币翻银币的定时器
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1").arg(this->min++);
        bool ret = pix.load(str);
        if(!ret)
        {
            qDebug()<<"图片加载失败"<<imgPath;
            return;
        }

        pix = pix.scaled(pix.width()*2,pix.height()*2);//图片进行缩放
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(min>max)
        {
            this->min = 1;//还原最小值停止定时器
            this->isAnimation = false;//改回动画标志

            timer1->stop();
        }
    });
    //银币翻金币
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1").arg(this->max--);
        bool ret = pix.load(str);
        if(!ret)
        {
            qDebug()<<"图片加载失败"<<imgPath;
            return;
        }

        pix = pix.scaled(pix.width()*2,pix.height()*2);//图片进行缩放
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(max<min)
        {
            this->max = 8;//还原最大值，停止定时器
            this->isAnimation = false;//改回动画标志
            timer2->stop();
        }
    });
    qDebug()<<"图片加载成功"<<imgPath;
}
//改变状态
void MyIcon::changeFlag()
{
    //如果金币改为银币
    if(this->flag)
    {
        //启动金币翻银币的定时器
        timer1->start(30);
        this->isAnimation = true;//正在做动画的标志
        flag = false;

    }
    else
    {
        timer2->start(30);
        this->isAnimation = true;//正在做动画的标志

        flag = true;
    }

}

void MyIcon::mousePressEvent(QMouseEvent *e)
{
    //如果在做动画，不响应。
    //否则抛给父类
    if(this->isAnimation||this->isWin)
        return;
    else
        QPushButton::mousePressEvent(e);
}
