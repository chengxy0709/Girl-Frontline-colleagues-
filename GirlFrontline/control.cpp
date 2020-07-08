/*
 *  Filename: control.cpp
 *  Author:   UbuntuCXY
 *  Email Address: 1484652026@qq.com
 *
 *  游戏类控制的实现文件
 *  注释添加时间: 2020.7.8
 *
 *  子函数说明（类成员函数说明见gamestart.h）:
 *
 *  leftmove(*fig, *gmap)
 *      尝试在地图gmap上向左移动，移动距离为人形速度，若可以移动返回人形速度，否则返回负值。
 *  rightmove(*fig, *gmap)
 *      尝试在地图gmap上向右移动，移动距离为人形速度，若可以移动返回人形速度，否则返回负值。
 *  upmove(*fig, *gmap)
 *      尝试在地图gmap上向上移动，移动距离为人形速度，若可以移动返回人形速度，否则返回负值。
 *  downmove(*fig, *gmap)
 *      尝试在地图gmap上向下移动，移动距离为人形速度，若可以移动返回人形速度，否则返回负值。
 *  GrassCheck(*fig, *gmap)
 *      检测人形是否在草地上，是的话隐身。
 *  DesertCheck(*fig, *gmap)
 *      检测人形是否在沙漠上，是的话减速。
 *  autoMoveExecute( initDir, *fig, *gmap )
 *      自动控制，逻辑为先尝试向initDir方向移动，不能移动的话随机选择其他几个方向，直到能够
 *  移动为止。
 *  automove(*fig, *gmap)
 *      自动移动，方向为自己现在的方向。
 *  judgeHit(bx, by, fx, fy)
 *      判断子弹(bx, by)是否击中人形(fx,fy) （实地址）。
 *
 *
 */

#include <QDebug>
#include "gamestart.h"

inline int leftmove(Figure *fig, GameMap *gmap){

    int tempX = fig->getXpos() - MAPUNITSZ / 2 - fig->getSpeed();
    MapElement elem1 = gmap->getMapElem(tempX, fig->getYpos() - MAPUNITSZ / 2);
    MapElement elem2 = gmap->getMapElem(tempX, fig->getYpos() + MAPUNITSZ / 2 - 1);
    bool elem1CanPass = gmap->canPass(elem1);
    bool elem2CanPass = gmap->canPass(elem2);
    bool figInMap = gmap->inMap(tempX, fig->getYpos());

    // 人形左上角不能通过或者左下角不能通过或者越界
    if( !elem1CanPass || !elem2CanPass || !figInMap ){
        //左下角可以通过，尝试将人形对齐到单元格中
        if( elem2CanPass && figInMap ){
            int t1 = fig->getYpos() + MAPUNITSZ / 2 - 1;
            int t2 = t1 + fig->getSpeed();
            t2 = t2 / MAPUNITSZ * MAPUNITSZ;
            fig->move(t2 - t1 - 1, DOWN);
        }
        //左上角可以通过，尝试将人形对齐到单元格中
        else if( elem1CanPass && figInMap ){
            int t1 = fig->getYpos() - MAPUNITSZ / 2;
            int t2 = t1 - fig->getSpeed();
            t2 = (t2 / MAPUNITSZ + 1) * MAPUNITSZ;
            fig->move(t1 - t2, UP);
        }
        tempX += fig->getSpeed();
        tempX = tempX / MAPUNITSZ * MAPUNITSZ + MAPUNITSZ / 2;
        return fig->getXpos() - tempX;
    }
    else {
        return fig->getSpeed();
    }

}

inline int rightmove(Figure *fig, GameMap *gmap){

    int tempX = fig->getXpos() + MAPUNITSZ / 2 + fig->getSpeed() - 1;
    MapElement elem1 = gmap->getMapElem(tempX, fig->getYpos() - MAPUNITSZ / 2);
    MapElement elem2 = gmap->getMapElem(tempX, fig->getYpos() + MAPUNITSZ / 2 - 1);
    bool elem1CanPass = gmap->canPass(elem1);
    bool elem2CanPass = gmap->canPass(elem2);
    bool figInMap = gmap->inMap(tempX, fig->getYpos());

    if( !elem1CanPass || !elem2CanPass || !figInMap ){
        if( elem2CanPass && figInMap ){
            int t1 = fig->getYpos() + MAPUNITSZ / 2 - 1;
            int t2 = t1 + fig->getSpeed();
            t2 = t2 / MAPUNITSZ * MAPUNITSZ;
            fig->move(t2 - t1 - 1, DOWN);
        }
        else if( elem1CanPass && figInMap ){
            int t1 = fig->getYpos() - MAPUNITSZ / 2;
            int t2 = t1 - fig->getSpeed();
            t2 = (t2 / MAPUNITSZ + 1) * MAPUNITSZ;
            fig->move(t1 - t2, UP);
        }
        tempX -= fig->getSpeed();
        tempX = (tempX / MAPUNITSZ) * MAPUNITSZ + MAPUNITSZ / 2;
        return tempX - fig->getXpos();
    }
    else {
        return fig->getSpeed();
    }

}

