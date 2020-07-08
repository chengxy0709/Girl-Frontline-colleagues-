/*
 *  Filename: effect.h
 *  Author:   UbuntuCXY
 *  Email Address: 1484652026@qq.com
 *
 *  特效类的头文件
 *  注释添加时间: 2020.7.7
 *
 *  函数说明:
 *
 *  Effect(*parent)
 *      实例化一个Effect类，其私有变量使用默认值，parent指定特效显示组件的父组件。
 *  Effect(t, *parent)
 *      实例化一个Effect类，特效驻留时间为(t * GAMELOOPPROCESSTIME)ms，parent指定特效显示组件
 *  的父组件。
 *  addEffect(x, y, effectKind)
 *      在位置(x,y)（实坐标）处添加一个特效，特效类型为effectKind。
 *  updateEffect()
 *      更新特效显示，将显示超时的特效去掉。
 *  ~Effect();
 *      析构函数。
 *
 *  变量说明:
 *
 *  stayTime    特效驻留时间
 *  widget      父组件地址
 *  labels      特效注册表，表项为<特效显示Label地址, 特效驻留时间>
 *
 */

#ifndef EFFECT_H
#define EFFECT_H

#include <QWidget>
#include <QLabel>
#include <QList>
#include <QPair>
#include <QImage>
#include <QMovie>

#define BULLET1EFFECT 1 // 子弹特效1
#define BOOMEFFECT    2 //  爆炸特效
#define COVERBOOM     3 //  范围爆炸特效

class Effect : public QWidget
{
    Q_OBJECT
public:
    explicit Effect(QWidget *parent = 0);
    Effect(int t, QWidget *parent = 0);

    void addEffect(int x, int y, int effectKind);
    void updateEffect();

    ~Effect();

signals:

public slots:

private:
    int stayTime;
    QWidget *widget;
    QList< QPair<QLabel*, int> > labels;

};

#endif // EFFECT_H
