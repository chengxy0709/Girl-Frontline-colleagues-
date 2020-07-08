/*
 *  Filename: gamestart.cpp
 *  Author:   UbuntuCXY
 *  Email Address: 1484652026@qq.com
 *
 *  游戏类的实现文件
 *  注释添加时间: 2020.7.7
 *
 *  类成员函数说明见头文件gamestart.h
 *
 *
 */

#include "gamestart.h"
#include "ui_gamestart.h"


gameStart::gameStart(int mainFigNo, const Mission *mission, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gameStart)
{
    ui->setupUi(this);

    srand(time(NULL));
    widget = new QWidget;
    timer = new QTimer(this);

    startBtn = new QPushButton(widget);
    startBtn->setText("开始");
    startBtn->setGeometry(QRect(MAPWIDTH * MAPUNITSZ + 8,
                                MAPHEIGHT * MAPUNITSZ - 30, 50, 25));
    startBtn->setFocusPolicy(Qt::NoFocus);
    pauseBtn = new QPushButton(widget);
    pauseBtn->setText("暂停");
    pauseBtn->setGeometry(QRect(MAPWIDTH * MAPUNITSZ + 74,
                                MAPHEIGHT * MAPUNITSZ - 30, 50, 25));
    pauseBtn->setFocusPolicy(Qt::NoFocus);
    stopBtn = new QPushButton(widget);
    stopBtn->setText("结束");
    stopBtn->setGeometry(QRect(MAPWIDTH * MAPUNITSZ + 140,
                                MAPHEIGHT * MAPUNITSZ - 30, 50, 25));
    stopBtn->setFocusPolicy(Qt::NoFocus);

    enemyNumStrLabel = new QLabel(widget);
    enemyNumStrLabel->setGeometry(QRect(MAPWIDTH * MAPUNITSZ + 8,
                                       (MAPHEIGHT * MAPUNITSZ) / 2, 70, 25));
    enemyNumStrLabel->setText("敌方数量：");
    enemyNumLabel = new QLabel(widget);
    enemyNumLabel->setGeometry(QRect(MAPWIDTH * MAPUNITSZ + 108,
                                    (MAPHEIGHT * MAPUNITSZ) / 2, 50, 25));
    enemyNumLabel->setText("--");
    myLifeStrLabel = new QLabel(widget);
    myLifeStrLabel->setGeometry(QRect(MAPWIDTH * MAPUNITSZ + 8,
                                       (MAPHEIGHT * MAPUNITSZ) / 2 + 50, 70, 25));
    myLifeStrLabel->setText("人形生命值：");
    myLifeLabel = new QLabel(widget);
    myLifeLabel->setGeometry(QRect(MAPWIDTH * MAPUNITSZ + 108,
                                    (MAPHEIGHT * MAPUNITSZ) / 2 + 50, 50, 25));
    myLifeLabel->setText("--");
    enemyLifeNumStrLabel = new QLabel(widget);
    enemyLifeNumStrLabel->setGeometry(QRect(MAPWIDTH * MAPUNITSZ + 8,
                                       (MAPHEIGHT * MAPUNITSZ) / 2 + 100, 70, 25));
    enemyLifeNumStrLabel->setText("敌人生命值：");
    enemyLifeNumLabel = new QLabel(widget);
    enemyLifeNumLabel->setGeometry(QRect(MAPWIDTH * MAPUNITSZ + 108,
                                    (MAPHEIGHT * MAPUNITSZ) / 2 + 100, 50, 25));
    enemyLifeNumLabel->setText("--");

    myBulletStrLabel = new QLabel(widget);
    myBulletStrLabel->setGeometry(QRect(MAPWIDTH * MAPUNITSZ + 8,
                                       (MAPHEIGHT * MAPUNITSZ) / 2 + 150, 70, 25));
    myBulletStrLabel->setText("子弹数：");
    myBulletLabel = new QLabel(widget);
    myBulletLabel->setGeometry(QRect(MAPWIDTH * MAPUNITSZ + 108,
                                    (MAPHEIGHT * MAPUNITSZ) / 2 + 150, 50, 25));
    myBulletLabel->setText("--");

    limitTimeStrLabel = new QLabel(widget);
    limitTimeStrLabel->setGeometry(QRect(MAPWIDTH * MAPUNITSZ + 8,
                                       (MAPHEIGHT * MAPUNITSZ) / 2 + 200, 70, 25));
    limitTimeStrLabel->setText("剩余时间：");
    limitTimeLabel = new QLabel(widget);
    limitTimeLabel->setGeometry(QRect(MAPWIDTH * MAPUNITSZ + 108,
                                    (MAPHEIGHT * MAPUNITSZ) / 2 + 200, 50, 25));
    limitTimeLabel->setText("--");

    hintText = new QTextEdit(widget);
    hintText->setGeometry(QRect(MAPWIDTH * MAPUNITSZ + 8, 0, 180, 250));
    hintText->setFocusPolicy(Qt::NoFocus);
    hintText->setPlainText(mission->hintInfo);

    analyMission(mission);

    fig = new Figure(mainFigNo, mission->pos[1] * MAPUNITSZ, mission->pos[0] * MAPUNITSZ,
            widget);
    myLifeLabel->setText(QString::number(fig->getLife()));
    myBulletLabel->setText(QString::number(fig->getBulletNum()));

    effects = new Effect(5, widget);

    setMinimumSize(MAPWIDTH * MAPUNITSZ + 200, MAPHEIGHT * MAPUNITSZ + 30);
    setCentralWidget(widget);

    connect(timer, SIGNAL(timeout()), this, SLOT(timerInterrupt()));
    connect(startBtn, SIGNAL(clicked()), this, SLOT(startgame()));
    connect(pauseBtn, SIGNAL(clicked()), this, SLOT(pausegame()));
    connect(stopBtn, SIGNAL(clicked()), this, SLOT(stopgame()));

}

