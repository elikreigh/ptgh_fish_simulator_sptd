#include "pillar.h"

Pillar::Pillar()
{

}

int Pillar::get_right(){
    return ui_pillar->x()+ui_pillar->width();
}
int Pillar::get_left(){
    return ui_pillar->x();
}
int Pillar::get_top(){
    return ui_pillar->y();
}

void Pillar::set_pillar(QLabel *pillar){
    ui_pillar = pillar;
}

QLabel* Pillar::get_pillar(){
    return ui_pillar;
}
