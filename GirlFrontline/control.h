/*
 *  Filename: control.h
 *  Author:   UbuntuCXY
 *  Email Address: 1484652026@qq.com
 *
 *  控制相关的头文件
 *  注释添加时间: 2020.7.7
 *
 *  相关说明:
 *
 *  DIRECTION: 定义了方向的枚举类型
 *  FigPosInfo: 定义人形一个位置相关结构体
 *
 */

#ifndef CONTROL_H
#define CONTROL_H

enum DIRECTION{
    UP = 0,
    LEFT = 1,
    RIGHT = 2,
    DOWN = 3,
};

struct FigPosInfo{
    int No; // 人形编号，参考figureinfo.h
    int x;  // 人形在地图上其中心位置X坐标（实坐标）
    int y;  // 人形在地图上其中心位置Y坐标（实坐标）
    DIRECTION dir;  // 人形的朝向
};

#endif // CONTROL_H

