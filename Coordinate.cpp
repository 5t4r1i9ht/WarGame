#ifndef COORDINATE_CPP
#define COORDINATE_CPP

#include "Coordinate.h"

//构造函数
Coordinate::Coordinate(int _x,int _y)
{
    x=_x;
    y=_y;
}

//获取x坐标
int Coordinate::getX()
{
    return x;
}

//获取y坐标
int Coordinate::getY()
{
    return y;
}

//设置坐标
void Coordinate::setCoordinate(int _x, int _y)
{
    x=_x;
    y=_y;
}

//获取距离
double Coordinate::getDistance(Coordinate* _coordinate)
{
    return sqrt((x-_coordinate->x)*(x-_coordinate->x)+(y-_coordinate->y)*(y-_coordinate->y));
}

#endif