inline int upmove(Figure *fig, GameMap *gmap){

    int tempY = fig->getYpos() - MAPUNITSZ / 2 - fig->getSpeed();
    MapElement elem1 = gmap->getMapElem(fig->getXpos() - MAPUNITSZ / 2, tempY);
    MapElement elem2 = gmap->getMapElem(fig->getXpos() + MAPUNITSZ / 2 - 1, tempY);
    bool elem1CanPass = gmap->canPass(elem1);
    bool elem2CanPass = gmap->canPass(elem2);
    bool figInMap = gmap->inMap(fig->getXpos(), tempY);

    // 人形左上角不能通过或者右上角不能通过或者越界
    if( !elem1CanPass || !elem2CanPass || !figInMap ){
        //右上角可以通过，尝试将人形对齐到单元格中
        if( elem2CanPass && figInMap ){
            int t1 = fig->getXpos() + MAPUNITSZ / 2 - 1;
            int t2 = t1 + fig->getSpeed();
            t2 = t2 / MAPUNITSZ * MAPUNITSZ;
            fig->move(t2 - t1 - 1, RIGHT);
        }
        //左上角可以通过，尝试将人形对齐到单元格中
        else if( elem1CanPass && figInMap ){
            int t1 = fig->getXpos() - MAPUNITSZ / 2;
            int t2 = t1 - fig->getSpeed();
            t2 = (t2 / MAPUNITSZ + 1) * MAPUNITSZ;
            fig->move(t1 - t2, LEFT);
        }
        tempY += fig->getSpeed();
        tempY = tempY / MAPUNITSZ * MAPUNITSZ + MAPUNITSZ / 2;
        return fig->getYpos() - tempY;
    }
    else {
        return fig->getSpeed();
    }

}

inline int downmove(Figure *fig, GameMap *gmap){

    int tempY = fig->getYpos() + MAPUNITSZ / 2 + fig->getSpeed() - 1;
    MapElement elem1 = gmap->getMapElem(fig->getXpos() - MAPUNITSZ / 2, tempY);
    MapElement elem2 = gmap->getMapElem(fig->getXpos() + MAPUNITSZ / 2 - 1, tempY);
    bool elem1CanPass = gmap->canPass(elem1);
    bool elem2CanPass = gmap->canPass(elem2);
    bool figInMap = gmap->inMap(fig->getXpos(), tempY);

    if( !elem1CanPass || !elem2CanPass || !figInMap ){
        if( elem2CanPass && figInMap ){
            int t1 = fig->getXpos() + MAPUNITSZ / 2 - 1;
            int t2 = t1 + fig->getSpeed();
            t2 = t2 / MAPUNITSZ * MAPUNITSZ;
            fig->move(t2 - t1 - 1, RIGHT);
        }
        else if( elem1CanPass && figInMap ){
            int t1 = fig->getXpos() - MAPUNITSZ / 2;
            int t2 = t1 - fig->getSpeed();
            t2 = (t2 / MAPUNITSZ + 1) * MAPUNITSZ;
            fig->move(t1 - t2, LEFT);
        }
        tempY -= fig->getSpeed();
        tempY = tempY / MAPUNITSZ * MAPUNITSZ + MAPUNITSZ / 2;
        return tempY - fig->getYpos();
    }
    else {
        return fig->getSpeed();
    }

}

inline void GrassCheck(Figure *fig, GameMap *gmap){
    if(gmap->getMapElem(fig->getXpos(), fig->getYpos()) == GRASS)
        fig->setHidden(true);
    else
        fig->setHidden(false);
}

inline void DesertCheck(Figure *fig, GameMap *gmap){
    if(gmap->getMapElem(fig->getXpos(), fig->getYpos()) == DESERT)
        fig->setSlow(true);
    else
        fig->setSlow(false);
}

