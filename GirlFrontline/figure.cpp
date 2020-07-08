/*
 *  Filename: facility.cpp
 *  Author:   UbuntuCXY
 *  Email Address: 1484652026@qq.com
 *
 *  设施类的实现文件
 *  注释添加时间: 2020.7.7
 *
 *  子函数说明（类成员函数说明见设施类头文件）:
 *
 *  isBossforNo(No)
 *      返回编号位No人形是否位Boss
 *
 */


#include <QDebug>
#include <QFile>
#include "figure.h"

bool isBossforNo(int No){

    if(No == GUIZISHOU){
        return true;
    }
    else{
        return false;
    }

}

Figure::Figure(int fig, int x, int y, QWidget *parent, DIRECTION dir){
    if(fig < 0 || fig > FIGMAXNUM){
        qDebug() << "fig error\n";
    }

    this->x = x;
    this->y = y;
    this->centerX = x + MAPUNITSZ / 2;
    this->centerY = y + MAPUNITSZ / 2;
    this->figdata = FiguresData[fig];
    this->widget = parent;

    waitmovie[0] = new QMovie("../picture/" + figdata.name + "_wait_up.gif");
    waitmovie[1] = new QMovie("../picture/" + figdata.name + "_wait_left.gif");
    waitmovie[2] = new QMovie("../picture/" + figdata.name + "_wait_right.gif");
    waitmovie[3] = new QMovie("../picture/" + figdata.name + "_wait_down.gif");
    if(QFile("../picture/" + figdata.name + "_fire_left.gif").exists()){
        firemovie[0] = new QMovie("../picture/" + figdata.name + "_fire_up.gif");
        firemovie[1] = new QMovie("../picture/" + figdata.name + "_fire_left.gif");
        firemovie[2] = new QMovie("../picture/" + figdata.name + "_fire_right.gif");
        firemovie[3] = new QMovie("../picture/" + figdata.name + "_fire_down.gif");
    }
    else {
        firemovie[0] = waitmovie[0];
        firemovie[1] = waitmovie[1];
        firemovie[2] = waitmovie[2];
        firemovie[3] = waitmovie[3];
    }
    if(QFile("../picture/" + figdata.name + "_move_up.gif").exists()){
        movemovie[0] = new QMovie("../picture/" + figdata.name + "_move_up.gif");
        movemovie[1] = new QMovie("../picture/" + figdata.name + "_move_left.gif");
        movemovie[2] = new QMovie("../picture/" + figdata.name + "_move_right.gif");
        movemovie[3] = new QMovie("../picture/" + figdata.name + "_move_down.gif");
    }
    else {
        movemovie[0] = waitmovie[0];
        movemovie[1] = waitmovie[1];
        movemovie[2] = waitmovie[2];
        movemovie[3] = waitmovie[3];
    }
    if(isBossforNo(fig)) bossflag = true;
    else   bossflag = false;
    this->dir = dir;
    label = new QLabel(parent);
    label->setGeometry(QRect(x, y, MAPUNITSZ, MAPUNITSZ));
    label->show();
    setMovie(dir, ACT_WAIT);

    original_bullets = figdata.bullet;
    bulletTimeCounter = -1;
}

void Figure::move(int delta, DIRECTION dir){

    this->dir = dir;
    switch (dir) {
    case LEFT:
        x -= delta;
        centerX = x + MAPUNITSZ / 2;
        break;
    case RIGHT:
        x += delta;
        centerX = x + MAPUNITSZ / 2;
        break;
    case UP:
        y -= delta;
        centerY = y + MAPUNITSZ / 2;
        break;
    case DOWN:
        y += delta;
        centerY = y + MAPUNITSZ / 2;
        break;
    default:
        break;
    }
    label->move(x, y);

}

void Figure::setMovie(DIRECTION dir, int action){
    if(action == ACT_MOVE){
        label->setMovie(movemovie[static_cast<int>(dir)]);
        movemovie[static_cast<int>(dir)]->start();
    }
    else if(action == ACT_FIRE){
        label->setMovie(firemovie[static_cast<int>(dir)]);
        firemovie[static_cast<int>(dir)]->start();
    }
    else{
        label->setMovie(waitmovie[static_cast<int>(dir)]);
        waitmovie[static_cast<int>(dir)]->start();
    }
}

bool Figure::subBullet(){
    if(figdata.bullet > 0) {figdata.bullet--; return true;}
    else {return false;}
}

Figure::~Figure(){

    //qDebug() << "delete a enemy\n";
    if(waitmovie[0] != firemovie[0])
        for(QMovie *movie : firemovie)
            if(movie) delete movie;
    if(waitmovie[0] != movemovie[0])
        for(QMovie *movie : movemovie)
            if(movie) delete movie;
    for(QMovie *movie : waitmovie)
        if(movie) delete movie;
    if(label) delete label;

}

