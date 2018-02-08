#ifndef INTERFERENCES_H
#define INTERFERENCES_H

#include <QtUiTools>
#include <QString>
#include <QPixmap>
#include <QImage>
#include <cstdlib>

enum Avoidance {Food, Obstical, Hooks, Null};
class Interferences
{
public:
    Interferences();
    int get_depth();
    int get_right();
    int get_left();
    int get_top();
    int get_bottom();
    Avoidance get_type();
    Avoidance type;
    void set_depth(int dpth);
    void set_label(QLabel *label);
    QLabel* get_label();

private:
    QLabel *ui;
    QPixmap current_pixmap;
    int sprite_index;
    int depth;
};

#endif // INTERFERENCES_H
