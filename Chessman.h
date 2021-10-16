#ifndef CHESSMAN_H
#define CHESSMAN_H

#include"Coordinate.h"

class Chessman
{
public:
    Chessman(int _chessmanID=0,int _chessmanType=0,int _x=0,int _y=0,int _HP=0,int _attackRange=0,int _attackDamage=0);//构造函数
    void initChessman(int _chessmanID=0,int _chessmanType=0,int _x=0,int _y=0,int _HP=0,int _attackRange=0,int _attackDamage=0);//初始化
    int getX();//获取棋子的x坐标
    int getY();//获取棋子的y坐标
    int getChessmanType();//获取棋子类型
    void setCoordinate(int _x,int _y);//设置棋子坐标
    int getHP();//获取玩家棋子生命值
    bool canMoveTo(int _x,int _y);//判断玩家棋子能否移动到某个坐标
    bool isDied();//获取玩家棋子是否处于阵亡的状态
    void goDied();//设置玩家棋子阵亡状态
    bool isMoved();//返回玩家棋子在本回合内的移动状态
    void setMoved();//设置玩家棋子在本回合内已移动的状态
    void cancelMoved();//取消玩家棋子已移动状态
    int getAttackRange();//获取防守点射程
    int getAttackDamage();//获取防守点攻击力
    bool canAttack(Chessman* _chessman);//判断防守点能否攻击玩家棋子
    void attack(Chessman* _chessman);//防守点攻击玩家棋子

private:
    int chessmanID;//棋子ID，大于0，ID分配如下：1：目标进攻区，2~k+1：玩家棋子，k+2~k+1+d：防守点，k+2+d~k+1+d+b：障碍
    int chessmanType;//棋子类型，1：目标进攻区，2：玩家棋子，3:防守点，4：障碍
    Coordinate* coordinate;//棋子坐标
    int HP;//玩家棋子生命值，大于0，非玩家棋子此项为0
    bool hasMoved;//玩家棋子在本回合内是否已移动的状态，false：未移动，true：已移动
    bool hasDied;//玩家棋子是否处于阵亡的状态，false：已阵亡，true：未阵亡
    int attackRange;//攻击范围，即射程，大于0，非防守点此属性为0
    int attackDamage;//攻击伤害，即攻击力，大于0，非防守点此属性为0
};

#endif // CHESSMAN_H
