/*
 *  Filename: gameconsole.cpp
 *  Author:   UbuntuCXY
 *  Email Address: 1484652026@qq.com
 *
 *  游戏控制台类的实现文件
 *  注释添加时间: 2020.7.7
 *
 *  类成员函数说明见游戏控制台类头文件
 *
 */

#include <QMessageBox>
#include <QDebug>
#include "gameconsole.h"
#include "figureinfo.h"

gameConsole::gameConsole(QWidget *parent) : QMainWindow(parent)
{

    widget = new QWidget;

    currentFirstIndex = 0;
    for(int i = 0; i < GAMENUMINONEPAGE; i++){
        QPushButton *newgamebtn = new QPushButton;
        newgamebtn->setStyleSheet("background-color:rgba(229,209,162,0.7)");
        if(i >= MISSIONUM)
            newgamebtn->setText(" ");
        else
            newgamebtn->setText("Mission " + QString::number(i));
        newgamebtns.push_back(newgamebtn);
    }

    upbtn = new QPushButton;
    upbtn->setFixedSize(75, 25);
    upbtn->setStyleSheet("background-color:rgba(229,209,162,0.7)");
    upbtn->setText("上一页");

    downbtn = new QPushButton;
    downbtn->setFixedSize(75, 25);
    downbtn->setStyleSheet("background-color:rgba(229,209,162,0.7)");
    downbtn->setText("下一页");

    figSelect = new QComboBox;
    figSelect->setFixedSize(100,25);
    figSelect->setStyleSheet("background-color:rgba(229,209,162,0.7)");
    for(int i = GELIFENMINNUM; i <= GELIFENMAXNUM; i++){
        figSelect->addItem(FiguresData[i].name);
    }
    int index = GELIFENMINNUM;

    figImgLabel = new QLabel;
    figImgLabel->setFixedSize(50, 50);
    movie = new QMovie( "../picture/" + FiguresData[index].name + "_wait_right.gif");
    figImgLabel->setMovie(movie);
    movie->start();

    figHurtLabel = new QLabel;
    figHurtLabel->setFixedSize(100, 25);
    figHurtLabel->setText("伤害：" + QString::number(FiguresData[index].hurt) );
    figHurtLabel->setStyleSheet("background-color:rgba(229,209,162,0.7)");

    figLiftLabel = new QLabel;
    figLiftLabel->setFixedSize(100, 25);
    figLiftLabel->setText("生命值：" + QString::number(FiguresData[index].life));
    figLiftLabel->setStyleSheet("background-color:rgba(229,209,162,0.7)");

    figSpeedLabel = new QLabel;
    figSpeedLabel->setFixedSize(100, 25);
    figSpeedLabel->setText("速度：" + QString::number(FiguresData[index].speed));
    figSpeedLabel->setStyleSheet("background-color:rgba(229,209,162,0.7)");

    mainlayout = new QGridLayout;

    for(int i = 0; i < GAMENUMINONEPAGE; i++){
        mainlayout->addWidget(newgamebtns[i], i, 0, 1, 2);
    }
    mainlayout->addWidget(upbtn, 5, 0, 1, 1);
    mainlayout->addWidget(downbtn, 5, 1, 1, 1);
    mainlayout->addWidget(figSelect, 0, 2, 1, 1);
    mainlayout->addWidget(figImgLabel, 1, 2, 1, 1);
    mainlayout->addWidget(figHurtLabel, 2, 2, 1, 1);
    mainlayout->addWidget(figLiftLabel, 3, 2, 1, 1);
    mainlayout->addWidget(figSpeedLabel, 4, 2, 1, 1);

    widget->setLayout(mainlayout);
    setMinimumSize(600, 400);

    QPalette pal = this->palette();
    pal.setBrush(QPalette::Background, QBrush(QPixmap("../picture/"
                                                      "background1.png")));
    setPalette(pal);
    setCentralWidget(widget);

    player = new QMediaPlayer;
    playerlist = new QMediaPlaylist;
    playerlist->addMedia(QUrl::fromLocalFile("../music/gameconsole.wav"));
    playerlist->addMedia(QUrl::fromLocalFile("../music/gamestart.wav"));
    playerlist->setCurrentIndex(0);
    playerlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    player->setVolume(30);
    player->setPlaylist(playerlist);
    player->play();

    connect(newgamebtns[0], SIGNAL(clicked()), this, SLOT(newgame1()));
    connect(newgamebtns[1], SIGNAL(clicked()), this, SLOT(newgame2()));
    connect(newgamebtns[2], SIGNAL(clicked()), this, SLOT(newgame3()));
    connect(newgamebtns[3], SIGNAL(clicked()), this, SLOT(newgame4()));
    connect(newgamebtns[4], SIGNAL(clicked()), this, SLOT(newgame5()));
    connect(upbtn, SIGNAL(clicked()), this, SLOT(upbtnSlot()));
    connect(downbtn, SIGNAL(clicked()), this, SLOT(downbtnSlot()));
    connect(figSelect, SIGNAL(currentIndexChanged(int)), this, SLOT(figureChange(int)));

}