void gameStart::keyPressEvent(QKeyEvent *event){

    if(gamestate) return;

    switch (event->key()) {
    case Qt::Key_Left:
    {
        fig->move( leftmove(fig, gmap), LEFT);
        fig->setMovie(LEFT, ACT_MOVE);
        GrassCheck(fig, gmap);
        DesertCheck(fig, gmap);
        break;
    }
    case Qt::Key_Right:
    {
        fig->move( rightmove(fig, gmap), RIGHT);
        fig->setMovie(RIGHT, ACT_MOVE);
        GrassCheck(fig, gmap);
        DesertCheck(fig, gmap);
        break;
    }
    case Qt::Key_Down:
    {
        fig->move( downmove(fig, gmap), DOWN);
        fig->setMovie(DOWN, ACT_MOVE);
        GrassCheck(fig, gmap);
        DesertCheck(fig, gmap);
        break;
    }
    case Qt::Key_Up:
    {
        fig->move( upmove(fig, gmap), UP);
        fig->setMovie(UP, ACT_MOVE);
        GrassCheck(fig, gmap);
        DesertCheck(fig, gmap);
        break;
    }
    case Qt::Key_Q:
    {
        if(event->isAutoRepeat()) break;
        fig->setMovie(fig->getDirection(), ACT_FIRE);
        fig->setFire(true);
        break;
    }
    case Qt::Key_W:
    {
        for(int i = 0; i < bombBases.size(); i++){
            if(bombBases[i]->tryGet(fig->getXpos(), fig->getYpos())){
                Bag.push_back(BOMB);
                delete bombBases[i];
                bombBases.removeAt(i);
                hintText->append("系统：\n你获得一枚炸弹，按E键放置.\n");
                hintText->verticalScrollBar()->setSliderPosition(
                            hintText->verticalScrollBar()->maximum());
                break;
            }
        }
        for(Cage *cage : cages){
            if(cage->trySave(fig->getXpos(), fig->getYpos())){
                hintText->append("系统：\n已救援一名人质.\n");
                hintText->verticalScrollBar()->setSliderPosition(
                            hintText->verticalScrollBar()->maximum());
            }
        }
        break;
    }
    case Qt::Key_E:
    {
        for(int i = 0; i < Bag.size(); ++i){
            if(Bag[i] == BOMB){
                Bomb *bomb = new Bomb(fig->getXpos(), fig->getYpos()
                                                  , widget);
                bombs.push_back(bomb);
                Bag.removeAt(i);
            }
        }
    }
    default:
        break;
    }

}

void gameStart::keyReleaseEvent(QKeyEvent *event){

    if(gamestate) return;

    switch (event->key()) {
    case Qt::Key_Left:
    {
        fig->setMovie(LEFT, ACT_WAIT);
        break;
    }
    case Qt::Key_Right:
    {
        fig->setMovie(RIGHT, ACT_WAIT);
        break;
    }
    case Qt::Key_Down:
    {
        fig->setMovie(DOWN, ACT_WAIT);
        break;
    }
    case Qt::Key_Up:
    {
        fig->setMovie(UP, ACT_WAIT);
        break;
    }
    case Qt::Key_Q:
    {
        if(event->isAutoRepeat()) break;
        if(fig->subBullet()){
            fig->setMovie(fig->getDirection(), ACT_WAIT);
            fig->setFire(false);
            generateOneBullet(fig);
            myBulletLabel->setText(QString::number(fig->getBulletNum()));
        }
        else{
            restoreFigBullet(fig);
        }
        break;
    }
    default:
        break;
    }

}

inline void autoMoveExecute( int initDir, Figure *fig, GameMap *gmap ){

    int (*moveTest[4])(Figure*, GameMap*) = {upmove, leftmove, rightmove, downmove};
    DIRECTION dirs[4] = {UP, LEFT, RIGHT, DOWN};
    std::swap(moveTest[0], moveTest[initDir]);
    std::swap(dirs[0], dirs[initDir]);

    int pos1 = (rand() % 3) + 1;
    int pos2 = (rand() % 3) + 1;
    std::swap(moveTest[pos1], moveTest[pos2]);
    std::swap(dirs[pos1], dirs[pos2]);

    int delta = moveTest[0](fig, gmap);
    if(delta == 0){
        int t = 0;
        if(t = moveTest[1](fig, gmap)) fig->move( t, dirs[1]);
        else if(t = moveTest[2](fig, gmap)) fig->move( t, dirs[2]);
        else if(t = moveTest[3](fig, gmap)) fig->move( t, dirs[3]);
    }
    else fig->move( delta, dirs[0]);

}

