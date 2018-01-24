#include "interferences.h"

Interferences::Interferences()
{
    depth = 5;
}

int Interferences::get_depth(){
    return depth;
}

void Interferences::set_depth(int dpth){
    depth = dpth;
}

int Interferences::get_right(){
    return ui->x()+ui->width();
}

int Interferences::get_left(){
    return ui->x();
}

int Interferences::get_top(){
    return ui->y();
}

int Interferences::get_bottom(){
    return ui->y()+ui->height();
}

Avoidance Interferences::get_type(){
    return type;
}

void Interferences::set_label(QLabel *label){
    ui = label;
}

QLabel* Interferences::get_label(){
    return ui;
}
