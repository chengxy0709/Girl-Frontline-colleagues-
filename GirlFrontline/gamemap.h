/*
 *  Filename: gamemap.h
 *  Author:   UbuntuCXY
 *  Email Address: 1484652026@qq.com
 *
 *  游戏地图类的头文件
 *  注释添加时间: 2020.7.7
 *
 *  函数说明:
 *
 *  GameMap(MapNo)
 *      实例化一个地图类，选择地图编号MapNo。
 *  generateMap(*parent)
 *      生成地图，选择父组件为parent。
 *  getMapElem(x, y)
 *      获取位置(x,y)（实地址）处的地图元素。
 *  canPass(MapElement elem)
 *      测试某一个地图元素是否可以通过。
 *  inMap(x, y)
 *      (x,y)是否在地图中。
 *  ~GameMap()
 *      析构函数。
 *
 *  变量说明:
 *
 *  MapNo       地图编号
 *  mapes       地图矩阵
 *  labels      显示地图单元图像的Label数组
 *  mapimgs     地图单元图像数组
 *
 *
 */

#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QWidget>
#include <QLabel>
#include <QVector>
#include <QImage>
#include <QPixmap>
#include <QString>

#include "mapinfo.h"

class GameMap{

public:
    GameMap(int MapNo = 1) : MapNo(MapNo){}

    void generateMap(QWidget *parent);
    MapElement getMapElem(int x, int y);
    bool canPass(MapElement elem);
    bool inMap(int x, int y);

    ~GameMap();

private:
    int MapNo;
    int mapes[MAPHEIGHT][MAPWIDTH];
    QVector< QVector<QLabel*> > labels;
    QVector<QImage*> mapimgs;

};

#endif // GAMEMAP_H

