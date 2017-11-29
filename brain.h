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
    brain(int x, int y, int width, int height);
    Move_State moveState(int input);
    Move_Type moveTypeState(int input);
    void decision();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void moveUpRight();
    void moveUpLeft();
    void moveDownRight();
    void moveDownLeft();
    int getX();
    int getY();
    void setX(int new_x);
    void setY(int new_y);

private:
    bool isFood;
    enum Move_State currentState;
    enum Move_Type direction;
    int x_att;
    int y_att;
    int max_height;
    int max_width;
};

#endif // BRAIN_H
