#ifndef BRAIN_H
#define BRAIN_H


class brain
{
public:
    brain();
    moveState(int input);
    moveTypeState(int input);
    typedef enum {Move, Idle, Feed} Move_State;
    typedef enum {Up, Down, Left, Right, Forward, Back,
                  UpBack, UpForward, UpRight, UpLeft, UpBackRight, UpBackLeft, UpForwardRight,
                  UpForwardLeft, DownBack, DownForward, DownRight, DownLeft, DownBackRight,
                  DownBackLeft, DownForwardRight, DownForwardLeft, ForwardRight, ForwardLeft,
                  BackRight, BackLeft} Move_Type;
private:
    bool isFood;
};

#endif // BRAIN_H
