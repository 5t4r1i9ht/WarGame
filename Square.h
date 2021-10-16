#ifndef SQUARE_H
#define SQUARE_H

#include<QLabel>
#include<QString>
#include"Coordinate.h"

class Square : public QLabel
{
    Q_OBJECT

public:
    Square(QWidget *parent=0,int _squareID=0,int _x=0,int _y=0,int _chessmanType=0);//构造函数
    int getChessmanID();//获取棋盘格上棋子的ID
    int getChessmanType();//获取棋盘格上棋子的类型
    void setSquareID(int _squareID);//设置棋盘格ID
    void setChessmanID(int _chessmanID);//设置棋盘格上的棋子ID
    void setChessmanType(int _chessmanType);//设置棋盘格上的棋子类型
    int getX();//获取棋盘格x坐标
    int getY();//获取棋盘格y坐标
    void setCoordinate(int _x,int _y);//设置棋盘格坐标
    void setMovedTo();//设置光标移动到棋盘格上的状态
    void cancelMove();//取消光标移动到棋盘格上的状态
    void setSelected();//设置棋盘格选中状态
    void cancelSelect();//取消棋盘格选中状态
    void setColor();//设置棋盘格颜色
    void setSquareText();//设置棋盘格文字
    void clearContent();//清空棋盘格内容

private:
    Coordinate* coordinate;//棋盘格坐标
    int squareID;//棋盘格ID，代表棋盘格数组的下标，大于0
    int chessmanID;//棋盘格上棋子的ID，大于0，ID分配如下：1：目标进攻区，2~k+1：用棋子，k+2~k+1+d：防守点，k+2+d~k+1+d+b：障碍
    int chessmanType;//棋盘格上棋子的类型：0：无棋子，1：目标进攻区，2：防守点，3：棋子
    bool beMovedTo;//棋盘格是否被光标移动到的状态：false：未被移动到，true：被移动到
    bool beSelected;//棋盘格选中状态，false：未被选中，true被选中
    void mousePressEvent(QMouseEvent*);//鼠标点击棋盘格事件

signals:
    void signalMoveToSquare(int);//光标移动到棋盘格信号
    void signalSelectSquare(int);//棋盘格选中信号
};

#endif // SQUARE_H
