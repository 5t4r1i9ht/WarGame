#ifndef WIDGET_CPP
#define WIDGET_CPP

#include "widget.h"
#include "Square.h"

Widget::Widget(QWidget *parent):QWidget(parent)
{
    Round=1;
    srand((int)time(NULL));
    initWidget();//初始化界面
    initGame();//初始化游戏
}

void Widget::initWidget()
{
    //设置主界面最小尺寸
    this->setMinimumSize(1080,550);

    //新建详细信息栏
    widgetDetails=new QWidget(this);

    //新建棋盘视图
    n=rand()%10+10;
    m=rand()%15+10;
    warGame=new WarGameWidget(n,m,this);

    //新建状态显示标签、回合显示标签
    labelShowStatus=new QLabel(widgetDetails);
    labelShowRound=new QLabel(widgetDetails);
    //设置回合显示标签的文字
    labelShowRound->setText(QString::number(Round));

    //新建结束回合按钮
    btnEndRound=new MyButton(widgetDetails);
    //设置按钮文字
    btnEndRound->setText("结束回合");
    //将按钮的点击信号与结束回合槽函数绑定
    connect(btnEndRound,SIGNAL(clicked(bool)),this,SLOT(sltEndRound()));
    connect(btnEndRound,SIGNAL(clicked(bool)),warGame,SLOT(sltEndRound()));

    //标签文字居中
    labelShowStatus->setAlignment(Qt::AlignLeft);
    labelShowRound->setAlignment(Qt::AlignCenter);

    //设置大小、文字及背景样式
    labelShowStatus->setStyleSheet("font:18px;");
    labelShowRound->setStyleSheet("background-color: #fb0;color: white; font: 64px;");
    labelShowRound->setMinimumWidth(180);
    labelShowRound->setMaximumHeight(120);
    btnEndRound->setStyleSheet("font:12px;");
    btnEndRound->setMaximumHeight(30);

    //新建垂直布局，将回合显示标签、状态显示标签、结束回合按钮添加到该布局
    verLayoutDetails=new QVBoxLayout(widgetDetails);
    verLayoutDetails->addWidget(labelShowRound);
    verLayoutDetails->addWidget(labelShowStatus);
    verLayoutDetails->addWidget(btnEndRound);

    //新建主界面水平布局，并将棋盘视图和详细信息栏添加到其中
    horLayoutWidget=new QHBoxLayout(this);
    horLayoutWidget->addWidget(widgetDetails);
    horLayoutWidget->addWidget(warGame,Qt::AlignCenter);

    //将棋盘格选中信号、游戏胜利信号、游戏失败信号与对应槽函数连接
    connect(warGame, SIGNAL(signalSelectSquare(int)), this, SLOT(sltSelectSquare(int)));
    connect(warGame,SIGNAL(signalWin()),this,SLOT(sltWin()));
    connect(warGame,SIGNAL(signalLose()),this,SLOT(sltLose()));
}

void Widget::initGame()
{
    //随机生成棋子、防守点、障碍数量
    k=rand()%n;
    if(k<3)
    {
        k=k+3;
    }
    g=rand()%n+1;
    d=rand()%5+5;
    b=rand()%5+4;
    //初始化游戏
    warGame->initGame(k,g,d,b);
}

//选中棋盘格槽函数，更新详细信息栏的信息
void Widget::sltSelectSquare(int _squareID)
{
    QString info="";
    info.append("第"+QString::number(Round)+"回合\n");
    info.append("坐标: ("+QString::number(warGame->square[_squareID]->getX())+","+QString::number(warGame->square[_squareID]->getY())+")\n");
    info.append("棋子类型: ");
    int _chessmanType=warGame->square[_squareID]->getChessmanType();
    int _chessmanID=warGame->square[_squareID]->getChessmanID();
    if(_chessmanType==0)
    {
        info.append("无\n");
    }
    else if(_chessmanType==1)
    {
        info.append("目标进攻区\n");
    }
    else if(_chessmanType==2)
    {
        info.append("棋子\n");
        info.append("生命值: "+QString::number(warGame->chessman[_chessmanID].getHP())+"\n");
        info.append("已移动: ");
        if(warGame->chessman[_chessmanID].isMoved())
        {
            info.append("是\n");
        }
        else
        {
            info.append("否\n");
        }
    }
    else if(_chessmanType==3)
    {
        info.append("防守点\n");
        info.append("射程: "+QString::number(warGame->chessman[_chessmanID].getAttackRange())+"\n");
        info.append("攻击力: "+QString::number(warGame->chessman[_chessmanID].getAttackDamage())+"\n");
    }
    else if(_chessmanType)
    {
        info.append("障碍\n");
    }
    labelShowStatus->setText(info);
}

//键盘事件
void Widget::keyPressEvent(QKeyEvent *e)
{
    int _beMovedToSquareID=warGame->currentSquareID;
    if(e->key()==Qt::Key_Left)//按下左方向键
    {
        Q_EMIT warGame->square[_beMovedToSquareID]->signalMoveToSquare(_beMovedToSquareID-1);//发射信号，参数为_num-1
    }
    else if(e->key()==Qt::Key_Right)//按下右方向键
    {
        Q_EMIT warGame->square[_beMovedToSquareID]->signalMoveToSquare(_beMovedToSquareID+1);//类别上面
    }
    else if(e->key()==Qt::Key_Up)//按下上方向键
    {
        Q_EMIT warGame->square[_beMovedToSquareID]->signalMoveToSquare(_beMovedToSquareID-m);
    }
    else if(e->key()==Qt::Key_Down)//按下下方向键
    {
        Q_EMIT warGame->square[_beMovedToSquareID]->signalMoveToSquare(_beMovedToSquareID+m);
    }
    else if(e->key()==Qt::Key_Return)//按下回车，选中棋盘格
    {
        Q_EMIT warGame->square[_beMovedToSquareID]->signalSelectSquare(_beMovedToSquareID);
    }
    else if(e->key()==Qt::Key::Key_Space)
    {
        Q_EMIT btnEndRound->clicked();
    }
}

//结束回合槽函数
void Widget::sltEndRound()
{
    Round++;
    labelShowRound->setText(QString::number(Round));
    labelShowStatus->clear();
}

//游戏胜利槽函数
void Widget::sltWin()
{
    //设置标签文字
    labelShowRound->setText("WIN");
    labelShowStatus->setText("你赢了！");
    //设置红色背景
    labelShowRound->setStyleSheet("background-color: #ff0000;color: white; font: 64px;");
    //禁用结束回合按钮
    btnEndRound->setDisabled(true);
}

//游戏失败槽函数
void Widget::sltLose()
{
    //设置标签文字
    labelShowRound->setText("LOSE");
    labelShowStatus->setText("你输了！");
    //设置灰色背景
    labelShowRound->setStyleSheet("background-color: #666666;color: white; font: 64px;");
    //禁用结束回合槽函数
    btnEndRound->setDisabled(true);
}

#endif