void gameStart::timerInterrupt(){
    counter++;
    hitCheck();
    effects->updateEffect();
    updateBulletList();
    updateEnemiesBulletTimer();
    if(counter % 5 == 0){
        updateRadar();
        updatePillboxFire();
        updateEnemiesList();
        bombTestBoom();
    }
    if(counter % 500 == 0){
        addEnemies();
    }
    myLifeLabel->setText(QString::number(fig->getLife()));
    enemyNumLabel->setText(QString::number(enemies.size()));
    limitTimeLabel->setText(QString::number(limitTime - counter));
    if(gameCheck()) emit gameStop(1);
}

void gameStart::startgame(){
    timer->start(GAMELOOPPROCESSTIME);
    gamestate = GAMESTART;
    addEnemies();
}

void gameStart::pausegame(){
    if(gamestate != GAMESTART){
        timer->start(GAMELOOPPROCESSTIME);
        gamestate = GAMESTART;
        pauseBtn->setText("暂停");
    }
    else{
        timer->stop();
        gamestate = GAMEPAUSE;
        pauseBtn->setText("继续");
    }
}

void gameStart::stopgame(){
    timer->stop();
    gamestate = GAMESTOP;
    emit gameStop(0);
}

void gameStart::addEnemies(){

    for(Airport *p : Airports){
        FigPosInfo *info = p->putOneEnemyInfo();
        if(info){
            Figure *enemy = new Figure(info->No, info->x - MAPUNITSZ / 2,
                                       info->y - MAPUNITSZ / 2, widget, info->dir );
            enemies.push_back(enemy);
            delete info;
        }
    }

}

void gameStart::restoreFigBullet(Figure *fig){
    if(fig->bulletTimeCounter < 0) fig->bulletTimeCounter = 0;
    if(fig->bulletTimeCounter >= 10){    // 换弹时间
        fig->addBullet();
        fig->bulletTimeCounter = -1;
    }
}


void gameStart::updateEnemiesList(){

    for(Figure *fig : enemies){
        if(fig->isBoss()) autocontrolForBoss(fig);
        else autocontrol(fig);
    }

}

void gameStart::updateEnemiesBulletTimer(){

    for(Figure *fig : enemies){
        if(fig->bulletTimeCounter >= 0)
            fig->bulletTimeCounter++;
    }
    if(fig->bulletTimeCounter >= 0)
        fig->bulletTimeCounter++;

}

void gameStart::updateBulletList(){

    for(QList<Bullet*>::iterator p = bullets.begin(); p != bullets.end();){
        if(!(*p)->update()){
            delete *p;
            p = bullets.erase(p);
        }
        else {
            p++;
        }
    }

}

