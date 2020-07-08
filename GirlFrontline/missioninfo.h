/*
 *  Filename: missioninfo.h
 *  Author:   UbuntuCXY
 *  Email Address: 1484652026@qq.com
 *
 *  任务相关的头文件
 *  注释添加时间: 2020.7.7
 *
 *  相关说明:
 *
 *  Mission: 定义了一局游戏中要用到的参数结构体。
 *
 *  missions数组定义了所有关卡的参数结构体，通过增加该数组内容，可以新增关卡，格式参照前面的内容
 *  即可。
 *
 */

#ifndef MISSIONINFO_H
#define MISSIONINFO_H

#include <QList>
#include <QVector>

#include "mapinfo.h"
#include "control.h"
#include "figure.h"
#include "facility.h"

//任务种类
#define ALLKILLED 1     // 全部击杀
#define SAVEFIG   2     // 拯救人形

struct Mission{
    QVector< int > pos;   //参战人形初始位置
    QVector< QList<int> >  facilities;  // 设施
    int     MissionKind;    // 任务种类
    QString hintInfo;    // 提示信息
    int     MapNo;      // 地图
    int     limitTime;  // 限时
};

// 任务格式:
// { {我方人形起始位置},
//   {{设施列表1},..,{设施列表n}},
//   任务种类,
//   提示信息字符串,
//   地图编号,
//   限时时间,
//  },
//
// 设施列表格式:
//      飞机场: {AIRPORT, x坐标(虚地址), y坐标(虚地址), 敌人n编号, 敌人n-1编号, .., 敌人1编号}
//      存放地雷的设施: {BOMBBASE, x坐标(虚地址), y坐标(虚地址)}
//      碉堡设施: {PILLBOX, x坐标(虚地址), y坐标(虚地址), 方向, 阵营编号}
//      囚笼设施: {CAGE, x坐标(虚地址), y坐标(虚地址)}
//      雷达设施: {RADAR, x坐标(虚地址), y坐标(虚地址)}

#define MISSIONUM 3 // 任务数量

const Mission missions[] = {
    // Mission 1
    {{11, 10},
     {{AIRPORT, 0, 0, DIANFANBAO, LONGQIBIN, DIANFANBAO},
      {AIRPORT, 9, 0, QIEGEZHE, DIANFANBAO, HUFENG},
      {AIRPORT, 19, 0, DIANFANBAO, DIANFANBAO, DIANFANBAO},
     },
     ALLKILLED, "格里芬指挥部：\n请在规定时间内击杀所有敌军单位.\n", 1, 6000},

    // Mission 2
    {{11, 10},
     {{AIRPORT, 0, 11, HUFENG, XUNYOUZHE,DIANFANBAO},
      {AIRPORT, 19, 0, GUIZISHOU, XUNYOUZHE,HUFENG},
      {AIRPORT, 5, 4,  QIEGEZHE, LIEOU, HUFENG},
      {AIRPORT, 14, 7, QIEGEZHE, LONGQIBIN, DIANFANBAO},
      {BOMBBASE, 14, 4},
      {BOMBBASE, 5, 7},
     },
     ALLKILLED, "格里芬指挥部：\n请在规定时间内击杀所有敌军单位.另外请注意附近有刽子手"
     "出没，使用歌利亚可以降低其伤害和生命值.Good luck!\n", 2, 6000},

    // Mission 3
    {{0, 0},
     {{AIRPORT, 0, 11, HUFENG, XUNYOUZHE,XUNYOUZHE},
     {AIRPORT, 10, 4, HUFENG, XUNYOUZHE,HUFENG},
     {AIRPORT, 19, 2,  QIEGEZHE, LIEOU, XUNYOUZHE},
     {AIRPORT, 19, 6, QIEGEZHE, LONGQIBIN, QIEGEZHE},
     {PILLBOX, 5, 11, static_cast<int>(LEFT), TIEXUE},
     {PILLBOX, 15, 7, static_cast<int>(LEFT), TIEXUE},
     {PILLBOX, 17, 2, static_cast<int>(LEFT), TIEXUE},
     {CAGE, 19, 0},
     {CAGE, 19, 11},
     {RADAR, 9, 0},
     {RADAR, 12, 2},
    },
    SAVEFIG, "格里芬指挥部：\n请在规定时间内营救我方全部人形.\n提示：\n使用雷达可以使某一个井盖宕机."
    "Good luck!\n", 3, 3000},

};

#endif // MISSIONINFO_H

