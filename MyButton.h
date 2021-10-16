#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>
#include<QEvent>
#include<QKeyEvent>

class MyButton : public QPushButton
{
public:
    MyButton(QWidget *parent=0);//构造函数
    //重写QPushButton的event函数，以免键盘事件被按钮监听到，使得用户无法通过键盘控制棋子
    bool event(QEvent *e);
};

#endif // MYBUTTON_H
