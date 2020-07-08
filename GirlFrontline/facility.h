/*
 *  Filename: facility.h
 *  Author:   UbuntuCXY
 *  Email Address: 1484652026@qq.com
 *
 *  设施类的头文件
 *  注释添加时间: 2020.7.7
 *
 *  函数说明:
 *
 *  Facility(*parent)
 *      实例化一个设施类，其私有变量使用默认值，parent指定特效显示组件的父组件。
 *  Facility(x, y, *parent, adnormal)
 *      在位置(x,y)处实例化一个设施类，parent指定特效显示组件的父组件，abnormal若为false表示位置
 *  为实地址，否则为虚地址，默认使用虚地址。
 *  setImage(filepath, mirror, rotate)
 *      设置设施图片，图片地址为filepath，若mirror为true则将该图片水平镜像翻转，默认不翻转，若指
 *  定rotate，则将图片顺时针旋转rotate度，默认不旋转。
 *  getXpos()
 *      获取设施中心位置X坐标（实坐标）。
 *  getYpos()
 *      获取设施中心位置Y坐标（实坐标）。
 *  ~Facility();
 *      析构函数。
 *
 *  变量说明:
 *
 *  x       设施左上角X坐标（实坐标）
 *  y       设施左上角Y坐标（实坐标）
 *  widget  父组件地址
 *  label   显示设施的Label
 *
 *  设施类的派生类说明（具体说明参考其详细介绍）:
 *  Airport     飞机场，可以产生敌人
 *  BombBase    用于存放一个地雷
 *  Bomb        地雷
 *  Pillbox     碉堡
 *  Cage        囚笼
 *  Radar       雷达
 *
 */

#ifndef FACILITY_H
#define FACILITY_H

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QMatrix>
#include <QList>
#include <QInputDialog>
#include <stdlib.h>

#include "gamemap.h"
#include "control.h"
#include "figure.h"

#define AIRPORT 1           //飞机场
#define BOMBBASE  2         //存放地雷设施
#define BOMB  3             //地雷
#define PILLBOX 4           //碉堡
#define CAGE    5           //囚笼
#define RADAR   6           //雷达
#define FACILITYKINDNUM 6   //设施种类数

class Facility : public QWidget
{
    Q_OBJECT
public:
    explicit Facility(QWidget *parent = 0);
    Facility(int x, int y, QWidget *parent, bool adnormal = true);

    void setImage(const QString& filepath, bool mirror = false, int rotate = 0);
    int getXpos() const {return x + MAPUNITSZ / 2;}
    int getYpos() const {return y + MAPUNITSZ / 2;}

    ~Facility();

signals:

public slots:

private:
    int x;
    int y;

    QWidget *widget;
    QLabel *label;

};

/*
 *  飞机场类
 *
 *  函数说明:
 *
 *  Airport(*parent)
 *      实例化一个飞机场类，其私有变量使用默认值，parent指定特效显示组件的父组件。
 *  Airport(x, y, *parent)
 *      在位置(x,y)（实坐标）处实例化一个飞机场类，其余私有变量使用默认值，parent指定特效显示组件
 *  的父组件。
 *  Airport(x, y, enemiesList, *parent)
 *      在位置(x,y)（实坐标）处实例化一个飞机场类，其私有变量使用默认值，parent指定特效显示组件的
 *  父组件，enemiesList指定飞机场生成敌人的编号。
 *  putOneEnemyInfo()
 *      在自身位置处生成一个编号为enemiesNo.back()的敌人，其朝向随机，并将这些信息组织为一个结构体
 *  FigPosInfo，返回其地址。
 *  remainNum()
 *      返回飞机场还剩多少敌人未生成。
 *  ~Airport()
 *      析构函数。
 *
 *  变量说明:
 *
 *  enemiesNo 飞机场待生成敌人编号列表，每次从其末尾取一个编号
 *
 */

class Airport : public Facility
{

    Q_OBJECT
public:
    explicit Airport(QWidget *parent = 0);
    Airport(int x, int y, QWidget *parent);
    Airport(int x, int y, QList<int>& enemiesList, QWidget *parent);

    FigPosInfo* putOneEnemyInfo();
    int remainNum() const {return enemiesNo.size();}

    ~Airport();

signals:

public slots:

private:
    QList<int> enemiesNo;

};

/*
 *  存放地雷设施类
 *
 *  函数说明:
 *
 *  BombBase(*parent)
 *      实例化一个存放地雷设施类，parent指定特效显示组件的父组件。
 *  BombBase(x, y, *parent)
 *      在位置(x,y)（实坐标）处实例化一个存放地雷设施类，parent指定特效显示组件的父组件。
 *  tryGet(x, y)
 *      在位置(x,y)（实坐标）处尝试获取地雷，成功返回true，否则返回false。
 *  ~BombBase()
 *      析构函数。
 *
 */

class BombBase : public Facility
{

    Q_OBJECT
public:
    explicit BombBase(QWidget *parent = 0);
    BombBase(int x, int y, QWidget *parent);

