/*
 *  Filename: bullet.cpp
 *  Author:   UbuntuCXY
 *  Email Address: 1484652026@qq.com
 *
 *  子弹类的实现文件
 *  注释添加时间: 2020.7.7
 *
 *  子函数说明（类成员函数说明见子弹类头文件）:
 *
 *  leftmove(*bullet, *gmap)
 *      尝试在地图gmap上向左移动，移动距离为子弹速度，若可以移动返回子弹速度，否则返回负值。
 *  rightmove(*bullet, *gmap)
 *      尝试在地图gmap上向右移动，移动距离为子弹速度，若可以移动返回子弹速度，否则返回负值。
 *  upmove(*bullet, *gmap)
 *      尝试在地图gmap上向上移动，移动距离为子弹速度，若可以移动返回子弹速度，否则返回负值。
 *  downmove(*bullet, *gmap)
 *      尝试在地图gmap上向下移动，移动距离为子弹速度，若可以移动返回子弹速度，否则返回负值。
 *
 */

#include "bullet.h"

Bullet::Bullet(int x, int y, DIRECTION dir, int id, int hurt, GameMap *gmap , QWidget *parent){

    this->x = x;
    this->y = y;
    this->ID = id;
    this->hurt = hurt;
    if(dir == UP || dir == DOWN){
        this->centerX = x + BULLETLEN / 2;
        this->centerY = y + BULLETWIDTH / 2;
    }
    else{
        this->centerX = x + BULLETWIDTH / 2;
        this->centerY = y + BULLETLEN / 2;
    }
    this->speed = MAPUNITSZ / 4;
    this->dir = dir;
    this->widget = parent;
    this->gmap = gmap;

    label = new QLabel(parent);
    img = new QImage("../picture/bullet.png");
    label->setGeometry(QRect(x, y, BULLETLEN, BULLETWIDTH));
    if(dir == UP || dir == DOWN){
        QMatrix matrix;
        matrix.rotate(90.0);
        *img = img->transformed(matrix,Qt::FastTransformation);
        label->setGeometry(QRect(x, y, BULLETWIDTH, BULLETLEN));
    }
    label->setPixmap(QPixmap::fromImage(*img));
    label->show();

}

inline int leftmove(Bullet *bullet, GameMap *gmap){

    int tempX = bullet->getXpos() - BULLETLEN / 2 - bullet->getSpeed();
    MapElement elem1 = gmap->getMapElem(tempX, bullet->getYpos() - BULLETWIDTH / 2);
    MapElement elem2 = gmap->getMapElem(tempX, bullet->getYpos() + BULLETWIDTH / 2 - 1);

    if( elem1 == WALL || elem2 == WALL || tempX < 0){
        return -1;
    }
    else {
        return bullet->getSpeed();
    }

}

inline int rightmove(Bullet *bullet, GameMap *gmap){

    int tempX = bullet->getXpos() + BULLETLEN / 2 + bullet->getSpeed() - 1;
    MapElement elem1 = gmap->getMapElem(tempX, bullet->getYpos() - BULLETWIDTH / 2);
    MapElement elem2 = gmap->getMapElem(tempX, bullet->getYpos() + BULLETWIDTH / 2 - 1);

    if( elem1 == WALL || elem2 == WALL || tempX >= MAPWIDTH * MAPUNITSZ - 1){
        return -1;
    }
    else {
        return bullet->getSpeed();
    }

}

inline int upmove(Bullet *bullet, GameMap *gmap){

    int tempY = bullet->getYpos() - BULLETLEN / 2 - bullet->getSpeed();
    MapElement elem1 = gmap->getMapElem(bullet->getXpos() - BULLETWIDTH / 2, tempY);
    MapElement elem2 = gmap->getMapElem(bullet->getXpos() + BULLETWIDTH / 2 - 1, tempY);

    if( elem1 == WALL || elem2 == WALL || tempY < 0){
        return -1;
    }
    else {
        return bullet->getSpeed();
    }

}

inline int downmove(Bullet *bullet, GameMap *gmap){

    int tempY = bullet->getYpos() + BULLETLEN / 2 + bullet->getSpeed() - 1;
    MapElement elem1 = gmap->getMapElem(bullet->getXpos() - BULLETWIDTH / 2, tempY);
    MapElement elem2 = gmap->getMapElem(bullet->getXpos() + BULLETWIDTH / 2 - 1, tempY);

    if( elem1 == WALL || elem2 == WALL || tempY >= MAPHEIGHT * MAPUNITSZ - 1){
        return -1;
    }
    else {
        return bullet->getSpeed();
    }

}

bool Bullet::update(){

    int delta = 0;
    switch (dir) {
    case LEFT:
    {
        delta = leftmove(this, gmap);
        move( delta, LEFT);
        break;
    }
    case RIGHT:
    {
        delta = rightmove(this, gmap);
        move( delta, RIGHT);
        break;
    }
    case UP:
    {
        delta = upmove(this, gmap);
        move( delta, UP);
        break;
    }
    case DOWN:
    {
        delta = downmove(this, gmap);
        move( delta, DOWN);
        break;
    }
    default:
        break;
    }

    if(delta < 0)
        return false;
    else
        return true;

}

void Bullet::move(int delta, DIRECTION dir){

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

Bullet::~Bullet(){

    delete img;
    delete label;

}

