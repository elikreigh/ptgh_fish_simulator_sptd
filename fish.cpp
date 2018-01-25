//Adam Griswold : Version 1.0
//Purpose: basic fish animations (cycles through currently two) and setting fish location
//Date: 12/1/2017
#include "fish.h"
#include "mainwindow.h"

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
    counter = 0;
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
    origin();
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
    Move_Type direction = f_brain->decisionDirection();
    f_brain->move(direction);
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
    if(face_left){
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

bool Fish::no_over_lap(Pillar *pile[2]){
    bool ans = true;
    for(int i = 0; i < 2; i++){
        int pile_right = pile[i]->get_right();
        int pile_left = pile[i]->get_left();
        int pile_top = pile[i]->get_top();
        if((f_brain->getLeft() == pile_right && f_brain->getBottom() >= pile_top) || (f_brain->getRight() == pile_left && f_brain->getBottom() >= pile_top) || (f_brain->getBottom() == pile_top && f_brain->getRight() >= pile_left && f_brain->getLeft() <= pile_right)){
            ans = false;
        }
    }
    return ans;
}

bool Fish::eat_food(FishFood *food){
    bool ans = false;
    if(!food->getUI()->isHidden()){
        int food_right = food->getRight();
        int food_left = food->getLeft();
        int food_top = food->getTop();
        int food_bottom = food->getBottom();
        if((f_brain->getLeft() <= (food_left+25) && f_brain->getLeft() >= (food_left-25)) && (f_brain->getBottom() <= (food_bottom+25) && f_brain->getBottom() >= (food_bottom-25))){
            ans = true;
        }
    }
    return ans;
}

void Fish::fish_logic(Fish* mainFish, Pillar *pile[], FishFood* food, QMediaPlayer* sound_fx){
    Fish *test_fish = new Fish(mainFish);
    enum Move_Type direction;
    test_fish->swim();
    direction = (test_fish->get_brain()).getDirection();
    if(test_fish->no_over_lap(pile)){
        if(direction == Left || direction == UpLeft || direction == DownLeft){
            mainFish->set_left(true);
        }
        else if(direction == Right || direction == UpRight || direction == DownRight){
            mainFish->set_left(false);
        } else {
            mainFish->set_left(mainFish->get_face_left());
        }
        mainFish->get_brain().set_direction(direction);
        mainFish->swim(direction);
        if(mainFish->eat_food(food)){
            food->eaten();
            sound_fx->setMedia(QUrl("qrc:/sound/munch.mp3"));
            sound_fx->play();
        }
    }
    test_fish->~Fish();
    //mainFish->swim(DownRight);
}
