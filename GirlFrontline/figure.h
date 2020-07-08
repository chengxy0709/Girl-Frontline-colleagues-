/*
 *  Filename: figure.h
 *  Author:   UbuntuCXY
 *  Email Address: 1484652026@qq.com
 *
 *  人形类的头文件
 *  注释添加时间: 2020.7.7
 *
 *  函数说明:
 *
 *  Figure(fig, x, y, *parent, dir)
 *      在位置(x,y)处实例化一个人形类，编号为fig，parent指定特效显示组件的父组件，朝向为dir，
 *  默认为右。
 *  move(delta, dir)
 *      人形向dir方向移动delta距离。
 *  isHidden()
 *      人形是否处于隐藏状态
 *  setHidden(sta)
 *      设置人形隐藏状态为sta。
 *  isWait()
 *      人形是否处于等待状态。
 *  setWait(sta)
 *      设置人形等待状态为sta。
 *  isFire()
 *      人形是否处于开火状态。
 *  setFire(sta)
 *      设置人形开火状态为sta。
 *  isSlow()
 *      人形是否处于减速状态。
 *  setSlow(sta)
 *      设置人形减速状态为sta。
 *  getXpos()
 *      返回人形中心位置X坐标（实坐标）。
 *  getYpos()
 *      返回人形中心位置Y坐标（实坐标）。
 *  getSpeed()
 *      返回人形速度。
 *  getDirection()
 *      返回人形朝向。
 *  getID()
 *      返回人形敌我识别ID。
 *  getLife()
 *      返回人形生命值。
 *  sublife(v)
 *      将人形生命值减v。
 *  getHurt()
 *      返回人形伤害。
 *  subBullet()
 *      人形弹量减一。
 *  addBullet()
 *      恢复人形弹量。
 *  subHurt(v)
 *      人形伤害减v。
 *  getBulletNum()
 *      获取人形剩余弹量。
 *  isBoss()
 *      人形是否为Boss单位。
 *  setMovie(dir, action)
 *      设置人形动画，动作为action，方向为dir。
 *  ~Figure()
 *      析构函数。
 *
 *  变量说明:
 *
 *  bulletTimeCounter   换弹时间计数器
 *  x                   人形左上角X坐标（实坐标）
 *  y                   人形左上角Y坐标（实坐标）
 *  centerX             人形中心位置X坐标（实坐标）
 *  centerY             人形中心位置Y坐标（实坐标）
 *  original_bullets    人形最大弹量数
 *  dir                 人形朝向
 *  state               人形状态
 *  figdata             人形属性结构体
 *  bossflag            Boss标志
 *  widget              父组件地址
 *  label               显示人形的Label
 *  firemovie           人形开火动画
 *  waitmovie           人形等待动画
 *  movemovie           人形移动动画
 *
 */


#ifndef FIGURE_H
#define FIGURE_H

#include <QString>
#include <QWidget>
#include <QLabel>
#include <QMovie>
#include <QImage>

#include "figureinfo.h"
#include "gamemap.h"
#include "control.h"


#define FIGWAIT 0x00000001  //等待标志位
#define FIGFIRE 0x00000002  //开火标志位
#define FIGHIDE 0x00000004  //隐藏标志位
#define FIGSLOW 0x00000008  //减速标志位

#define ACT_WAIT 0      //等待
#define ACT_MOVE 1      //移动
#define ACT_FIRE 2      //开火

class Figure : public QObject{

    //Q_OBJECT

public:
    Figure(int fig, int x, int y, QWidget *parent = 0, DIRECTION dir = RIGHT );

    void move(int delta, DIRECTION dir);

    bool isHidden() const {return state & FIGHIDE;}
    void setHidden(bool sta) {
        if(sta){ state = FIGHIDE | state; label->setHidden(true);}
        else {state = (~FIGHIDE) & state; label->setHidden(false);}
    }
    bool isWait() const {return state & FIGWAIT;}
    void setWait(bool sta) {
        if(sta) state = FIGWAIT | state;
        else state = (~FIGWAIT) & state;
    }
    bool isFire() const {return state & FIGFIRE;}
    void setFire(bool sta) {
        if(sta) state = FIGFIRE | state;
        else state = (~FIGFIRE) & state;
    }
    bool isSlow() const {return state & FIGSLOW;}
    void setSlow(bool sta) {
        if(sta) state = FIGSLOW | state;
        else state = (~FIGSLOW) & state;
    }
    int getXpos() const{return centerX;}
    int getYpos() const{return centerY;}
    int getSpeed() const{
        if(isSlow()) return figdata.speed / 4;
        else return figdata.speed;
    }
    DIRECTION getDirection() const{return dir;}
    int getID() const {return figdata.department;}
    int getLife() const {return figdata.life;}
    bool sublife(int v){
        if(figdata.life > v) {figdata.life -= v; return true;}
        else {figdata.life = 0; return false;}
    }
    int getHurt() const {return figdata.hurt;}
    bool subBullet();
    void addBullet(){figdata.bullet = original_bullets;}
    void subHurt(int v){
        if(figdata.hurt > v) {figdata.hurt -= v;}
        else {figdata.hurt = 1;}
    }
    int getBulletNum() const {return figdata.bullet;}

    bool isBoss() const {return bossflag;}

    void setMovie(DIRECTION dir, int action);

    int bulletTimeCounter;

    ~Figure();

private:
    int x;
    int y;
    int centerX;
    int centerY;
    int original_bullets;
    DIRECTION dir;
    unsigned int state;
    FigureInfo figdata;
    bool bossflag;

    QWidget *widget;
    QLabel *label;
    QMovie *firemovie[4];
    QMovie *waitmovie[4];
    QMovie *movemovie[4];

};

#endif // FIGURE_H

