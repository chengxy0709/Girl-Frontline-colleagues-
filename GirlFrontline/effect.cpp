/*
 *  Filename: effect.cpp
 *  Author:   UbuntuCXY
 *  Email Address: 1484652026@qq.com
 *
 *  特效类的实现文件
 *  注释添加时间: 2020.7.7
 *
 *  类成员函数说明见特效类头文件
 *
 */

#include "effect.h"

Effect::Effect(QWidget *parent) : QWidget(parent), stayTime(10), widget(parent)
{

}

Effect::Effect(int t, QWidget *parent) : QWidget(parent), stayTime(t), widget(parent)
{

}

void Effect::addEffect(int x, int y, int effectKind){

    switch (effectKind) {
    case BULLET1EFFECT:
    {
        QLabel *label = new QLabel(widget);
        QImage img("../picture/boom.png");
        label->setGeometry(QRect(x - 20, y - 20, 30, 30));
        label->setPixmap(QPixmap::fromImage(img));
        label->show();
        labels.append(QPair<QLabel*, int>(label, stayTime));
        break;
    }
    case BOOMEFFECT:
    {
        QLabel *label = new QLabel(widget);
        QImage img("../picture/boom2.png");
        label->setGeometry(QRect(x - 20, y - 20, 40, 40));
        label->setPixmap(QPixmap::fromImage(img));
        label->show();
        labels.append(QPair<QLabel*, int>(label, stayTime));
        break;
    }
    case COVERBOOM:
    {
        QLabel *label = new QLabel(widget);
        QImage img("../picture/coverboom.png");
        label->setGeometry(QRect(x - 75, y - 75, 150, 150));
        label->setPixmap(QPixmap::fromImage(img));
        label->show();
        labels.append(QPair<QLabel*, int>(label, stayTime));
        break;
    }
    default:
        break;
    }

}

void Effect::updateEffect(){
    for(QList< QPair<QLabel*, int> >::iterator p = labels.begin(); p != labels.end();){
        (*p).second--;
        if((*p).second <= 0){
            delete (*p).first;
            p = labels.erase(p);
        }
        else{
            p++;
        }
    }
}

Effect::~Effect()
{
    for(QPair<QLabel*, int>& effect : labels){
        delete effect.first;
    }
}

