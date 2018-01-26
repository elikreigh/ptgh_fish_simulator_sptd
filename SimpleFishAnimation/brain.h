#ifndef BRAIN_H
#define BRAIN_H

#include <QPoint>
#include "pillar.h"
#include "fishfood.h"

enum  Move_State {Move, Idle, DecideMove, Scared, Feeding};
enum Move_Type {Left, UpLeft, Up, UpRight, Right, DownRight, Down, DownLeft,
                ALeft, AUpLeft, AUp, AUpRight, ARight, ADownRight, ADown, ADownLeft,
                TLeft, TUpLeft, TUp, TUpRight, TRight, TDownRight, TDown, TDownLeft,};
class brain
{
public:
    brain();
    brain(int width, int height);
    brain(brain *other);

    void changeState(int input, Interferences* pile[3]);
    void moveTypeState(int input);
    Move_State getState();
    Move_Type getDirection();
    Move_Type decisionDirection(int driver);
    void decisionDirection();
    void decisionState(Interferences* pile[3]);

    void move(Move_Type dir);
    void move(Interferences* pile[3]);
    void idle_ani();
    void setX(int new_x);
    void setY(int new_y);
    void setDestination();
    void setDestination(QPoint dest);
    void setDestination(Interferences* pile[3]);
    void set_fwidth(int width);
    void set_fheight(int height);
    void set_direction(Move_Type direction);
    void set_state(Move_State state);
    int getDepth();
    int getPrevDepth();
    void setDepth(int dpth);
    void setPrevDepth(int dpth);
    void resetPrevDepth();
    int getX();
    int getY();
    int getTop();
    int getBottom();
    int getLeft();
    int getRight();

    void increase_hunger();
    void reduce_hunger();
    float getHunger();

    QPoint get_destination();

    bool no_over_lap(Interferences* pile[3]);

private:
    bool isFood;
    enum Move_State current_state;
    enum Move_Type direction;

    QPoint place;
    QPoint destination;

    int destdepth;
    int depth;
    int prevdepth;
    int max_height;
    int max_width;
    int fish_height;
    int fish_width;
    int bob_counter;
    int fish_speed;
    float hunger;
};

#endif // BRAIN_H
