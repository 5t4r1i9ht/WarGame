#ifndef WARGAMEWIDGET_H
#define WARGAMEWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <set>
#include <cstdlib>
#include <ctime>
#include "MyButton.h"
#include "Square.h"
#include "Chessman.h"

using namespace std;

class WarGameWidget : public QWidget
{
    Q_OBJECT

public:
    WarGameWidget(int _n=10,int _m=10,QWidget *parent=0);//构造函数
    friend class Widget;//声明友元类

private:

    int n,m;//棋盘大小n*m，n大于等于10，m大于等于10
    int k;//棋子个数，棋子在最右边，位置随机，大于等于3，小于等于n
    int g;//目标进攻区的y坐标
    int d;//防守点个数，大于等于5
    int b;//障碍个数，大于等于4

    int currentSquareID;//当前光标所指的棋盘格的数组下标
    int selectedSquareID;//被选中的棋盘格的数组下标

    bool allDied;//是否团灭状态，false：未团灭，true：已团灭
    Coordinate* allCoordinate;//棋盘上所有坐标指针
    Square** square;//棋盘格数组指针
    Chessman* chessman;//棋子数组指针
    QGridLayout *gridLayoutBody;//棋盘的网格布局

    void initWidget();//初始化布局
    void initGame(int _k, int _g, int _d, int _b);//初始化游戏

signals:
    void signalSelectSquare(int _squareID);//选中棋盘格信号
    void signalWin();//游戏胜利信号
    void signalLose();//游戏失败信号

private slots:
    void sltMoveToSquare(int _squareID);//光标移动到棋盘格槽函数
    void sltSelectSquare(int _squareID);//选中棋盘格槽函数
    void sltEndRound();//回合结束槽函数
};

#endif // WARGAMEWIDGET_H
