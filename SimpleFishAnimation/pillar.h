#ifndef PILLAR_H
#define PILLAR_H

#include <QtUiTools>
#include <QString>
#include <QPixmap>
#include <QImage>
#include <cstdlib>
#include <QLabel>

class Pillar
{
public:
    Pillar();
    int get_right();
    int get_left();
    int get_top();
    void set_pillar(QLabel *pillar);
    QLabel* get_pillar();

private:
    QLabel *ui_pillar;
    QPixmap current_pixmap;
    int sprite_index;
};

#endif // PILLAR_H
