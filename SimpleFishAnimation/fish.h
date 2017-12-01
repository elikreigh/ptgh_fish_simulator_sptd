#ifndef FISH_H
#define FISH_H

#include <QtUiTools>
#include <QString>
#include <QPixmap>
#include <QImage>

class Fish
{
public:
    Fish();
    void swim(int dest_x, int dest_y);
    void bob();
    void origin();
    void set_fish(QLabel *fish);
    void cycle_sprite();
    int get_x();
    int get_y();
    bool get_left();
    void set_left(bool lft);

private:
    QLabel *ui_fish;
    QPixmap current_pixmap;
    int sprite_index;
    bool left;
};

#endif // FISH_H
