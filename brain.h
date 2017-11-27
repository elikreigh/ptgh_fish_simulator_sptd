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
    Move_State moveState(int input);
    Move_Type moveTypeState(int input);
    void decision();


private:
    bool isFood;
    enum Move_State currentState;
    enum Move_Type direction;
};

#endif // BRAIN_H