void gameStart::analyMission(const Mission *mission){

    gmap = new GameMap(mission->MapNo);
    gmap->generateMap(widget);

    for(int i = 0; i < mission->facilities.size(); i++){
        int FacKind = mission->facilities[i].at(0);
        int x = mission->facilities[i].at(1);
        int y = mission->facilities[i].at(2);
        if(FacKind == AIRPORT){
            QList<int> tempList(mission->facilities[i]);
            auto pos = tempList.begin(); pos++; pos++; pos++;
            tempList.erase(tempList.begin(), pos);
            Airport *airport = new Airport(x, y, tempList, widget);
            Airports.push_back(airport);
        }
        else if(FacKind == BOMBBASE){
            BombBase *bombBase = new BombBase(x, y, widget);
            bombBases.push_back(bombBase);
        }
        else if(FacKind == PILLBOX){
            Pillbox *pillbox = new Pillbox(x, y, static_cast<DIRECTION>(
                                               mission->facilities[i].at(3)),
                                            mission->facilities[i].at(4), widget);
            pillboxses.push_back(pillbox);
        }
        else if(FacKind == CAGE){
            Cage *cage = new Cage(x, y, widget);
            cages.push_back(cage);
        }
        else if(FacKind == RADAR){
            Radar *radar = new Radar(x, y, widget);
            radars.push_back(radar);
        }
    }

    limitTime = mission->limitTime;
    missionKind = mission->MissionKind;

}

void gameStart::bombTestBoom(){

    for( QList<Bomb*>::iterator p = bombs.begin(); p != bombs.end(); ){
        bool boomFlag{false};
        for( Figure *fig : enemies ){
            if((*p)->tryBoom(fig)){
                effects->addEffect((*p)->getXpos(), (*p)->getYpos(), BOOMEFFECT);
                delete *p;
                boomFlag = true;
                enemyLifeNumLabel->setText(QString::number(fig->getLife()));
                hintText->append("系统：\n炸弹已引爆，被炸对象生命值和攻击力减半.\n");
                hintText->verticalScrollBar()->setSliderPosition(
                            hintText->verticalScrollBar()->maximum());
                break;
            }
        }
        if(boomFlag) p = bombs.erase(p);
        else p++;
    }

}

void gameStart::updatePillboxFire(){

    for(Pillbox *pillbox : pillboxses){
        if(pillbox->isFire()){
            generateOneBullet(pillbox);
        }
    }

}

void gameStart::updateRadar(){

    for(Radar *radar : radars){
        if(radar->isUsed()) continue;
        int index = radar->tryStart(fig->getXpos(), fig->getYpos(), pillboxses);
        if(index >= 0){
            pillboxses[index]->SetStopFire();
            effects->addEffect(pillboxses[index]->getXpos(),
                               pillboxses[index]->getYpos(), BOOMEFFECT);
            radar->setUsed();
            hintText->append("系统：\n执行命令成功.\n");
            hintText->verticalScrollBar()->setSliderPosition(
                        hintText->verticalScrollBar()->maximum());
        }
        radar->tryStop(fig->getXpos(), fig->getYpos());
    }

}

bool gameStart::gameCheck(){

    if(missionKind == ALLKILLED){
        if((enemies.size() == 0 && !airPortHasEnemies()) ||
                counter >= limitTime)
            return true;
    }
    else if(missionKind == SAVEFIG){
        bool flag = true;
        for(Cage *cage : cages){
            if(!cage->isSaved()) flag = false;
        }
        if(flag) return true;
    }

    return false;

}

gameStart::~gameStart()
{
    delete startBtn;
    delete pauseBtn;
    delete stopBtn;
    delete enemyNumLabel;
    delete enemyNumStrLabel;
    delete myLifeLabel;
    delete myLifeStrLabel;
    delete enemyLifeNumLabel;
    delete enemyLifeNumStrLabel;
    delete myBulletLabel;
    delete myBulletStrLabel;
    delete limitTimeLabel;
    delete limitTimeStrLabel;
    delete hintText;

    delete gmap;
    delete effects;
    for(auto p : bullets){
        if(p) delete p;
    }
    for(auto p : enemies){
        if(p) delete p;
    }
    for(auto p : Airports){
        delete p;
    }
    for(auto p : bombBases){
        delete p;
    }
    for(auto p : bombs){
        delete p;
    }
    for(auto p : pillboxses){
        delete p;
    }
    for(auto p : cages){
        delete p;
    }
    for(auto p : radars){
        delete p;
    }
    delete fig;
    delete widget;

    delete ui;
}
