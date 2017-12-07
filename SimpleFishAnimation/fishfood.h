#ifndef FISHFOOD_H
#define FISHFOOD_H

#include <QtUiTools>
#include <QString>
#include <QPixmap>
#include <QImage>
#include <cstdlib>

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

private:
    QLabel *ui_fish_food;
    QPixmap current_pixmap;
    int sprite_index;
    int speed;
};

#endif // FISHFOOD_H
