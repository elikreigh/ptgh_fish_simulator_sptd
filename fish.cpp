//Adam Griswold : Version 1.0
//Purpose: basic fish animations (cycles through currently two) and setting fish location
//Date: 12/1/2017
#include "fish.h"

Fish::Fish(int window_width, int window_height){
    this->face_left = true;
    sprite_index = 0;
    f_brain = new brain(window_width,window_height);
}

Fish::Fish(Fish *newFish){
    this->face_left = true;
    sprite_index = 0;
    f_brain = new brain(newFish->get_brain());
    set_left(newFish->get_face_left());
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

void Fish::set_fish(QLabel *fish){
    ui_fish = fish;
}

void Fish::brain_setup(){
    f_brain->setX(ui_fish->x());
    f_brain->setY(ui_fish->y());
    f_brain->set_fwidth(ui_fish->width());
    f_brain->set_fheight(ui_fish->height());
}

/*Mutator for state*/
void Fish::set_left(bool lft){
    face_left = lft;
}

void Fish::swim(){
    cycle_sprite();
    f_brain->decision();
    ui_fish->move(f_brain->getX(), f_brain->getY());
}

void Fish::swim(Move_Type direction){
    cycle_sprite();
    f_brain->move(direction);
    ui_fish->move(f_brain->getX(), f_brain->getY());
}

/*Idle Animation*/
void Fish::bob(){
    if(f_brain->getState() == Idle){
        ui_fish->move(ui_fish->x(), ui_fish->y());
    }
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
