#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include <QWidget>
#include "playscene.h"

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

    //重写绘图事件
    void paintEvent(QPaintEvent *);
    //下一个场景
    PlayScene *playScene;

signals:
    //发出返回信号
    void chooseSceneBack();

};

#endif // CHOOSELEVELSCENE_H
