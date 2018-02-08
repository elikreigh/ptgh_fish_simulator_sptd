#ifndef HOOK_H
#define HOOK_H

#include "interferences.h"

enum  Hook_State {Empty, Full};

class Hook :  public Interferences
{
public:
    Hook();
    void logic(int fish_x);
    void set_hook(QLabel *hook);
    void cycle_sprite();
    bool check_height();
    void hide_hook();
    void show_hook();
    void eaten();
    void new_spawn();
    //Looking through the three pile objects will include current object
    bool no_over_lap(Interferences *pile[4]);

private:
    QLabel *ui_hook;
    QPixmap current_pixmap;
    Hook_State state;
    int sprite_index;
    int speed;
};

#endif // HOOK_H