void gameConsole::deletegame(int flag){
    QString infoStr = "";
    if(flag == 0){
        infoStr = "Game stop!";
    }
    else if(flag == 1){
        infoStr = "Victory!";
    }
    else if(flag == 2){
        infoStr = "You have been killed!";
    }
    else{
        infoStr = "Game terminated";
    }
    QMessageBox::information(this, "GrilFrontline", infoStr,
                                  QMessageBox::Ok,QMessageBox::NoButton);
    game->deleteLater();
    playerlist->setCurrentIndex(0);
    //delete game;
    //game->hide();
}

void gameConsole::figureChange(int changedIndex){

    QString name = figSelect->currentText();
    int index = changedIndex + GELIFENMINNUM;
    delete movie;
    movie = new QMovie( "../picture/" + name + "_wait_right.gif");
    figImgLabel->setMovie(movie);
    movie->start();
    figHurtLabel->setText("伤害：" + QString::number(FiguresData[index].hurt) );
    figLiftLabel->setText("生命值：" + QString::number(FiguresData[index].life));
    figSpeedLabel->setText("速度：" + QString::number(FiguresData[index].speed));

}

void gameConsole::newgame1(){

    if(currentFirstIndex >= MISSIONUM) return;

    playerlist->setCurrentIndex(1);
    game = new gameStart(figSelect->currentIndex() + GELIFENMINNUM,
                         &missions[currentFirstIndex]);
    connect(game, SIGNAL(gameStop(int)), this, SLOT(deletegame(int)));
    game->show();

}

void gameConsole::newgame2(){

    if(currentFirstIndex + 1 >= MISSIONUM) return;

    playerlist->setCurrentIndex(1);
    game = new gameStart(figSelect->currentIndex() + GELIFENMINNUM,
                         &missions[currentFirstIndex + 1]);
    connect(game, SIGNAL(gameStop(int)), this, SLOT(deletegame(int)));
    game->show();

}

void gameConsole::newgame3(){

    if(currentFirstIndex + 2 >= MISSIONUM) return;

    playerlist->setCurrentIndex(1);
    game = new gameStart(figSelect->currentIndex() + GELIFENMINNUM,
                         &missions[currentFirstIndex + 2]);
    connect(game, SIGNAL(gameStop(int)), this, SLOT(deletegame(int)));
    game->show();

}

void gameConsole::newgame4(){

    if(currentFirstIndex + 3 >= MISSIONUM) return;

    playerlist->setCurrentIndex(1);
    game = new gameStart(figSelect->currentIndex() + GELIFENMINNUM,
                         &missions[currentFirstIndex + 3]);
    connect(game, SIGNAL(gameStop(int)), this, SLOT(deletegame(int)));
    game->show();

}
void gameConsole::newgame5(){

    if(currentFirstIndex + 4 >= MISSIONUM) return;

    playerlist->setCurrentIndex(1);
    game = new gameStart(figSelect->currentIndex() + GELIFENMINNUM,
                         &missions[currentFirstIndex + 4]);
    connect(game, SIGNAL(gameStop(int)), this, SLOT(deletegame(int)));
    game->show();

}

void gameConsole::downbtnSlot(){

    if(currentFirstIndex + GAMENUMINONEPAGE < MISSIONUM){
        currentFirstIndex += GAMENUMINONEPAGE;
        for(int i = 0; i < GAMENUMINONEPAGE; i++){
            if(currentFirstIndex + i >= MISSIONUM)
                newgamebtns[i]->setText(" ");
            else
                newgamebtns[i]->setText("Mission " + QString::number(
                                            currentFirstIndex + i));
        }
    }

}

void gameConsole::upbtnSlot(){

    if(currentFirstIndex - GAMENUMINONEPAGE >= 0){
        currentFirstIndex -= GAMENUMINONEPAGE;
        for(int i = 0; i < GAMENUMINONEPAGE; i++){
            if(currentFirstIndex + i >= MISSIONUM)
                newgamebtns[i]->setText(" ");
            else
                newgamebtns[i]->setText("Mission " + QString::number(
                                            currentFirstIndex + i));
        }
    }

}

gameConsole::~gameConsole()
{
    for(int i = 0; i < GAMENUMINONEPAGE; i++){
        delete newgamebtns[i];
    }
    delete figSelect;
    delete movie;
    delete mainlayout;
    delete player;
    delete playerlist;
    delete widget;
}

