/*
 *  Filename: figureinfo.h
 *  Author:   UbuntuCXY
 *  Email Address: 1484652026@qq.com
 *
 *  人形属性的头文件
 *  注释添加时间: 2020.7.7
 *
 *  相关说明:
 *
 *  FigureInfo: 定义一个人形的基本属性
 *
 */

#ifndef FIGUREINFO_H
#define FIGUREINFO_H

#include <QString>

struct FigureInfo{
    QString name;   //名字
    int speed;      //速度
    int hurt;       //伤害
    int bullet;     //弹量
    int life;       //生命值
    int department; //敌我识别ID
};


#define GELIFEN 1   // 格里芬阵营
#define TIEXUE  2   // 铁血阵营
#define JUNFANG 3   // 军方阵营

// 格里芬阵营人形编号
#define GELIFENMINNUM 1
#define M4A1 1
#define STAR15 2
#define GELIFENMAXNUM 2

// 铁血阵营人形编号
#define DIANFANBAO GELIFENMAXNUM + 1
#define HUFENG GELIFENMAXNUM + 2
#define LIEOU GELIFENMAXNUM + 3
#define LONGQIBIN GELIFENMAXNUM + 4
#define XUNYOUZHE GELIFENMAXNUM + 5
#define QIEGEZHE GELIFENMAXNUM + 6
#define GUIZISHOU  GELIFENMAXNUM + 7
#define FIGMAXNUM GELIFENMAXNUM + 7

// 人形属性表，顺序与编号一致
const FigureInfo FiguresData[] = {
   // name          speed   hurt    elastance   life    department
    {"ZERO",        50,     100,    100,        10000,  GELIFEN},
    {"M4A1",        20,     10,     10,         100,    GELIFEN},
    {"ST-AR15",     30,     11,     10,         90,     GELIFEN},
    {"dianfanbao",  25,     5,      1000,       70,     TIEXUE},
    {"hufeng",      25,     8,      1000,       80,     TIEXUE},
    {"lieou",       15,     12,     1000,       30,     TIEXUE},
    {"longqibin",   30,     10,     1000,       90,     TIEXUE},
    {"xunyouzhe",   40,     5,      1000,       60,     TIEXUE},
    {"qiegezhe",    25,     6,      1000,       110,    TIEXUE},
    {"guizishou",   15,     20,     1000,       1000,   TIEXUE},
};

#endif // FIGUREINFO_H

