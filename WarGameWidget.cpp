#ifndef WARGAMEWIDGET_CPP
#define WARGAMEWIDGET_CPP

#include "WarGameWidget.h"

//构造函数
WarGameWidget::WarGameWidget(int _n, int _m, QWidget *parent):QWidget(parent)
{
    n=_n;
    m=_m;
    selectedSquareID=0;
    currentSquareID=1;
    initWidget();
}

//初始化布局
void WarGameWidget::initWidget()
{
    this->setMinimumSize(440,380);//设置棋盘视图的最小尺寸

    //新建网格布局
    gridLayoutBody=new QGridLayout(this);
    gridLayoutBody->setHorizontalSpacing(0);
    gridLayoutBody->setVerticalSpacing(0);
    gridLayoutBody->setContentsMargins(0,0,0,0);

    //新建棋盘格数组
    square=new Square*[n*m+1];

    //初始化棋盘格，设置对应坐标、ID
    int index=1;
    for(int y=1;y<=n;y++)
    {
        for(int x=1;x<=m;x++)
        {
            square[index]=new Square(this);
            square[index]->setCoordinate(x,y);
            square[index]->setSquareID(index);
            square[index]->setChessmanID(0);
            square[index]->setChessmanType(0);
            //将棋盘格加到网格布局
            gridLayoutBody->addWidget(square[index],y-1,x-1);
            //逐个将棋盘格的点击信号与槽函数连接
            connect(square[index],SIGNAL(signalMoveToSquare(int)),this,SLOT(sltMoveToSquare(int)));
            connect(square[index],SIGNAL(signalSelectSquare(int)),this,SLOT(sltSelectSquare(int)));
            index++;
        }
    }
}

