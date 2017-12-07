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
    brain(int x, int y, int width, int height, int fwidth, int fheight);
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
    int getX();
    int getY();
    int getTop();
    int getBottom();
    int getLeft();
    int getRight();

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
