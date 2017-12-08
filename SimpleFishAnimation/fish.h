#ifndef FISH_H
#define FISH_H

#include <QtUiTools>
#include <QString>
#include <QPixmap>
#include <QImage>
#include <QLabel>
#include "brain.h"
#include "pillar.h"

class Fish
{
public:
    Fish(int window_width, int window_height);
    Fish(Fish *newFish);

    void swim();
    void swim(Move_Type direction);
    void bob();
    void origin();
    void set_fish(QLabel *fish);
    void cycle_sprite();
    int get_x();
    int get_y();
    bool get_face_left();
    void set_left(bool lft);
    brain get_brain();
    void brain_setup();
    bool no_over_lap(Pillar* pile[2]);

private:
    QLabel *ui_fish;
    QPixmap current_pixmap;
    int sprite_index;
    bool face_left;
    brain *f_brain;
    int counter;
};

#endif // FISH_H
