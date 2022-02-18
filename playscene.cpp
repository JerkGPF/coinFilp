#include "playscene.h"
#include <QDebug>
#include <QLabel>
#include <QMenuBar>
#include <QPainter>
#include <QSound>
#include <QTimer>
#include "mypushbutton.h"
#include "myicon.h"
#include "dataconfig.h"
#include <QPropertyAnimation>
//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}

PlayScene::PlayScene(int levelIndex)
{
    this->levelIndex = levelIndex;
    qDebug()<<"s"<<levelIndex<<endl;

    this->setWindowTitle("翻金币游戏场景");
    this->setFixedSize(768,1024);
    //设置图标
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    //菜单栏
    QMenuBar *bar = menuBar();//创建菜单栏
    QMenu *startMenu = bar->addMenu("开始");//创建菜单
    QAction *quitAction = startMenu->addAction("退出");//创建菜单项
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });
    //返回音效
    QSound* backSound = new QSound(":/res/BackButtonSound.wav",this);
    //翻金币音效
    QSound* flipSound = new QSound(":/res/ConFlipSound.wav",this);
    //胜利音效
    QSound* winSound = new QSound(":/res/LevelWinSound.wav",this);

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
    //用户关卡
    QLabel *label = new QLabel;
    label->setParent(this);
    QString str = QString("Level: %1").arg(this->levelIndex);
    label->setText(str);
    //设置字体和字号
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    label->setFont(font);
    //设置位置和大小
    label->setGeometry(QRect(30,this->height()-50,160,50));

    dataConfig config;
    for (int i = 0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            this->gameArray[i][j] = config.mData[levelIndex][i][j];
        }

    }
    //胜利图片
    QLabel *winLabel = new QLabel;
    winLabel->setParent(this);
    QPixmap winPix;
    winPix.load(":/res/LevelCompletedDialogBg.png");
    winPix = winPix.scaled(winPix.width()*2,winPix.height()*2);
    winLabel->setGeometry(0,0,winPix.width(),winPix.height());
    winLabel->setPixmap(winPix);
    winLabel->move(this->width()-winPix.width()*1.3,-winPix.height());

    //创建金币背景图
    for (int i = 0;i<4;i++)
    {
        for (int j = 0;j<4;j++)
        {
            QPixmap pix;
            pix.load(":/res/BoardNode.png");
            pix = pix.scaled(pix.width()*2,pix.height()*2);//图片进行缩放
            //Qlabel显示图片
            QLabel *lb = new QLabel(this);
            lb->setGeometry(0,0,pix.width(),pix.height());
            lb->setPixmap(pix);
            lb->move(180+i*pix.width(),300+j*pix.height());

            QString str;
            if(this->gameArray[i][j]==1)
                str = ":/res/Coin0001.png";
            else
                str = ":/res/Coin0008.png";
            //创建金币
            MyIcon* coin = new MyIcon(str);
            coin->setParent(this);
            coin->move(184+i*pix.width(),308+j*pix.height());
            //给金币的属性赋值
            coin->posX = i;
            coin->posY = j;
            coin->flag = this->gameArray[i][j];
            //将金币放入到二维数组中
            coinBtn[i][j] = coin;
            //监听按钮点击 信号
            connect(coin,&MyIcon::clicked,[=](){
                flipSound->play();
                //屏蔽所有按钮点击
                for(int i = 0;i<4;i++)
                {
                    for(int j = 0;j<4;j++)
                    {
                        coinBtn[i][j]->isWin = true;
                    }
                }
                coin->changeFlag();
                //同步二维数组，用于保存
                this->gameArray[i][j] = gameArray[i][j]==1 ? 0:1;
                //延时翻转周围硬币，监测右侧金币是否可翻转
                QTimer::singleShot(300,this,[=](){
                    if(coin->posX+1<=3)
                    {
                        coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX+1][coin->posY] = gameArray[coin->posX+1][coin->posY]==1 ? 0:1;
                    }
                    //监测左侧是否可翻转
                    if(coin->posX-1>=0)
                    {
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX-1][coin->posY] = gameArray[coin->posX-1][coin->posY]==1 ? 0:1;
                    }
                    //检查下侧金币
                    if(coin->posY+1<=3)
                    {
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY+1] = gameArray[coin->posX][coin->posY+1]==1 ? 0:1;
                    }
                    //监测上侧
                    if(coin->posY-1>=0)
                    {
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY-1] = gameArray[coin->posX][coin->posY-1]==1 ? 0:1;
                    }
                    //开启按钮点击状态
                    for(int i = 0;i<4;i++)
                    {
                        for(int j = 0;j<4;j++)
                        {
                            coinBtn[i][j]->isWin = false;
                        }
                    }
                    //检测是否胜利
                    isWin = true;
                    for(int i = 0;i<4;i++)
                    {
                        for(int j = 0;j<4;j++)
                        {
                            if(coinBtn[i][j]->flag==false)//如果有一个是银币的状态，则失败
                            {
                                isWin = false;
                                break;
                            }
                        }
                    }
                    //游戏胜利
                    if(isWin)
                    {
                        winSound->play();
                        for(int i = 0;i<4;i++)
                        {
                            for(int j = 0;j<4;j++)
                            {
                                coinBtn[i][j]->isWin = true;
                            }
                        }
                        //将胜利图片动画
                        QPropertyAnimation *winAnimation = new QPropertyAnimation(winLabel,"geometry");
                        winAnimation->setDuration(1000);
                        winAnimation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        winAnimation->setEndValue(QRect(winLabel->x(),winLabel->y()+220,winLabel->width(),winLabel->height()));
                        winAnimation->setEasingCurve(QEasingCurve::OutBounce);
                        winAnimation->start(QAbstractAnimation::DeleteWhenStopped);




                    }
                });

            });
        }
    }
}

void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.7,pix.height()*0.7);//图片进行缩放
    painter.drawPixmap(this->width()-pix.width()*4,30,pix.width(),pix.height(),pix);

}
