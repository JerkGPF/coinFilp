#include "chooselevelscene.h"
#include "mypushbutton.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include <QSound>
ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //菜单栏
    QMenuBar *bar = menuBar();//创建菜单栏
    QMenu *startMenu = bar->addMenu("开始");//创建菜单
    QAction *quitAction = startMenu->addAction("退出");//创建菜单项
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });
    this->setWindowTitle("选择关卡场景");
    this->setFixedSize(768,1024);
    //设置图标
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    //选择按钮后的音效
    QSound* chooseSound = new QSound(":/res/TapButtonSound.wav",this);
    //返回音效
    QSound* backSound = new QSound(":/res/BackButtonSound.wav",this);

    //返回按钮
    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    connect(backBtn,&QPushButton::clicked,[=](){
//        qDebug()<<"返回到主场景";
        //播放音效
        backSound->play();
        //延迟发送信号,由主场景进行操作
        QTimer::singleShot(500,this,[=](){
            emit chooseSceneBack();
        });
    });
    playScene = NULL;//下一个场景
    //创建20个关卡按钮
    for(int i = 0;i<20;i++)
    {
        MyPushButton *menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(120+(i%4)*150,180+(i/4)*150);
        connect(menuBtn,&MyPushButton::clicked,[=](){
            //播放音效
            chooseSound->play();
            playScene = new PlayScene(i+1);       
            this->hide();
            //设置游戏场景位置
            this->playScene->setGeometry(this->geometry());
            playScene->show();
            //监听返回信号
            connect(playScene,&PlayScene::chooseSceneBack,[=](){
                this->setGeometry(playScene->geometry());
                delete this->playScene;
                this->playScene = NULL;
                this->show();
            });
//            qDebug()<<"选择了第"<<i+1<<"关";
        });
        //创建显示具体的label
        QLabel * label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->move(120+(i%4)*150,180+(i/4)*150);
        //设置label居中方式
        label->setAlignment(Qt::AlignCenter);
        //设置鼠标穿透事件
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //加载标题
    pix.load(":/res/Title.png");
    painter.drawPixmap(this->width()-pix.width()*2.8,30,pix.width(),pix.height(),pix);

}
