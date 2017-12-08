#ifndef BRAIN_H
#define BRAIN_H

enum  Move_State {Move, Idle, Feed};
enum Move_Type {Up, Down, Left, Right, Forward, Back,
              UpBack, UpForward, UpRight, UpLeft, UpBackRight, UpBackLeft, UpForwardRight,
              UpForwardLeft, DownBack, DownForward, DownRight, DownLeft, DownBackRight,
              DownBackLeft, DownForwardRight, DownForwardLeft, ForwardRight, ForwardLeft,
              BackRight, BackLeft};
class brain
{
public:
    brain();
    brain(int width, int height);
    brain(brain *other);
    Move_State moveState(int input);
    Move_Type moveTypeState(int input);
    Move_State getState();
    Move_Type getDirection();
    void decision();
    void move(Move_Type dir);
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void moveUpRight();
    void moveUpLeft();
    void moveDownRight();
    void moveDownLeft();
    void setX(int new_x);
    void setY(int new_y);
    void set_fwidth(int width);
    void set_fheight(int height);
    int getX();
    int getY();
    int getTop();
    int getBottom();
    int getLeft();
    int getRight();
    void set_direction(Move_Type dir);

private:
    bool isFood;
    enum Move_State currentState;
    enum Move_Type direction;
    int x_att;
    int y_att;
    int max_height;
    int max_width;
    int fish_height;
    int fish_width;
    int hunger;
};

#endif // BRAIN_H
