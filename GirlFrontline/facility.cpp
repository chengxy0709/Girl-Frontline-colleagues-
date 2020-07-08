/*
 *  Filename: facility.cpp
 *  Author:   UbuntuCXY
 *  Email Address: 1484652026@qq.com
 *
 *  设施类的实现文件
 *  注释添加时间: 2020.7.7
 *
 *  类成员函数说明见设施类头文件
 *
 */

#include <QDebug>
#include "facility.h"

Facility::Facility(QWidget *parent) : QWidget(parent), widget(parent)
{
    x = 0;  y = 0;
    label = new QLabel(parent);
    label->setGeometry(QRect(0, 0, MAPUNITSZ, MAPUNITSZ));
}

Facility::Facility(int x, int y, QWidget *parent, bool abnormal) :
    widget(parent){

    if(abnormal){
        this->x = x * MAPUNITSZ;
        this->y = y * MAPUNITSZ;
    }
    else{
        this->x = x;
        this->y = y;
    }
    label = new QLabel(parent);
    label->setGeometry(QRect(this->x, this->y, MAPUNITSZ, MAPUNITSZ));

}

void Facility::setImage(const QString &filepath, bool mirror, int rotate){

    QImage img(filepath);
    QMatrix mat;
    if(mirror) img = img.mirrored(true, false);
    mat.rotate(rotate);
    label->setPixmap(QPixmap::fromImage(img).transformed(mat, Qt::SmoothTransformation));
    label->show();

}

Facility::~Facility()
{
    delete label;
}

Airport::Airport(QWidget *parent) : Facility(parent)
{
    setImage("../picture/airport.png");
}

Airport::Airport(int x, int y, QWidget *parent) : Facility(x, y, parent)
{
    setImage("../picture/airport.png");
}

Airport::Airport(int x, int y, QList<int>& enemiesList, QWidget *parent) :
    Facility(x, y, parent)
{
    setImage("../picture/airport.png");
    enemiesNo = enemiesList;\
}

FigPosInfo* Airport::putOneEnemyInfo(){

    if(enemiesNo.size() == 0) return nullptr;

    FigPosInfo *info = new FigPosInfo;
    info->dir = static_cast<DIRECTION>(rand() % 4);
    info->No = enemiesNo.back();
    enemiesNo.pop_back();
    info->x = getXpos();
    info->y = getYpos();

    return info;

}

Airport::~Airport(){

}

BombBase::BombBase(QWidget *parent) : Facility(parent)
{
    setImage("../picture/bombbase.png");
}

BombBase::BombBase(int x, int y, QWidget *parent) : Facility(x, y, parent)
{
    setImage("../picture/bombbase.png");
}

bool BombBase::tryGet(int x, int y){

    if( getXpos() - 35 < x && x < getXpos() + 35 &&
        getYpos() - 35 < y && y < getYpos() + 35){
        return true;
    }
    else
        return false;

}

BombBase::~BombBase(){

}

Bomb::Bomb(QWidget *parent) : Facility(parent)
{
    setImage("../picture/bomb.png");
}

Bomb::Bomb(int x, int y, QWidget *parent) :
    Facility(x - MAPUNITSZ / 2, y - MAPUNITSZ / 2, parent, false)
{
    setImage("../picture/bomb.png");
}

bool Bomb::tryBoom(Figure *fig){

    int x = fig->getXpos();
    int y = fig->getYpos();
    if( getXpos() - 35 < x + 25 && x < getXpos() + 35 &&
        getYpos() - 35 < y && y < getYpos() + 35){

        fig->sublife(fig->getLife() / 2);
        fig->subHurt(fig->getHurt() / 2);
        return true;
    }
    else
        return false;

}

Bomb::~Bomb(){

}

Pillbox::Pillbox(QWidget *parent) : Facility(parent)
{
    fire = true;
    hurt = 40;
    dir = LEFT;
    ID = TIEXUE;
    setImage("../picture/pillbox.png");
}

Pillbox::Pillbox(int x, int y, DIRECTION dir, int ID, QWidget *parent) :
    Facility(x, y, parent), dir(dir), ID(ID)
{
    fire = true;
    hurt = 40;
    if(dir == RIGHT) setImage("../picture/pillbox.png", true);
    else if(dir == UP) setImage("../picture/pillbox.png", true, 270);
    else if(dir == DOWN) setImage("../picture/pillbox.png", false, 270);
    else  setImage("../picture/pillbox.png", false);
}

Pillbox::~Pillbox(){

}

Cage::Cage(QWidget *parent) : Facility(parent)
{
    setImage("../picture/savefig.png");
    saved = false;
}

Cage::Cage(int x, int y, QWidget *parent) : Facility(x, y, parent)
{
    setImage("../picture/savefig.png");
    saved = false;
}

bool Cage::trySave(int x, int y){

    if(saved) return false;

    if( getXpos() - 35 < x && x < getXpos() + 35 &&
        getYpos() - 35 < y && y < getYpos() + 35){

        saved = true;
        setImage("../picture/cage.png");
        return true;

    }
    else {
        return false;
    }

}

Cage::~Cage(){

}

Radar::Radar(QWidget *parent) : Facility(parent)
{
    setImage("../picture/radar.png");
    running = false;
    used = false;
}

Radar::Radar(int x, int y, QWidget *parent) : Facility(x, y, parent)
{
    setImage("../picture/radar.png");
    running = false;
    used = false;
}

int Radar::tryStart(int x, int y, QList<Pillbox*>& pillpoxs){

    if(running) return -1;

    if( getXpos() - 35 < x && x < getXpos() + 35 &&
        getYpos() - 35 < y && y < getYpos() + 35){

        running = true;
        QStringList items;
        for(Pillbox *pillbox : pillpoxs){
            items << "井盖[ " + QString::number(pillbox->getXpos() / MAPUNITSZ) +
                     " ," + QString::number(pillbox->getYpos() / MAPUNITSZ) + " ]";
        }

        bool ok{false};
        QString item = QInputDialog::getItem(this, "雷达控制台", "请选择要破坏的井盖", items,
                              0, false, &ok);

        if(ok && !item.isEmpty()){
            return items.indexOf(item);
        }
        else{
            return -1;
        }

    }
    else{
        return -1;
    }

}

void Radar::tryStop(int x, int y){

    if( getXpos() - 35 >= x || x >= getXpos() + 35 ||
        getYpos() - 35 >= y || y >= getYpos() + 35){
        running = false;
    }

}

Radar::~Radar(){

}
