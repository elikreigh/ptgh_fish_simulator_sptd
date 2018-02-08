#include "hook.h"

Hook::Hook(){
    type = Hooks;
    state = Empty;
    sprite_index = 0;
    speed = 0;
}

void Hook::logic(int fish_x){
    if(!ui_hook->isHidden()){
        if(state == Empty){
            ui_hook->move(fish_x, ui_hook->y()+speed);
            if(check_height()){
                speed = 0;
            }
        }
        else if(state == Full){
            ui_hook->move(ui_hook->x(), ui_hook->y()-speed);
        }
    }
}

void Hook::set_hook(QLabel *hook){
    ui_hook = hook;
    this->set_label(ui_hook);
    hide_hook();
}

void Hook::cycle_sprite(){
    //sprite for hook needs to be drawn...
    /*
    if(!ui_hook->isHidden()){
        if(sprite_index == 1){
            ui_hook->setPixmap(QPixmap("../Resources/FishFood1.png"));
        }
        else{
            ui_hook->setPixmap(QPixmap("../Resources/FishFood2.png"));
        }
        sprite_index++;
        if(sprite_index >= 2)
            sprite_index = 0;
    }*/
}

bool Hook::check_height(){
    bool max_height_reached;
    //height of hook is something, once hook reached floor return true
    if(ui_hook->y() > 530){
        max_height_reached = true;
    }
    else{
        max_height_reached = false;
    }
    return max_height_reached;
}

void Hook::hide_hook(){
    ui_hook->hide();
}

void Hook::show_hook(){
    ui_hook->show();
    speed = 2;
}

void Hook::eaten(){
    state = Full;
    speed = 3;
}

void Hook::new_spawn(){
    ui_hook->move(rand()%900+100, rand()%10-30);
    this->set_depth(rand()%10);
}

bool Hook::no_over_lap(Interferences *pile[4]){
    bool ans = true;
    for(int i = 0; i <= 3; i++){
        int pile_right = pile[i]->get_right();
        int pile_left = pile[i]->get_left();
        int pile_top = pile[i]->get_top();
        if((this->get_left() == pile_right && this->get_bottom() <= pile_top) || (this->get_right() == pile_left && this->get_bottom() <= pile_top) || (this->get_bottom() == pile_top && this->get_right() >= pile_left && this->get_left() <= pile_right)){
            ans = false;
        }
    }
    return ans;
}
