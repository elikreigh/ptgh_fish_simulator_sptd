#ifndef FLOATINGBUBBLES_H
#define FLOATINGBUBBLES_H

#include <QtUiTools>
#include <QString>
#include <QPixmap>
#include <QImage>
#include <cstdlib>
#include <QLabel>

class FloatingBubbles
{
public:
    FloatingBubbles();
    void float_up();
    void set_bubble(QLabel *bubble);
    void cycle_sprite();
    bool check_height();

private:
    QLabel *ui_floating_bubble;
    QPixmap current_pixmap;
    int sprite_index;
    int speed;
};

#endif // FLOATINGBUBBLES_H
