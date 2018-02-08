#ifndef FISH_H
#define FISH_H

#include <QtUiTools>
#include <QString>
#include <QPixmap>
#include <QImage>
#include <QLabel>
#include "brain.h"
#include "pillar.h"
#include "fishfood.h"

class Fish
{
public:
    Fish(int window_width, int window_height);
    Fish(Fish *newFish);

    void swim();
    void swim(Move_Type direction);
    void sprite_swim();
    void test_swim(Move_Type direction);
    void set_fish(QLabel *fish);
    void cycle_sprite();
    int get_x();
    int get_y();
    bool get_face_left();
    bool get_face_forward();
    QLabel* get_label();
    float get_hunger();
    void set_left(bool lft);
    void set_left(Move_Type dir);
    void set_forward(bool frwd);
    void set_forward(Move_Type dir);
    void frighten(QPoint mouse_cord);
    void feeding();
    void pulled();
    brain get_brain();
    void brain_setup();
    void sprite_setup();
    bool no_over_lap(Interferences* pile[4]);
    bool eat_food(Interferences* pile[4]);
    bool eat_hook(Interferences* pile[4]);
    Avoidance try_and_eat(Interferences* pile[4]);

    void logic(Interferences* pile[4]);

private:
    QLabel *ui_fish;
    QPixmap current_pixmap;
    int sprite_index;
    bool face_left;
    bool face_forward;
    brain *f_brain;
};

#endif // FISH_H
