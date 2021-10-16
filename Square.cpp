#ifndef SQUARE_CPP
#define SQUARE_CPP

#include<QObject>
#include<QWidget>
#include<QLabel>
#include"Square.h"

//构造函数
Square::Square(QWidget *parent, int _squareId, int _x, int _y, int _chessmanType):QLabel(parent)
{
    squareID=_squareId;
    coordinate=new Coordinate(_x,_y);
    chessmanType=_chessmanType;
    beMovedTo=false;
    beSelected=false;
    setColor();
}

//获取棋盘格上的棋子ID
int Square::getChessmanID()
{
    return chessmanID;
}

//获取棋盘格上棋子的类型
int Square::getChessmanType()
{
    return chessmanType;
}

//设置棋盘格上的棋子的ID
void Square::setChessmanID(int _chessmanID)
{
    chessmanID=_chessmanID;
}

//设置棋盘格ID
void Square::setSquareID(int _squareID)
{
    squareID=_squareID;
}

//设置棋盘格上棋子的类型
void Square::setChessmanType(int _chessmanType)
{
    chessmanType=_chessmanType;
    setColor();
    setSquareText();
}

//获取棋盘格x坐标
int Square::getX()
{
    return coordinate->getX();
}

//获取棋盘格y坐标
int Square::getY()
{
    return coordinate->getY();
}

//设置棋盘格坐标
void Square::setCoordinate(int _x,int _y)
{
    coordinate->setCoordinate(_x,_y);
}

//设置棋盘格被光标移动到
void Square::setMovedTo()
{
    beMovedTo=true;
    setColor();
}

//取消棋盘格被光标移动到
void Square::cancelMove()
{
    beMovedTo=false;
    setColor();
}

//设置棋盘格被选中
void Square::setSelected()
{
    beSelected=true;
    setColor();
}

//取消棋盘格被选中
void Square::cancelSelect()
{
    beSelected=false;
    setColor();
}

//设置棋盘格颜色
void Square::setColor()
{
    QString temp_string="";
    //棋盘格上没有棋子时，设置棋盘格背景为白色
    if(chessmanType==0)
    {
        temp_string.append("background-color:#ffffff;color:#000000;");
    }
    //棋盘格上为目标进攻区时，设置棋盘格背景为浅红色，文字为红色
    else if(chessmanType==1)
    {
        temp_string.append("background-color:#ffb9b9;color:#ff0000;");
    }
    //棋盘格上为棋子时，设置棋盘格背景为浅绿色，文字为草绿色
    else if(chessmanType==2)
    {
        temp_string.append("background-color:#aaff88;color:#308000;");
    }
    //棋盘格上为防守点时，设置棋盘格背景为浅橙色，字体为暗橙色
    else if(chessmanType==3)
    {
        temp_string.append("background-color:#ffc981;color:#784400;");
    }
    //棋盘格上为障碍时，设置棋盘格背景为灰色，字体为黑色
    else if(chessmanType==4)
    {
        temp_string.append("background-color:#888888;color:#000000;");
    }

    //如果棋盘格被光标移动到或被选中，则设置边框为2px，红色
    if(beMovedTo||beSelected)
    {
        temp_string.append("border: 2px solid #ff0000;");
    }
    //否则设置边框为1px，浅灰色
    else
    {
        temp_string.append("border: 1px solid #c3c3c3;");
    }

    this->setStyleSheet(temp_string);
}

void Square::setSquareText()
{
    //如果棋盘格上无棋子，则设置棋盘格文字为空
    if(chessmanType==0)
    {
        setText("");
    }
    //如果棋盘格上为目标进攻区，则设置棋盘格文字为“目标”
    else if(chessmanType==1)
    {
        setText("目标");
    }
    //如果棋盘格上为棋子，则设置棋盘格文字为“棋子”
    else if(chessmanType==2)
    {
        setText("棋子");
    }
    //如果棋盘格上为防守点，则设置棋盘格文字为“防守点”
    else if(chessmanType==3)
    {
        setText("防守点");
    }
    //如果棋盘格上为障碍，则设置棋盘格文字为“障碍”
    else if(chessmanType==4)
    {
        setText("障碍");
    }

    //设置棋盘格文字居中
    setAlignment(Qt::AlignCenter);
}

//清空棋盘格内容，包括棋子ID，棋子类型，文字，背景及边框颜色
void Square::clearContent()
{
    setChessmanID(0);
    setChessmanType(0);
    setSquareText();
    cancelSelect();
}

//鼠标点击事件
void Square::mousePressEvent(QMouseEvent*)
{
    Q_EMIT signalMoveToSquare(squareID);//发射光标移动信号
    Q_EMIT signalSelectSquare(squareID);//发射选中棋盘格信号
}

#endif
