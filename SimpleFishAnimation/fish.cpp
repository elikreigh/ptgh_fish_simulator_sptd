//Adam Griswold : Version 1.0
//Purpose: basic fish animations (cycles through currently two) and setting fish location
//Date: 12/1/2017
#include "fish.h"
#include <windows.h>

Fish::Fish(int window_width, int window_height){
    this->face_left = true;
    this->face_forward = false;
    sprite_index = 0;
    f_brain = new brain(window_width,window_height);
}

Fish::Fish(Fish *newFish){
    sprite_index = 0;
    f_brain = new brain(newFish->get_brain());
    this->set_left(newFish->get_face_left());
    this->set_forward(newFish->get_face_forward());
}

brain Fish::get_brain(){
    return f_brain;
}

/*Accessors for location and state*/
int Fish::get_x(){
    return ui_fish->x();
}

int Fish::get_y(){
    return ui_fish->y();
}

bool Fish::get_face_left(){
    return face_left;
}

bool Fish::get_face_forward(){
    return face_forward;
}

QLabel* Fish::get_label(){
    return ui_fish;
}

float Fish::get_hunger(){
    return f_brain->getHunger();
}

void Fish::set_fish(QLabel *fish){
    ui_fish = fish;
    ui_fish->setPixmap(QPixmap(":/pictures/FishIdle.png"));
    ui_fish->setGeometry(990, 250, 111, 71);
}

void Fish::brain_setup(){
    f_brain->setX(1050);
    f_brain->setY(300);
    f_brain->setDestination();
    f_brain->set_fwidth(111);
    f_brain->set_fheight(71);
}

void Fish::sprite_setup(){
    ui_fish->setPixmap(QPixmap(":/pictures/FishFinUp.png"));
}

/*Mutator for state*/
void Fish::logic(Interferences* pile[3]){
    this->f_brain->decisionState(pile);
    this->set_left(f_brain->getDirection());
    this->set_forward(f_brain->getDirection());
    this->sprite_swim();
}

void Fish::set_left(bool lft){
    face_left = lft;
}

void Fish::set_forward(bool frwd){
    face_forward = frwd;
}

void Fish::set_left(Move_Type dir){
    if(dir == Left || dir == UpLeft || dir == DownLeft){
        face_left = true;
    }
    else if(dir == Right || dir == UpRight || dir == DownRight){
        face_left = false;
    } else {
        face_left = face_left;
    }
}

void Fish::set_forward(Move_Type dir){
    if(dir == TLeft || dir == TUpLeft || dir == TDownLeft || dir == TUp || dir == TDown){
        face_forward = true;
    }
    else if(dir == ARight || dir == AUpRight || dir == ADownRight || dir == AUp || dir == ADown){
        face_forward = false;
    } else {
        face_forward = face_forward;
    }
}

void Fish::frighten(QPoint mouse_cord){
    f_brain->runFromMouseClick(mouse_cord);
    f_brain->set_state(Scared);
}

void Fish::feeding(){
    if(f_brain->getHunger() > .25){
        f_brain->set_state(Feeding);
    }
}

void Fish::swim(){
    /*Move_Type direction = f_brain->decisionDirection();
    f_brain->move(direction);*/
}

void Fish::swim(Move_Type direction){
    static int cycle = 0;
    this->cycle_sprite();
    f_brain->decisionDirection(direction);
    ui_fish->move(f_brain->getX(), f_brain->getY());
}

void Fish::sprite_swim(){
    static int cycle = 0;
    if(cycle >= 10){
        this->cycle_sprite();
        cycle=0;
    }
    cycle++;

    ui_fish->move(f_brain->getX(), f_brain->getY());
}

void Fish::test_swim(Move_Type direction){
    /*f_brain->move(direction);*/
}

void Fish::cycle_sprite(){
    //Default sprite is idle, toggles between fin states
    //Flips QPixmap if right
    //Frames will be moved to an attribute of fish and not individually cycled

    /*qDebug() << "depth: " << f_brain->getDepth();
    qDebug() << "prevdepth: " <<f_brain->getPrevDepth();
    qDebug() << "destdepht: " <<f_brain->getDestDepth();
    qDebug() << "\n";*/

    if(f_brain->getDepth() < f_brain->getPrevDepth()){
        ui_fish->resize(ui_fish->width()+4, ui_fish->height()+2);
        qDebug() << "width: " << ui_fish->width();
        qDebug() << "height: " << ui_fish->height();
        if(sprite_index == 1){
            ui_fish->setPixmap(QPixmap(":/pictures/ForwardFishFinUp.png"));
        }
        else{
            ui_fish->setPixmap(QPixmap(":/pictures/ForwardFishIdle.png"));
        }
        this->f_brain->resetPrevDepth();
    }
    else if(f_brain->getDepth() > f_brain->getPrevDepth()){
        ui_fish->resize(ui_fish->width()-4, ui_fish->height()-2);
        qDebug() << "width: " << ui_fish->width();
        qDebug() << "height: " << ui_fish->height();
        if(sprite_index == 1){
            ui_fish->setPixmap(QPixmap(":/pictures/BackFishFinUp.png"));
        }
        else{
            ui_fish->setPixmap(QPixmap(":/pictures/BackFishIdle.png"));
        }
        this->f_brain->resetPrevDepth();
    }
    else {
        qDebug() << "width: " << ui_fish->width();
        qDebug() << "height: " << ui_fish->height();
        if(face_left){
            if(sprite_index == 1){
                ui_fish->setPixmap(QPixmap(":/pictures/FishFinUp.png"));
            }
            else{
                ui_fish->setPixmap(QPixmap(":/pictures/FishIdle.png"));
            }
        }
        else if (!face_left){
            if(sprite_index == 1){
                ui_fish->setPixmap(QPixmap::fromImage(QPixmap(":/pictures/FishFinUp.png").toImage().mirrored(true, false)));
            }
            else{
                ui_fish->setPixmap(QPixmap::fromImage(QPixmap(":/pictures/FishIdle.png").toImage().mirrored(true, false)));
            }
        }
    }

    sprite_index++;
    if(sprite_index >= 2)
        sprite_index = 0;
}

bool Fish::eat_food(Interferences *pile[3]){
    bool ans = false;
    if(!pile[2]->get_label()->isHidden()){
        int food_right = pile[2]->get_right();
        int food_left = pile[2]->get_left();
        int food_top = pile[2]->get_top();
        int food_bottom = pile[2]->get_bottom();
        if((f_brain->getLeft() <= (food_left+25) && f_brain->getLeft() >= (food_left-25)) && (f_brain->getTop() <= (food_top+25) && f_brain->getTop() >= (food_top-25))){
            ans = true;
            f_brain->set_state(DecideMove);
            f_brain->reduce_hunger();
        }
    }
    return ans;
}