void WarGameWidget::initGame(int _k,int _g,int _d,int _b)
{
    k=_k;
    g=_g;
    d=_d;
    b=_b;

    //新建坐标
    allCoordinate=new Coordinate[n*m];
    //新建棋子
    chessman=new Chessman[k+g+d+b+1];

    int chessmanIndex=1,squareIndex;
    Coordinate* temp_coordinate;
    //右边空闲坐标集合
    set<Coordinate*> right;
    //全部空闲坐标集合
    set<Coordinate*> emptyCoordinate;

    for(int y=1;y<=n;y++)
    {
        for(int x=1;x<=m;x++)
        {
            //将坐标逐一添加到右边空闲坐标集合和全部空闲坐标集合
            temp_coordinate=&allCoordinate[(y-1)*m+x-1];
            if(x==m)
            {
                right.insert(temp_coordinate);
            }
            emptyCoordinate.insert(temp_coordinate);
        }
    }

    int temp_x,temp_y,temp_HP,temp_attackRange,temp_attackDamage;
    //目标进攻区初始化
    chessman[chessmanIndex].initChessman(chessmanIndex,1,1,g,0,0,0);
    temp_coordinate=&allCoordinate[(g-1)*m];
    emptyCoordinate.erase(temp_coordinate);
    chessmanIndex++;

    //棋子初始化
    for(int i=1;i<=k;i++)
    {
        //无可用坐标则退出坐标生成
        if(emptyCoordinate.empty()||right.empty())
        {
            break;
        }

        //随机生成y坐标
        temp_y=rand()%n+1;
        temp_coordinate=&allCoordinate[(temp_y)*m-1];

        //随机生成的坐标不在右边空闲坐标集合中则继续生成
        if(right.find(temp_coordinate)==right.end())
        {
            i--;
            continue;
        }
        //否则初始化棋子ID，坐标和生命值
        else
        {
            temp_HP=rand()%99+1;
            chessman[chessmanIndex].initChessman(chessmanIndex,2,m,temp_y,temp_HP,0,0);
            chessmanIndex++;
            //将棋子坐标从右边空闲坐标集合和全部空闲坐标集合移除
            right.erase(temp_coordinate);
            emptyCoordinate.erase(temp_coordinate);
        }
    }

    //防守点初始化
    for(int i=1;i<=d;i++)
    {
        //无可用坐标则退出坐标生成
        if(emptyCoordinate.empty())
        {
            break;
        }

        //随机生成x，y坐标
        temp_x=rand()%m+1;
        temp_y=rand()%n+1;
        temp_coordinate=&allCoordinate[(temp_y-1)*m+(temp_x-1)];

        //随机生成的坐标不在所有空闲坐标集合中
        if(emptyCoordinate.find(temp_coordinate)==emptyCoordinate.end())
        {
            i--;
            continue;
        }
        //否则初始化防守点ID，坐标，射程和攻击力
        else
        {
            temp_attackRange=rand()%5+1;
            temp_attackDamage=rand()%10+1;
            chessman[chessmanIndex].initChessman(chessmanIndex,3,temp_x,temp_y,0,temp_attackRange,temp_attackDamage);
            chessmanIndex++;
            //将棋子坐标从全部空闲坐标集合移除
            emptyCoordinate.erase(temp_coordinate);
        }
    }

    //初始化障碍
    for(int i=1;i<=b;i++)
    {
        //无可用坐标则退出坐标生成
        if(emptyCoordinate.empty())
        {
            break;
        }

        //随机生成x，y坐标
        temp_x=rand()%m+1;
        temp_y=rand()%n+1;
        temp_coordinate=&allCoordinate[(temp_y-1)*m+(temp_x-1)];

        //随机生成的坐标不在所有空闲坐标集合中
        if(emptyCoordinate.find(temp_coordinate)==emptyCoordinate.end())
        {
            i--;
            continue;
        }
        //否则初始化防守点ID和坐标
        else
        {
            chessman[chessmanIndex].initChessman(chessmanIndex,4,temp_x,temp_y,0,0,0);
            chessmanIndex++;
            //将棋子坐标从全部空闲坐标集合移除
            emptyCoordinate.erase(temp_coordinate);
        }
    }

    //初始化棋子对应的棋盘格
    for(int i=1;i<chessmanIndex;i++)
    {
        temp_x=chessman[i].getX();
        temp_y=chessman[i].getY();
        squareIndex=(temp_y-1)*m+(temp_x-1)+1;
        square[squareIndex]->setChessmanID(i);
        square[squareIndex]->setChessmanType(chessman[i].getChessmanType());
    }
}

//光标移动到棋盘格槽函数，能处理键盘事件，不用处理键盘事件的话不用那么复杂
void WarGameWidget::sltMoveToSquare(int _squareID)
{
    if(_squareID==n*m+1)
    {
        if(currentSquareID==n*m)
        {
            _squareID=1;
        }
        else
        {
            _squareID=2;
        }
    }
    else if(_squareID==n*m+m)
    {
        _squareID=1;
    }
    else if(_squareID>n*m)
    {
        _squareID=_squareID%(n*m)+1;
    }
    else if(_squareID<=0)
    {
        if(_squareID==0)
        {
            if(currentSquareID==1)
            {
                _squareID=n*m;
            }
            else if(currentSquareID==m)
            {
                _squareID=n*m-1;
            }
        }
        else if(_squareID==1-m)
        {
            _squareID=n*m;
        }
        else
        {
            _squareID=n*m+_squareID-1;
        }
    }

    if(currentSquareID==0)
    {
        currentSquareID=_squareID;
    }
    else
    {
        square[currentSquareID]->cancelMove();
        currentSquareID=_squareID;
        square[currentSquareID]->setMovedTo();
    }
}

