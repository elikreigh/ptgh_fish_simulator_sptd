#ifndef BRAIN_H
#define BRAIN_H


class brain
{
public:
    brain();
    Move_State moveState(int input);
    Move_Type moveTypeState(int input);
    void decision();
    typedef enum {Move, Idle, Feed} Move_State;
    typedef enum {Up, Down, Left, Right, Forward, Back,
                  UpBack, UpForward, UpRight, UpLeft, UpBackRight, UpBackLeft, UpForwardRight,
                  UpForwardLeft, DownBack, DownForward, DownRight, DownLeft, DownBackRight,
                  DownBackLeft, DownForwardRight, DownForwardLeft, ForwardRight, ForwardLeft,
                  BackRight, BackLeft} Move_Type;
private:
    bool isFood;
    moveState currentState;
    moveTypeState direction;
};

#endif // BRAIN_H