    bool tryGet(int x, int y);

    ~BombBase();

signals:

public slots:

private:

};

/*
 *  地雷设施类
 *
 *  函数说明:
 *
 *  Bomb(*parent)
 *      实例化一个地雷设施类，parent指定特效显示组件的父组件。
 *  Bomb(x, y, *parent)
 *      在位置(x,y)（实坐标）处实例化一个地雷设施类，parent指定特效显示组件的父组件。
 *  tryBoom(*fig)
 *      尝试对人形fig进行爆破，成功减掉fig一定的血量和攻击力，同时返回true，否则返回false。
 *  ~Bomb()
 *      析构函数。
 *
 */

class Bomb : public Facility
{

    Q_OBJECT
public:
    explicit Bomb(QWidget *parent = 0);
    Bomb(int x, int y, QWidget *parent);

    bool tryBoom(Figure *fig);

    ~Bomb();

signals:

public slots:

private:

};

/*
 *  碉堡类
 *
 *  函数说明:
 *
 *  Pillbox(*parent)
 *      实例化一个碉堡类，parent指定特效显示组件的父组件。
 *  Pillbox(x, y, dir, ID, *parent)
 *      在位置(x,y)（实坐标）处实例化一个碉堡类，parent指定特效显示组件的父组件，并指定其朝向dir以及
 *  敌我识别ID。
 *  SetStopFire()
 *      设置碉堡停止攻击。
 *  isFire()
 *      返回碉堡是否在开火，true表示仍在开火。
 *  getHurt()
 *      返回碉堡伤害。
 *  getDirection()
 *      返回碉堡朝向。
 *  getID()
 *      返回碉堡敌我识别ID。
 *  ~Pillbox()
 *      析构函数。
 *
 *  变量说明
 *  fire    碉堡开火标志，true(开火)
 *  hurt    碉堡伤害
 *  dir     碉堡朝向
 *  ID      碉堡敌我识别ID
 *
 */

class Pillbox : public Facility
{

    Q_OBJECT
public:
    explicit Pillbox(QWidget *parent = 0);
    Pillbox(int x, int y, DIRECTION dir, int ID, QWidget *parent);

    void SetStopFire(){fire = false;}
    bool isFire() const {return fire;}
    int getHurt() const{return hurt;}
    DIRECTION getDirection() const {return dir;}
    int getID() const{return ID;}

    ~Pillbox();

signals:

public slots:

private:
    bool fire;
    int hurt;
    DIRECTION dir;
    int ID;

};

/*
 *  囚笼类
 *
 *  函数说明:
 *
 *  Cage(*parent)
 *      实例化一个囚笼类，parent指定特效显示组件的父组件。
 *  Cage(x, y, *parent)
 *      在位置(x,y)（实坐标）处实例化一个囚笼类，parent指定特效显示组件的父组件。
 *  trySave(int x, int y)
 *      尝试解救囚笼中的人质，成功返回true，否则false。
 *  isSaved()
 *      返回囚笼中的人是否已解救。
 *  ~Cage()
 *      析构函数。
 *
 *  变量说明
 *  saved    人质已解救标志，true(已解救)
 *
 */

class Cage : public Facility
{

    Q_OBJECT
public:
    explicit Cage(QWidget *parent = 0);
    Cage(int x, int y, QWidget *parent);

    bool trySave(int x, int y);
    bool isSaved() const{return saved;}

    ~Cage();

signals:

public slots:

private:
    bool saved;

};

/*
 *  雷达类
 *
 *  函数说明:
 *
 *  Radar(*parent)
 *      实例化一个雷达类，parent指定特效显示组件的父组件。
 *  Radar(x, y, *parent)
 *      在位置(x,y)（实坐标）处实例化一个雷达类，parent指定特效显示组件的父组件。
 *  tryStart(x, y, pillpoxs)
 *      在位置(x,y)（实坐标）处尝试启动雷达，如果启动成功，在pillpoxs中选择一个要破化的碉堡，并
 *  返回true，否则返回false。
 *  tryStop(x, y)
 *      在位置(x,y)（实坐标）处尝试关闭雷达，如果关闭成功，返回true，否则返回false。
 *  setUsed()
 *      设置雷达已被用过。
 *  isUsed()
 *      返回雷达是否已经被使用过。
 *  ~Radar()
 *      析构函数。
 *
 *  变量说明
 *
 *  running 雷达正在使用标志
 *  used    雷达已被使用过标志
 *
 */

class Radar : public Facility
{

    Q_OBJECT
public:
    explicit Radar(QWidget *parent = 0);
    Radar(int x, int y, QWidget *parent);

    int tryStart(int x, int y, QList<Pillbox*>& pillpoxs);
    void tryStop(int x, int y);

    void setUsed(){used = true;}
    bool isUsed() const{return used;}

    ~Radar();

signals:

public slots:

private:
    bool running;
    bool used;

};

#endif // FACILITY_H
