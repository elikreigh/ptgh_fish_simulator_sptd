#ifndef BUBBLES_H
#define BUBBLES_H

#include <QtUiTools>
#include <QString>
#include <QPixmap>
#include <QImage>
#include <cstdlib>

class Bubbles
{
public:
    Bubbles();
    void set_bubble(QLabel *bubble);
    void cycle_sprite();

private:
    QLabel *ui_bubble;
    QPixmap current_pixmap;
    int sprite_index;
};

#endif // BUBBLES_H
