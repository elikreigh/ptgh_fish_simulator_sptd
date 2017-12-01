//Adam Griswold : Version 1.0
//Purpose: basic fish animations (cycles through currently two) and setting fish location
//Date: 12/1/2017
#include "fish.h"

Fish::Fish(){
    left = true;
    sprite_index = 0;
}

/*Accessors for location and state*/
int Fish::get_x(){
    return ui_fish->x();
}

int Fish::get_y(){
    return ui_fish->y();
}

bool Fish::get_left(){
    return left;
}

void Fish::set_fish(QLabel *fish){
    ui_fish = fish;
}

/*Mutator for state*/
void Fish::set_left(bool lft){
    left = lft;
}

void Fish::swim(int destX, int destY){
    cycle_sprite();
    ui_fish->setGeometry(ui_fish->x()+destX, ui_fish->y()+destY, ui_fish->width(), ui_fish->height());
}

/*Idle Animation*/
void Fish::bob(){
    ui_fish->move(ui_fish->x(), ui_fish->y());
}

void Fish::origin(){
    ui_fish->setGeometry(1050, 300, ui_fish->width(), ui_fish->height());
}

void Fish::cycle_sprite(){
    //Default sprite is idle, toggles between fin states
    //Flips QPixmap if right
    //Frames will be moved to an attribute of fish and not individually cycled
    if(left){
        if(sprite_index == 1){
            ui_fish->setPixmap(QPixmap("../Resources/FishFinUp.png"));
        }
        else{
            ui_fish->setPixmap(QPixmap("../Resources/FishIdle.png"));
        }
    }
    else{
        if(sprite_index == 1){
            ui_fish->setPixmap(QPixmap::fromImage(QPixmap("../Resources/FishFinUp.png").toImage().mirrored(true, false)));
        }
        else{
            ui_fish->setPixmap(QPixmap::fromImage(QPixmap("../Resources/FishIdle.png").toImage().mirrored(true, false)));
        }
    }

    sprite_index++;
    if(sprite_index >= 2)
        sprite_index = 0;
}
