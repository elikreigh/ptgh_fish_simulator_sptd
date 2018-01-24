#include "fishfood.h"

FishFood::FishFood()
{
    type = Food;
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
    this->set_label(ui_fish_food);
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
    this->set_depth(rand()%10);
}

bool FishFood::no_over_lap(Interferences *pile[3]){
    bool ans = true;
    for(int i = 0; i < 3; i++){
        int pile_right = pile[i]->get_right();
        int pile_left = pile[i]->get_left();
        int pile_top = pile[i]->get_top();
        if((this->get_left() == pile_right && this->get_bottom() <= pile_top) || (this->get_right() == pile_left && this->get_bottom() <= pile_top) || (this->get_bottom() == pile_top && this->get_right() >= pile_left && this->get_left() <= pile_right)){
            ans = false;
        }
    }
    return ans;
}
