#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>
//MyPushButton::MyPushButton(QWidget *parent) : QWidget(parent)
//{

//}

MyPushButton::MyPushButton(QString normalImg, QString pressImg)
{
    this->normalImgPath = normalImg;
    this->pressImgPath = pressImg;

    //Qpixmap加载图标
    QPixmap pix;
    bool ret = pix.load(normalImgPath);
    if(!ret)
    {
        QString str = QString ("图片加载失败 %1").arg(normalImg);
        qDebug()<<str;
        return;
    }
    //设置图片大小
    this->setFixedSize(pix.width(),pix.height());
    //设置风格
    this->setStyleSheet("QPushButton{border:0px}");
    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));

}

void MyPushButton::zoom1()
{
    QPropertyAnimation* animation = new QPropertyAnimation(this,"geometry");
    //设置动画时间间隔
    animation->setDuration(200);
    //动画起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //弹起效果
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //让动画执行
    animation->start(QAbstractAnimation::DeleteWhenStopped);


}

void MyPushButton::zoom2()
{
    QPropertyAnimation* animation = new QPropertyAnimation(this,"geometry");
    //设置动画时间间隔
    animation->setDuration(200);
    //动画起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //弹起效果
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //让动画执行
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    //如果按下路径的图片不为空则切图
    if(this->pressImgPath!="")
    {
        //Qpixmap加载图标
        QPixmap pix;
        bool ret = pix.load(pressImgPath);
        if(!ret)
        {
            QString str = QString ("图片加载失败 %1").arg(pressImgPath);
            qDebug()<<str;
            return;
        }
        //设置图片大小
        this->setFixedSize(pix.width(),pix.height());
        //设置风格
        this->setStyleSheet("QPushButton{border:0px}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //点击事件抛给父类处理
    QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    //如果按下路径的图片不为空则切图
    if(this->pressImgPath!="")
    {
        //Qpixmap加载图标
        QPixmap pix;
        bool ret = pix.load(this->normalImgPath);
        if(!ret)
        {
            QString str = QString ("图片加载失败 %1").arg(normalImgPath);
            qDebug()<<str;
            return;
        }
        //设置图片大小
        this->setFixedSize(pix.width(),pix.height());
        //设置风格
        this->setStyleSheet("QPushButton{border:0px}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //点击事件抛给父类处理
    QPushButton::mouseReleaseEvent(e);
}
