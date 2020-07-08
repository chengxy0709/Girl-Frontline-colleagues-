/*
 *  Filename: gamestart.h
 *  Author:   UbuntuCXY
 *  Email Address: 1484652026@qq.com
 *
 *  游戏类的头文件，实例化可以产生一局游戏
 *  注释添加时间: 2020.7.7
 *
 *  函数说明:
 *
 *  gameStart(mainFigNo, Mission *mission, *parent)
 *      实例化一局游戏，我方参战人形编号mainFigNo，游戏参数结构体地址mission，父组件地址parent。
 *  analyMission(*mission)
 *      分析部分游戏参数，建立一局游戏。
 *  keyPressEvent(*event)
 *      按键按下控制函数。
 *  keyReleaseEvent(*event)
 *      按键释放控制函数。
 *  automoveForBoss(*fig, *gmap)
 *      争对Boss(fig)进行自动移动。
 *  autocontrol(*fig)
 *      对某个人形fig进行自动控制。
 *  autocontrolForBoss(*fig)
 *      对Boss(fig)进行自动控制。
 *  updateBulletList()
 *      更新游戏内现存的所有子弹移动。
 *  updateEnemiesList()
 *      更新游戏内所有现存敌人动作。
 *  updateEnemiesBulletTimer()
 *      更新游戏内所有人形换弹定时器。
 *  restoreFigBullet(Figure *fig)
 *      对某个人形(fig)进行换弹。
 *  hitCheck()
 *      对所有子弹进行击中检查。
 *  addEnemies()
 *      遍历飞机场，产生敌人。
 *  bombTestBoom()
 *      遍历所有地雷，尝试引爆。
 *  updatePillboxFire()
 *      更新所有碉堡开火。
 *  updateRadar()
 *      尝试启动或关闭所有雷达。
 *  generateOneBullet(*obj)
 *      对某一个可以开火的目标，产生一颗与其同向及同一位置的子弹。
 *  airPortHasEnemies()
 *      检测所有机场是否还有未生成的敌人。
 *  gameCheck()
 *      游戏检查，是否以达成目标。
 *  ~gameStart()
 *      析构函数。
 *  gameStop(flag)
 *      发射游戏停止信号，信号值为flag。
 *  startgame()
 *      启动游戏槽函数。
 *  pausegame()
 *      暂停游戏槽函数。
 *  stopgame()
 *      停止游戏槽函数。
 *  timerInterrupt()
 *      定时器中断函数，用于游戏循环。
 *
 *  变量说明:
 *
 *  widget              中心组件
 *  timer               定时器
 *  counter             计数器
 *  startBtn            开始按钮
 *  stopBtn             停止按钮
 *  pauseBtn            暂停按钮
 *  enemyNumLabel       显示敌人数量的Label
 *  enemyNumStrLabel    字符串Label
 *  myLifeLabel         显示我方人形生命值的Label
 *  myLifeStrLabel      字符串Label
 *  enemyLifeNumLabel   显示当前击中敌人生命值的Label
 *  enemyLifeNumStrLabel 字符串Label
 *  myBulletLabel       显示剩余弹药的Label
 *  myBulletStrLabel    字符串Label
 *  limitTimeLabel      显示剩余时间的Label
 *  limitTimeStrLabel   字符串Label
 *  hintText            显示提示信息的文本框
 *  gmap                游戏地图
 *  fig                 我方人形
 *  Bag                 我的背包
 *  effects             用于管理游戏特效
 *  bullets             用于存放所有产生的子弹
 *  enemies             用于存放所有生成的敌人
 *  Airports            用于存放所有的飞机场
 *  bombBases           用于存放所有bombbase
 *  bombs               用于存放所有地雷
 *  pillboxses          用于存放所有碉堡
 *  cages               用于存放所有囚笼
 *  radars              用于存放所有雷达
 *  gamestate           游戏状态
 *  limitTime           限制时间
 *  missionKind         任务种类
 *
 *
 */

#ifndef GAMESTART_H
#define GAMESTART_H

#include <QMainWindow>
#include <QDebug>
#include <QLabel>
#include <QTextEdit>
#include <QMovie>
#include <QWidget>
#include <QImage>
#include <windows.h>
#include <QPushButton>
#include <QScrollBar>
#include <QKeyEvent>
#include <QTimer>
#include <QList>
#include <QVector>
#include <QMessageBox>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <QMediaPlayer>

#include "gamemap.h"
#include "missioninfo.h"
#include "figure.h"
#include "control.h"
#include "bullet.h"
#include "facility.h"
#include "effect.h"
#include "skill.h"

#define GAMELOOPPROCESSTIME 20  // 游戏循环处理时间片断

//游戏状态
#define GAMESTART   0   //开始
#define GAMESTOP    1   //停止
#define GAMEPAUSE   2   //暂停

namespace Ui {
class gameStart;
}

class gameStart : public QMainWindow
{
    Q_OBJECT

public:
    explicit gameStart(int mainFigNo, const Mission *mission, QWidget *parent = 0);

    void analyMission(const Mission *mission);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    inline void automoveForBoss(Figure *fig, GameMap *gmap);
    void autocontrol(Figure *fig);
    void autocontrolForBoss(Figure *fig);
    void updateBulletList();
    void updateEnemiesList();
    void updateEnemiesBulletTimer();
    void restoreFigBullet(Figure *fig);
    void hitCheck();
    void addEnemies();
    void bombTestBoom();
    void updatePillboxFire();
    void updateRadar();

    template<class T>
    void generateOneBullet(T *obj){
        Bullet *bullet = new Bullet(obj->getXpos(), obj->getYpos(),
                                    obj->getDirection(), obj->getID(),
                                    obj->getHurt(),  gmap, widget);
        bullets.push_back(bullet);
    }

    bool airPortHasEnemies() const{
        for(Airport* p : Airports){
            if(p->remainNum() != 0) return true;
        }
        return false;
    }

    bool gameCheck();

    ~gameStart();

signals:
    void gameStop(int flag);

private slots:
    void startgame();
    void pausegame();
    void stopgame();
    void timerInterrupt();

private:
    Ui::gameStart *ui;

    QWidget *widget;
    QTimer *timer;
    int counter{0};

    QPushButton *startBtn;
    QPushButton *stopBtn;
    QPushButton *pauseBtn;

    QLabel *enemyNumLabel;
    QLabel *enemyNumStrLabel;
    QLabel *myLifeLabel;
    QLabel *myLifeStrLabel;
    QLabel *enemyLifeNumLabel;
    QLabel *enemyLifeNumStrLabel;
    QLabel *myBulletLabel;
    QLabel *myBulletStrLabel;
    QLabel *limitTimeLabel;
    QLabel *limitTimeStrLabel;
    QTextEdit *hintText;

    GameMap *gmap;
    Figure *fig;
    QList<int> Bag;
    Effect *effects;

    QList<Bullet*> bullets;
    QList<Figure*> enemies;

    QList<Airport*> Airports;
    QList<BombBase*> bombBases;
    QList<Bomb*> bombs;
    QList<Pillbox*> pillboxses;
    QList<Cage*> cages;
    QList<Radar*> radars;

    int gamestate{1};
    int limitTime;
    int missionKind;

};

#endif // GAMESTART_H
