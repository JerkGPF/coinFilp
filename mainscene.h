#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include "chooselevelscene.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

    //绘图事件绘制背景
    void paintEvent(QPaintEvent *);
    //选择关卡的指针
    ChooseLevelScene *chooseScene;

private:
    Ui::MainScene *ui;
};
#endif // MAINSCENE_H
