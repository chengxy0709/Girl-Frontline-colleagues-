/*
 *  Filename: bullet.h
 *  Author:   UbuntuCXY
 *  Email Address: 1484652026@qq.com
 *
 *  子弹类的头文件
 *  注释添加时间: 2020.7.7
 *
 *  函数说明:
 *
 *  Bullet(x, y, dir, id, hurt, *gmap ,*parent)
 *      在实坐标(x, y)处实例化一枚朝向为dir，发射方ID为id，伤害为hurt的子弹，并且需要将地图
 *  地址gamp与窗口组件地址parent一并传入。
 *  getXpos()
 *      返回子弹中心位置X坐标（实坐标）。
 *  getYpos()
 *      返回子弹中心位置Y坐标（实坐标）。
 *  getSpeed()
 *      返回子弹实际速度。
 *  getID()
 *      返回子弹识别ID。
 *  gethurt()
 *      返回子弹伤害。
 *  update()
 *      更新子弹位置。
 *  ~Bullet()
 *      析构函数。
 *  move(delta, dir)
 *      将子弹向dir方向移动delta距离。
 *
 *  变量说明:
 *  x   子弹左上角X坐标（实坐标）
 *  y   子弹左上角Y坐标（实坐标）
 *  centerX     子弹中心X坐标（实坐标）
 *  centerY     子弹中心Y坐标（实坐标）
 *  dir         子弹方向
 *  ID          子弹ID，用于敌我子弹识别
 *  speed       子弹速度
 *  hurt        子弹伤害
 *  widget      游戏窗口主组件，实例化其他组件时需要在其基础上进行
 *  gmap        游戏地图地址
 *  label       用于显示子弹的Label
 *  img         子弹图像
 *
 *
 */

#ifndef BULLET_H
#define BULLET_H

#include <QString>
#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QMatrix>
#include <QCoreApplication>

#include "control.h"
#include "gamemap.h"

#define BULLETWIDTH 4       //子弹宽
#define BULLETLEN   20      //子弹长

class Bullet{

public:
    Bullet(int x, int y, DIRECTION dir, int id, int hurt,
           GameMap *gmap ,QWidget *parent = 0);

    int getXpos() const{return centerX;}
    int getYpos() const{return centerY;}
    int getSpeed() const{return speed;}
    int getID() const{return ID;}
    int gethurt() const{return hurt;}
    bool update();

    ~Bullet();

protected:
    void move(int delta, DIRECTION dir);

private:
    int x;
    int y;
    int centerX;
    int centerY;
    DIRECTION dir;
    int ID;
    int speed;
    int hurt;

    QWidget *widget;
    GameMap *gmap;
    QLabel *label;
    QImage *img;

};

#endif // BULLET_H

