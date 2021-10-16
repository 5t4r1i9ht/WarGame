#ifndef CHESSMAN_CPP
#define CHESSMAN_CPP
#include "Chessman.h"

//构造函数
Chessman::Chessman(int _chessmanID, int _chessmanType, int _x, int _y, int _HP, int _attackRange, int _attackDamage)
{
    chessmanID=_chessmanID;
    chessmanType=_chessmanType;
    hasMoved=false;
    coordinate=new Coordinate(_x,_y);
    HP=_HP;
    hasDied=false;
    attackRange=_attackRange;
    attackDamage=_attackDamage;
}

//初始化
void Chessman::initChessman(int _chessmanID, int _chessmanType, int _x, int _y, int _HP, int _attackRange, int _attackDamage)
{
    chessmanID=_chessmanID;
    chessmanType=_chessmanType;
    hasMoved=false;
    setCoordinate(_x,_y);
    HP=_HP;
    attackRange=_attackRange;
    attackDamage=_attackDamage;
}

//获取x轴坐标
int Chessman::getX()
{
    return coordinate->getX();
}

//获取y轴坐标
int Chessman::getY()
{
    return coordinate->getY();
}

//获取棋子类型
int Chessman::getChessmanType()
{
    return chessmanType;
}

//设置棋子坐标
void Chessman::setCoordinate(int _x, int _y)
{
    coordinate->setCoordinate(_x,_y);
}

//获取棋子生命值
int Chessman::getHP()
{
    return HP;
}

//判断棋子能否移动到指定的坐标
bool Chessman::canMoveTo(int _x, int _y)
{
    //如果本回合内已经移动过则不能再移动
    if(hasMoved)
    {
        return false;
    }
    //如果x坐标相差1，y坐标相差0，即左或右一格则可以移动
    if(abs(coordinate->getX()-_x)==1&&abs(coordinate->getY()-_y)==0)
    {
        return true;
    }
    //如果y坐标相差1，x坐标相差0，即上或下一格则可以移动
    else if(abs(coordinate->getX()-_x)==0&&abs(coordinate->getY()-_y)==1)
    {
        return true;
    }
    //其他情况不能移动
    return false;
}

//获取棋子是否处于阵亡状态
bool Chessman::isDied()
{
    if(hasDied)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//设置棋子阵亡状态
void Chessman::goDied()
{
    hasDied=true;
}

//获取棋子本回合内是否移动的状态
bool Chessman::isMoved()
{
    return hasMoved;
}

//设置棋子本回合内已经移动过
void Chessman::setMoved()
{
    hasMoved=true;
}

//取消棋子移动状态
void Chessman::cancelMoved()
{
    hasMoved=false;
}

//获取防守点射程
int Chessman::getAttackRange()
{
    return attackRange;
}

//获取棋子攻击力
int Chessman::getAttackDamage()
{
    return attackDamage;
}

//判断防守点能否攻击指定的棋子
bool Chessman::canAttack(Chessman* _chessman)
{
    if(coordinate->getDistance(_chessman->coordinate)<=attackRange)
    {
        return true;
    }
    return false;
}

//防守点攻击指定的棋子
void Chessman::attack(Chessman* _chessman)
{
    _chessman->HP-=attackDamage;
}

#endif
