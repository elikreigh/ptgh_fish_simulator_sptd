#ifndef BRAIN_H
#define BRAIN_H

enum  Move_State {Move, Idle};
enum Move_Type {Up, Down, Left, Right, UpRight, UpLeft, DownRight, DownLeft};
class brain
{
public:
    brain();
    brain(int width, int height);
    brain(brain *other);
    void moveState(int input);
    void moveTypeState(int input);
    Move_State getState();
    Move_Type getDirection();
    Move_Type decisionDirection();
    void decisionState();
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
    void set_direction(Move_Type direction);
    void set_state(Move_State state);
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
