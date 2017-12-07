#include "floatingbubbles.h"

FloatingBubbles::FloatingBubbles()
{
    sprite_index = 0;
    speed = (rand()%5+1);
}

void FloatingBubbles::float_up(){
    ui_floating_bubble->move(ui_floating_bubble->x(), ui_floating_bubble->y()-speed);
    if(check_height()){
        //destroy bubble & "game" will spawn a new one
        //so that bubbles do not deal with spawning new bubbles
        //ui_floating_bubble->deleteLater();
        ui_floating_bubble->move((rand()%1000), ui_floating_bubble->y()+1000);
        speed = (rand()%5+1);
    }
}

void FloatingBubbles::set_bubble(QLabel *bubble){

    ui_floating_bubble = bubble;
}

void FloatingBubbles::cycle_sprite(){
    if(sprite_index == 1){
        ui_floating_bubble->setPixmap(QPixmap("../Resources/BubbleBasic1.png"));
    }
    else{
        ui_floating_bubble->setPixmap(QPixmap("../Resources/BubbleBasic2.png"));
    }
    sprite_index++;
    if(sprite_index >= 2)
        sprite_index = 0;
}

bool FloatingBubbles::check_height(){
    bool max_height_reached;
    //height of bubble is 31, once bubble is fully out of screen return true
    if(ui_floating_bubble->y() < -30){
        max_height_reached = true;
    }
    else{
        max_height_reached = false;
    }
    return max_height_reached;
}
