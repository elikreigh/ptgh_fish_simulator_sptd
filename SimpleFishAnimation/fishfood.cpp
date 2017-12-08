#include "fishfood.h"

FishFood::FishFood()
{
    sprite_index = 0;
    speed = 0;
}

void FishFood::sink(){
    if(!ui_fish_food->isHidden()){
        ui_fish_food->move(ui_fish_food->x(), ui_fish_food->y()+speed);
        if(check_height()){
            speed = 0;
        }
    }
}

void FishFood::set_food(QLabel *food){
    ui_fish_food = food;
    hide_food();
}

void FishFood::cycle_sprite(){
    if(!ui_fish_food->isHidden()){
        if(sprite_index == 1){
            ui_fish_food->setPixmap(QPixmap("../Resources/FishFood1.png"));
        }
        else{
            ui_fish_food->setPixmap(QPixmap("../Resources/FishFood2.png"));
        }
        sprite_index++;
        if(sprite_index >= 2)
            sprite_index = 0;
    }
}

bool FishFood::check_height(){
    bool max_height_reached;
    //height of food is 41, once food reached floor return true
    if(ui_fish_food->y() > 530){
        max_height_reached = true;
    }
    else{
        max_height_reached = false;
    }
    return max_height_reached;
}

void FishFood::hide_food(){
    ui_fish_food->hide();
}

void FishFood::show_food(){
    ui_fish_food->show();
    speed = 1;
}

void FishFood::eaten(){
    hide_food();
    new_spawn();
}

void FishFood::new_spawn(){
    ui_fish_food->move(rand()%900+100, rand()%10-30);
}

int FishFood::getLeft(){
    return ui_fish_food->x();
}

int FishFood::getRight(){
    return ui_fish_food->x()+ui_fish_food->width();
}

int FishFood::getBottom(){
    return ui_fish_food->y()+ui_fish_food->height();
}

int FishFood::getTop(){
    return ui_fish_food->y();
}

QLabel* FishFood::getUI(){
    return ui_fish_food;
}

bool FishFood::no_over_lap(Pillar *pile[2]){
    bool ans = true;
    for(int i = 0; i < 2; i++){
        int pile_right = pile[i]->get_right();
        int pile_left = pile[i]->get_left();
        int pile_top = pile[i]->get_top();
        if((getLeft() == pile_right && getBottom() <= pile_top) || (getRight() == pile_left && getBottom() <= pile_top) || (getBottom() == pile_top && getRight() >= pile_left && getLeft() <= pile_right)){
            ans = false;
        }
    }
    return ans;
}
