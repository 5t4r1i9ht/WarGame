#ifndef MYBUTTON_CPP
#define MYBUTTON_CPP

#include "MyButton.h"

MyButton::MyButton(QWidget *parent):QPushButton(parent){}

//重写QPushButton的event函数，以免键盘事件被按钮监听到，使得用户无法通过键盘控制棋子
bool MyButton::event(QEvent *e)
{
    if (e->type() == QEvent::KeyPress)
    {

        QKeyEvent *ke = (QKeyEvent *)(e);
        if (ke->key() == Qt::Key_Up)
        {
            return false;
        }
        else if(ke->key()==Qt::Key_Down)
        {
            return false;
        }
        else if(ke->key()==Qt::Key_Left)
        {
            return false;
        }
        else if(ke->key()==Qt::Key_Right)
        {
            return false;
        }
        else if(ke->key()==Qt::Key_Return)
        {
            return false;
        }
    }
    return QWidget::event(e);
}

#endif
