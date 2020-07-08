/*
 *  Filename: gameconsole.h
 *  Author:   UbuntuCXY
 *  Email Address: 1484652026@qq.com
 *
 *  游戏控制台类的头文件
 *  注释添加时间: 2020.7.7
 *
 *  函数说明:
 *
 *  gameConsole(*parent)
 *      实例化一个游戏控制台
 *  ~gameConsole()
 *      析构函数。
 *  figureChange(changedIndex)
 *      切换人形槽函数
 *  newgame1()
 *      启动第(currentFirstIndex + 0)关游戏槽函数
 *  newgame2()
 *      启动第(currentFirstIndex + 1)关游戏槽函数
 *  newgame3()
 *      启动第(currentFirstIndex + 2)关游戏槽函数
 *  newgame4()
 *      启动第(currentFirstIndex + 3)关游戏槽函数
 *  newgame5()
 *      启动第(currentFirstIndex + 4)关游戏槽函数
 *  upbtnSlot()
 *      上翻页槽函数
 *  downbtnSlot()
 *      下翻页槽函数
 *  deletegame(flag)
 *      关闭游戏槽函数
 *
 *  变量说明:
 *
 *  widget          中心组件
 *  mainlayout      主要布局
 *  newgamebtns     新游戏按钮组
 *  upbtn           上翻页按钮
 *  downbtn         下翻页按钮
 *  figSelect       人形选择下拉框
 *  figImgLabel     显示人形Label
 *  figHurtLabel    显示人形伤害Label
 *  figLiftLabel    显示人形生命Label
 *  figSpeedLabel   显示人形速度Label
 *  movie           人形动画
 *  player          背景音乐播放控件
 *  playerlist      背景音乐播放列表
 *  game            新游戏地址
 *  currentFirstIndex   当前页第一个游戏索引号
 *
 *
 */

#ifndef GAMECONSOLE_H
#define GAMECONSOLE_H

#define GAMENUMINONEPAGE 5 //一页中显示的游戏数量

#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QComboBox>
#include <QMovie>
#include <QVector>
#include <QPalette>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include "gamestart.h"
#include "missioninfo.h"

class gameConsole : public QMainWindow
{
    Q_OBJECT
public:
    explicit gameConsole(QWidget *parent = 0);
    ~gameConsole();

signals:

public slots:
    void figureChange(int changedIndex);
    void newgame1();
    void newgame2();
    void newgame3();
    void newgame4();
    void newgame5();
    void upbtnSlot();
    void downbtnSlot();
    void deletegame(int flag);

private:
    QWidget     *widget;
    QGridLayout *mainlayout;
    QVector<QPushButton*> newgamebtns;
    QPushButton *upbtn;
    QPushButton *downbtn;
    QComboBox   *figSelect;
    QLabel      *figImgLabel;
    QLabel      *figHurtLabel;
    QLabel      *figLiftLabel;
    QLabel      *figSpeedLabel;
    QMovie      *movie;

    QMediaPlayer *player;
    QMediaPlaylist *playerlist;

    gameStart *game;
    int currentFirstIndex;

};

#endif // GAMECONSOLE_H
