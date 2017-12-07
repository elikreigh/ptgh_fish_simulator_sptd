#include "fishfood.h"

FishFood::FishFood()
{
    sprite_index = 0;
    speed = 1;
}

void FishFood::sink(){
    if(!ui_fish_food->isHidden()){
        ui_fish_food->move(ui_fish_food->x(), ui_fish_food->y()+speed);
        if(check_height()){
            speed=0;
        }
    }
}

void FishFood::set_food(QLabel *food){
    ui_fish_food = food;
    ui_fish_food->hide();
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
    if(ui_fish_food->y() > 540){
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
}
