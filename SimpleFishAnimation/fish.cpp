//Adam Griswold : Version 1.0
//Purpose: basic fish animations (cycles through currently two) and setting fish location
//Date: 12/1/2017
#include "fish.h"
#include <windows.h>

Fish::Fish(int window_width, int window_height){
    this->face_left = true;
    sprite_index = 0;
    f_brain = new brain(window_width,window_height);
}

Fish::Fish(Fish *newFish){
    face_left = true;
    sprite_index = 0;
    f_brain = new brain(newFish->get_brain());
    this->set_left(newFish->get_face_left());
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

QLabel* Fish::get_label(){
    return ui_fish;
}

void Fish::set_fish(QLabel *fish){
    ui_fish = fish;
    ui_fish->setPixmap(QPixmap(":/pictures/FishIdle.png"));
    ui_fish->setGeometry(1050, 300, ui_fish->width(), ui_fish->height());
}

void Fish::brain_setup(){
    f_brain->setX(1050);
    f_brain->setY(300);
    f_brain->setDestination();
    f_brain->set_fwidth(ui_fish->width());
    f_brain->set_fheight(ui_fish->height());
}

void Fish::sprite_setup(){
    ui_fish->setPixmap(QPixmap(":/pictures/FishFinUp.png"));
    ui_fish->move(f_brain->getX(), f_brain->getY());
}

/*Mutator for state*/
void Fish::logic(Interferences* pile[3]){
    this->f_brain->decisionState(pile);
    this->set_left(f_brain->getDirection());
    this->sprite_swim();
}

void Fish::set_left(bool lft){
    face_left = lft;
}

void Fish::set_left(Move_Type dir){
    if(dir == Left || dir == UpLeft || dir == DownLeft || dir == ALeft || dir == AUpLeft || dir == ADownLeft || dir == TLeft || dir == TUpLeft || dir == TDownLeft){
        face_left = true;
    }
    else if(dir == Right || dir == UpRight || dir == DownRight || dir == ARight || dir == AUpRight || dir == ADownRight || dir == TRight || dir == TUpRight || dir == TDownRight){
        face_left = false;
    } else {
        face_left = face_left;
    }
}

void Fish::frighten(QPoint mouse_cord){
    f_brain->setDestination(mouse_cord);
    f_brain->set_state(Scared);
}

void Fish::feeding(){
    f_brain->set_state(Feeding);
}

void Fish::swim(){
    /*Move_Type direction = f_brain->decisionDirection();
    f_brain->move(direction);*/
}

void Fish::swim(Move_Type direction){
    this->cycle_sprite();
    f_brain->decisionDirection(direction);
    ui_fish->move(f_brain->getX(), f_brain->getY());
}

void Fish::sprite_swim(){
    this->cycle_sprite();
    ui_fish->move(f_brain->getX(), f_brain->getY());
}

void Fish::test_swim(Move_Type direction){
    /*f_brain->move(direction);*/
}

void Fish::run(QPoint mouse_cord){
    /*enum Move_Type direction;
    if(ui_fish->x() < mouse_cord.x() && ui_fish->y() < mouse_cord.y()){
        direction = UpLeft;
    }
    else if(ui_fish->x() == mouse_cord.x() && ui_fish->y() > mouse_cord.y()){
        direction = Up;
    }
    else if(ui_fish->x() > mouse_cord.x() && ui_fish->y() > mouse_cord.y()){
        direction = UpRight;
    }
    else if(ui_fish->x() > mouse_cord.x() && ui_fish->y() == mouse_cord.y()){
        direction = Right;
    }
    else if(ui_fish->x() < mouse_cord.x() && ui_fish->y() < mouse_cord.y()){
        direction = DownRight;
    }
    else if(ui_fish->x() == mouse_cord.x() && ui_fish->y() < mouse_cord.y()){
        direction = Down;
    }
    else if(ui_fish->x() > mouse_cord.x() && ui_fish->y() < mouse_cord.y()){
        direction = DownLeft;
    }
    else if(ui_fish->x() < mouse_cord.x() && ui_fish->y() == mouse_cord.y()){
        direction = Left;
    }

    Fish *test_fish = new Fish(this);
    test_fish->swim(direction);
    if(test_fish->no_over_lap(pile)){
        if(direction == Left || direction == UpLeft || direction == DownLeft){
            this->set_left(true);
        }
        else if(direction == Right || direction == UpRight || direction == DownRight){
            this->set_left(false);
        } else {
            this->set_left(this->get_face_left());
        }
        this->get_brain().set_direction(direction);
    }
    test_fish->~Fish();*/
}

void Fish::cycle_sprite(){
    //Default sprite is idle, toggles between fin states
    //Flips QPixmap if right
    //Frames will be moved to an attribute of fish and not individually cycled

    if(f_brain->getDepth() < f_brain->getPrevDepth()){
        ui_fish->resize(ui_fish->width()+2, ui_fish->height()+1);
        this->f_brain->resetPrevDepth();
    }
    else if(f_brain->getDepth() > f_brain->getPrevDepth()){
        ui_fish->resize(ui_fish->width()-2, ui_fish->height()-1);
        this->f_brain->resetPrevDepth();
    }

    if(face_left){
        if(sprite_index == 1){
            ui_fish->setPixmap(QPixmap(":/pictures/FishFinUp.png"));
        }
        else{
            ui_fish->setPixmap(QPixmap(":/pictures/FishIdle.png"));
        }
    }
    else{
        if(sprite_index == 1){
            ui_fish->setPixmap(QPixmap::fromImage(QPixmap(":/pictures/FishFinUp.png").toImage().mirrored(true, false)));
        }
        else{
            ui_fish->setPixmap(QPixmap::fromImage(QPixmap(":/pictures/FishIdle.png").toImage().mirrored(true, false)));
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
        }
    }
    return ans;
}
