/*
 *  Filename: skill.cpp
 *  Author:   UbuntuCXY
 *  Email Address: 1484652026@qq.com
 *
 *  技能实现文件
 *  注释添加时间: 2020.7.7
 *
 *  函数说明技能头文件
 *
 */

#include "skill.h"

void coverboom(Figure *sender, Figure *receiver){

    int sx = sender->getXpos();
    int sy = sender->getYpos();
    int rx = receiver->getXpos();
    int ry = receiver->getYpos();

    if(sx - 75 <= rx && rx < sx + 75 &&
       sy - 75 <= ry && ry < sy + 75){
        receiver->sublife(1);
        receiver->subHurt(1);
    }

}
