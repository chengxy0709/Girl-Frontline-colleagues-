/*
 *  Filename: skill.h
 *  Author:   UbuntuCXY
 *  Email Address: 1484652026@qq.com
 *
 *  技能相关的头文件
 *  注释添加时间: 2020.7.7
 *
 *  相关说明:
 *
 *  本文件定义了一些特殊技能供系统调用，目前仅有一个。
 *
 */

#ifndef SKILL_H
#define SKILL_H

#include "figure.h"

// 范围爆炸
// sender: 释放人形
// receiver: 承受人形
void coverboom(Figure *sender, Figure *receiver);

#endif // SKILL_H

