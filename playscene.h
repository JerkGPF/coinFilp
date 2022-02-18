#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "myicon.h"
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int levelIndex);
    //关卡号
    int levelIndex;

    //绘图事件
    void paintEvent(QPaintEvent *);

    //记录当前关卡的二维数组
    int gameArray[4][4];
    //存放金币二维数组
    MyIcon* coinBtn[4][4];
    //胜利的标志
    bool isWin = true;

signals:

    void chooseSceneBack();
};

#endif // PLAYSCENE_H
