#ifndef FISHFOOD_H
#define FISHFOOD_H

#include <QtUiTools>
#include <QString>
#include <QPixmap>
#include <QImage>
#include <cstdlib>
#include "pillar.h"

class FishFood
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
    bool no_over_lap(Pillar *pile[2]);
    int getLeft();
    int getRight();
    int getBottom();
    int getTop();

private:
    QLabel *ui_fish_food;
    QPixmap current_pixmap;
    int sprite_index;
    int speed;
};

#endif // FISHFOOD_H