//选中棋盘格槽函数
void WarGameWidget::sltSelectSquare(int _squareID)
{
    int chessmanTypeOnSquare=square[selectedSquareID]->getChessmanType();
    int chessmanIDOnSquare=square[selectedSquareID]->getChessmanID();
    //先前无选中棋盘格
    if(selectedSquareID==0)
    {
        selectedSquareID=_squareID;
        square[selectedSquareID]->setSelected();
    }
    //先前选中了用户棋子所在的棋盘格
    else if(chessmanTypeOnSquare==2)
    {
        int next_x=square[_squareID]->getX();
        int next_y=square[_squareID]->getY();
        int nextSquareID=(next_y-1)*m+(next_x);
        //能移动到新坐标且新坐标上无棋子
        if(chessman[chessmanIDOnSquare].canMoveTo(next_x,next_y)&&(square[nextSquareID]->getChessmanType()==0))
        {
            chessman[chessmanIDOnSquare].setCoordinate(next_x,next_y);
            square[_squareID]->setChessmanID(square[selectedSquareID]->getChessmanID());
            square[_squareID]->setChessmanType(square[selectedSquareID]->getChessmanType());
            square[selectedSquareID]->clearContent();
            selectedSquareID=_squareID;
            square[selectedSquareID]->setSquareText();
            square[selectedSquareID]->setSelected();
            chessman[chessmanIDOnSquare].setMoved();
        }
        //能移动到新坐标且新坐标上为目标进攻区
        else if(chessman[chessmanIDOnSquare].canMoveTo(next_x,next_y)&&(square[nextSquareID]->getChessmanType()==1))
        {
            chessman[chessmanIDOnSquare].setCoordinate(next_x,next_y);
            square[_squareID]->setChessmanID(square[selectedSquareID]->getChessmanID());
            square[_squareID]->setChessmanType(square[selectedSquareID]->getChessmanType());
            square[selectedSquareID]->clearContent();
            selectedSquareID=_squareID;
            square[selectedSquareID]->setSquareText();
            square[selectedSquareID]->setSelected();
            chessman[chessmanIDOnSquare].setMoved();
            Q_EMIT signalWin();//发射胜利信号，噢耶
        }
        //新坐标上有其他棋子则选中新棋盘格
        else
        {
            square[selectedSquareID]->cancelSelect();
            selectedSquareID=_squareID;
            square[selectedSquareID]->setSelected();
        }
    }
    //先前选中了其他棋子或无棋子的棋盘格则取消原先选中的棋盘格的选中状态并设置新选中棋盘格的选中状态
    else
    {
        square[selectedSquareID]->cancelSelect();
        selectedSquareID=_squareID;
        square[selectedSquareID]->setSelected();
    }
    //向主界面发射棋盘格选中信号
    Q_EMIT signalSelectSquare(_squareID);
}

//结束回合槽函数
void WarGameWidget::sltEndRound()
{
    int _squareID;
    allDied=true;

    //若先前有选中棋盘格则取消选中
    if(selectedSquareID!=0)
    {
        square[selectedSquareID]->cancelSelect();
        square[selectedSquareID]->cancelMove();
    }

    if(currentSquareID!=0)
    {
        square[currentSquareID]->cancelMove();
    }

    currentSquareID=1;
    selectedSquareID=0;
    //伤害判定
    for(int i=k+2;i<=k+d+1;i++)
    {
        for(int j=2;j<=k+1;j++)
        {
            //用户棋子还没阵亡的话
            if(!chessman[j].isDied())
            {
                //取消用户棋子移动状态
                chessman[j].cancelMoved();
                //判断防守点能否攻击用户棋子
                if(chessman[i].canAttack(&chessman[j]))
                {
                    //能的话就攻击
                    chessman[i].attack(&chessman[j]);
                    //如果用户棋子生命值小于等于0则设置阵亡状态并清空对应棋盘格
                    if(chessman[j].getHP()<=0)
                    {
                        chessman[j].goDied();
                        _squareID=(chessman[j].getY()-1)*m+chessman[j].getX();
                        square[_squareID]->clearContent();
                    }
                }
            }
        }
    }
    //判断是否团灭
    for(int j=2;j<=k+1;j++)
    {
        if(!chessman[j].isDied())
        {
            allDied=false;
            break;
        }
    }
    //是的话发射游戏失败信号
    if(allDied)
    {
        Q_EMIT signalLose();//啊噢，你输了
    }
}

#endif
