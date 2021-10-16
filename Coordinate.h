#ifndef COORDINATE_H
#define COORDINATE_H

#include<cmath>

class Coordinate
{
public:
    Coordinate(int _x=0, int _y=0);//构造函数
    int getX();//获取x坐标
    int getY();//获取y坐标
    void setCoordinate(int _x,int _y);//设置坐标
    double getDistance(Coordinate* _coordinate);//获取距离
private:
    int x,y;//x，y坐标
};

#endif // COORDINATE_H
