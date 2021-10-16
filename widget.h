#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QString>
#include "MyButton.h"
#include "WarGameWidget.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);//构造函数

private:
    int n,m;//棋盘大小n*m，n大于等于10，m大于等于10
    int k;//棋子个数，在最右边，位置随机，大于等于3，小于等于n
    int g;//目标进攻区的y坐标
    int d;//防守点个数，大于等于5
    int b;//障碍个数，大于等于4
    int Round;//回合数，从1开始
    void initWidget();//初始化布局
    void initGame();//初始化游戏

    QVBoxLayout* verLayoutDetails;//详细信息区垂直布局
    QHBoxLayout* horLayoutWidget;//游戏运行区与详细信息区的水平布局

    WarGameWidget* warGame;//游戏运行区
    QWidget* widgetDetails;//详细信息区

    QLabel* labelShowRound;//回合显示标签
    QLabel* labelShowStatus;//状态显示标签
    MyButton* btnEndRound;//结束回合按钮

    void keyPressEvent(QKeyEvent *e);//键盘点击事件

private slots:

    void sltSelectSquare(int);//选中棋盘格槽函数
    void sltEndRound();//结束回合槽函数
    void sltWin();//游戏胜利槽函数
    void sltLose();//游戏失败槽函数
};
#endif // WIDGET_H
