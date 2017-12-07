#include "bubbles.h"

Bubbles::Bubbles()
{
    sprite_index = 0;
}

void Bubbles::set_bubble(QLabel *bubble){

    ui_bubble = bubble;
}

void Bubbles::cycle_sprite(){
    if(sprite_index == 1){
        ui_bubble->setPixmap(QPixmap("../Resources/BubblesFrame1.png"));
    }
    else{
        ui_bubble->setPixmap(QPixmap("../Resources/BubblesFrame2.png"));
    }
    sprite_index++;
    if(sprite_index >= 2)
        sprite_index = 0;
}
