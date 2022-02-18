#include "mainscene.h"
#include "ui_mainscene.h"
#include "mypushbutton.h"
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QSound>
MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    //设置主场景
    //设置标题
    this->setWindowTitle("翻金币主场景");
    //设置大小
    this->setFixedSize(480,800);
    //设置图标
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    //退出游戏
    connect(ui->actionquit,&QAction::triggered,[=](){
        close();
    });
    //开始音效准备
    QSound* startSound = new QSound(":/res/TapButtonSound.wav",this);

    //创建选择关卡的场景
    chooseScene = new ChooseLevelScene;
    //监听选择关卡中的自定义回退信号
    connect(chooseScene,&ChooseLevelScene::chooseSceneBack,[=](){
        chooseScene->hide();
        this->setGeometry(chooseScene->geometry());//设置位置
        this->show();
    });

    //开始按钮,自定义封装
    MyPushButton *startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.75);
    startBtn->setParent(this);//将按钮添加进当前布局

    connect(startBtn,&QPushButton::clicked,[=]()
    {
        //播放音效
        startSound->play();
        startBtn->zoom1();
        startBtn->zoom2();
        //延迟500毫秒切换场景
        QTimer::singleShot(500,this,[=](){
            this->hide();//自身隐藏
            //设置选择关卡位置
            chooseScene->setGeometry(this->geometry());
            chooseScene->show();//显示关卡
        });

    });
}
 //绘图事件绘制背景
void MainScene::paintEvent(QPaintEvent *)
{
    //背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix); //拉伸

    //加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.7,pix.height()*0.7);//图片进行缩放
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);

}

MainScene::~MainScene()
{
    delete ui;
}