inline void automove(Figure *fig, GameMap *gmap){

    autoMoveExecute( static_cast<int>(fig->getDirection()), fig, gmap );

}

inline void gameStart::automoveForBoss(Figure *fig, GameMap *gmap){

    if( !this->fig->isHidden() && abs(this->fig->getXpos() - fig->getXpos()) < MAPUNITSZ / 2 ){
        if( this->fig->getYpos() > fig->getYpos() ){
            autoMoveExecute( static_cast<int>(DOWN), fig, gmap );
        }
        else{
            autoMoveExecute( static_cast<int>(UP), fig, gmap );
        }
    }
    else if( !this->fig->isHidden() &&  abs(this->fig->getYpos() - fig->getYpos()) < MAPUNITSZ / 2 ){
        if( this->fig->getXpos() > fig->getXpos() ){
            autoMoveExecute( static_cast<int>(RIGHT), fig, gmap );
        }
        else{
            autoMoveExecute( static_cast<int>(LEFT), fig, gmap );
        }
    }
    else{
        automove(fig, gmap);
    }

}

void gameStart::autocontrol(Figure *fig){
    int ins = rand() % 10;
    if(ins <= 6)
    {
        automove(fig, gmap);
        fig->setMovie(fig->getDirection(), ACT_MOVE);
        GrassCheck(fig, gmap);
        DesertCheck(fig, gmap);
    }
    else if(ins <= 8)
    {
        if(fig->subBullet()){
            fig->setMovie(fig->getDirection(), ACT_FIRE);
            fig->setFire(true);
            generateOneBullet(fig);
        }
        else{
            restoreFigBullet(fig);
        }
    }
    else
    {
        fig->setMovie(fig->getDirection(), ACT_WAIT);
    }

}

void gameStart::autocontrolForBoss(Figure *fig){
    int ins = rand() % 11;
    if(ins <= 6)
    {
        automoveForBoss(fig, gmap);
        fig->setMovie(fig->getDirection(), ACT_MOVE);
        GrassCheck(fig, gmap);
        DesertCheck(fig, gmap);
    }
    else if(ins <= 8)
    {
        if(fig->subBullet()){
            fig->setMovie(fig->getDirection(), ACT_FIRE);
            fig->setFire(true);
            generateOneBullet(fig);
        }
        else{
            restoreFigBullet(fig);
        }
    }
    else if(ins <= 9)
    {
        coverboom(fig, this->fig);
        effects->addEffect(fig->getXpos(), fig->getYpos(), COVERBOOM);
    }
    else
    {
        fig->setMovie(fig->getDirection(), ACT_WAIT);
    }

}

inline bool judgeHit(int bx, int by, int fx, int fy){

    if(fx - MAPUNITSZ / 2 <= bx && bx < fx + MAPUNITSZ / 2 &&
       fy - MAPUNITSZ / 2 <= by && by < fy + MAPUNITSZ / 2){
        return true;
    }
    else
        return false;

}

void gameStart::hitCheck(){

    for(QList<Bullet*>::iterator p = bullets.begin(); p != bullets.end();){
        int id = (*p)->getID();
        int bx = (*p)->getXpos();
        int by = (*p)->getYpos();
        bool hitflag{false};
        if(id == GELIFEN){
            for(QList<Figure*>::iterator q = enemies.begin(); q != enemies.end();){
                Figure *fig = *q;
                if(judgeHit(bx, by, fig->getXpos(), fig->getYpos())){
                    bool deathflag = false;
                    hitflag = true;
                    deathflag = fig->sublife((*p)->gethurt());
                    enemyLifeNumLabel->setText(QString::number(fig->getLife()));
                    if(!deathflag){
                        delete fig;
                        q = enemies.erase(q);
                        break;
                    }
                    else q++;
                }
                else {
                    q++;
                }
            }
        }
        else {
            if(judgeHit(bx, by, fig->getXpos(), fig->getYpos())){
                bool deathflag = false;
                qDebug() << "hit me!\n";
                hitflag = true;
                deathflag = fig->sublife((*p)->gethurt());
                if(!deathflag){
                    emit gameStop(2);
                    break;
                }
            }
        }

        if(hitflag){
            delete *p; p = bullets.erase(p);
            effects->addEffect(bx, by, BULLET1EFFECT);
        }
        else p++;
    }

}
