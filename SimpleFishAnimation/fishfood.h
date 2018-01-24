#ifndef FISHFOOD_H
#define FISHFOOD_H

#include "interferences.h"
#include "pillar.h"

class FishFood : public Interferences
{
public:
    FishFood();
    void sink();
    void set_food(QLabel *food);
    void cycle_sprite();
    bool check_height();
    void hide_food();
    void show_food();
    void eaten();
    void new_spawn();
    //Looking through the three pile objects will include current object
    bool no_over_lap(Interferences *pile[3]);

private:
    QLabel *ui_fish_food;
    QPixmap current_pixmap;
    int sprite_index;
    int speed;
};

#endif // FISHFOOD_H
