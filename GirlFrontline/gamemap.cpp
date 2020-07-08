/*
 *  Filename: gamemap.cpp
 *  Author:   UbuntuCXY
 *  Email Address: 1484652026@qq.com
 *
 *  游戏地图类的实现文件
 *  注释添加时间: 2020.7.7
 *
 *  类成员函数说明见游戏地图类头文件
 *
 */

#include <QDebug>
#include "gamemap.h"

void GameMap::generateMap(QWidget *parent){

    labels = QVector< QVector<QLabel*> >(MAPHEIGHT, QVector<QLabel*>(MAPWIDTH, nullptr));

    for(int i = 0; i < static_cast<int>(TOTALNUM); ++i){
        QImage *image = new QImage("../picture/mape" + QString("%1").arg(i) + ".png");
        mapimgs.push_back(image);
    }
    for(int i = 0; i < MAPHEIGHT; ++i){
        for(int j = 0; j < MAPWIDTH; ++j){
            QLabel *label = new QLabel(parent);
            mapes[i][j] = Maps[MapNo][i][j];
            label->setPixmap(QPixmap::fromImage(*mapimgs[mapes[i][j]]));
            label->move(j * 50, i * 50);
            labels[i][j] = label;
        }
    }

}

MapElement GameMap::getMapElem(int x, int y){

    int tx,ty;
    tx = x / MAPUNITSZ;
    ty = y / MAPUNITSZ;

    return static_cast<MapElement>(mapes[ty][tx]);

}

bool GameMap::canPass(MapElement elem){

    if(elem == WALL || elem == RIVER)   return false;
    else return true;

}

bool GameMap::inMap(int x, int y){

    if(x >= 0 && x < MAPUNITSZ * MAPWIDTH &&
       y >= 0 && y < MAPHEIGHT * MAPUNITSZ)

        return true;
    else
        return false;

}

GameMap::~GameMap(){

    qDebug() << "delete game map\n";
    for(QVector<QLabel*>& p : labels){
        for(QLabel* q : p){
            delete q;
        }
    }
    for(QImage* p : mapimgs){
        delete p;
    }

}
