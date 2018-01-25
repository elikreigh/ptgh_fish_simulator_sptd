/*
 * Author: Matt Westjohn
 * Version 1.1 11/27/17
 * Version 1.2 11/29/17
 * Version 1.3 12/1/17
 * Purpose: Implement the fish's movement ability, decision making ability,
 *  and what each of those decisons does for the fish
 * Collision detection in another file (probably mainwindow)
 * */
#include "brain.h"
#include <stdlib.h>
#include <time.h>

//Default constructor
brain::brain(){
    x_att = 50;
    y_att = 10;
    max_width = 1000;
    max_height = 1000;
    fish_width = 100;
    fish_height = 50;
    hunger = 0;
    currentState = Idle;
    direction = Up;
}

//Constructor to create a new fish based on parameters
brain::brain(int width, int height){
    max_width = width-131;
    max_height = height;
    hunger = 0;
    currentState = Idle;
    direction = Up;
}

//Constructor to create a new fish that is exactly like the old fish
brain::brain(brain *other){
    x_att = other->x_att;
    y_att = other->y_att;
    max_width = other->max_width;
    max_height = other->max_height;
    fish_height = other->fish_height;
    fish_width = other->fish_width;
    currentState = other->getState();
    direction = other->getDirection();
}

void brain::set_fwidth(int width){
    fish_width = width;
}

void brain::set_fheight(int height){
    fish_height = height;
}

//Function to return the current x attribute of the fish
int brain::getX(){
    return x_att;
}

//Function to return the current y attribute of the fish
int brain::getY(){
    return y_att;
}

//Function to change the x attribute of the fish
void brain::setX(int new_x){
    if (new_x < 10) x_att = 10;
    else if (new_x > max_width-fish_width-10) x_att = max_width-fish_width-10;
    else x_att = new_x;
}

//Function to change the y attribute of the fish
void brain::setY(int new_y){
    if (new_y < 10) y_att = 10;
    else if (new_y > max_height-fish_height-100) y_att = max_height-fish_height-100;
    else y_att = new_y;
}

void brain::move(Move_Type dir){
    switch(dir){
        case(Up):
            setY(y_att - 1);
            setX(x_att);
            break;
        case(Down):
            setY(y_att + 1);
            setX(x_att);
            break;
        case(Left):
            setX(x_att - 1);
            setY(y_att);
            break;
        case(Right):
            setX(x_att + 1);
            setY(y_att);
            break;
        case(UpLeft):
            setX(x_att - 1);
            setY(y_att - 1);
            break;
        case(UpRight):
            setX(x_att + 1);
            setY(y_att - 1);
            break;
        case(DownLeft):
            setX(x_att - 1);
            setY(y_att + 1);
            break;
        case(DownRight):
            setX(x_att + 1);
            setY(y_att + 1);
            break;
    }
}

//Function to choose the next state of the fish
void brain::moveState(int input){
    typedef enum {S_Move, S_Idle} SMove;
    static SMove s = S_Idle;
    //Create state transitions
         if((input == 0)) {s = S_Idle;}
    else if((input <= 7 && input > 0)) {s = S_Move;}
    else{s = S_Move;}
    //Create output table
    switch(s){
        case(S_Idle): set_state(Idle);
        case(S_Move): set_state(Move);
    }
    set_state(Move); //If state machine fails, fish goes to Move state
}

//State machine to choose the next movement direction of the fish
void brain::moveTypeState(int input){
    typedef enum {S_Up, S_Down, S_Left, S_Right, S_UpRight, S_UpLeft, S_DownRight, S_DownLeft} S_Move_Type;
    static S_Move_Type s = S_Up;

    //Create state transitions
         if(input == 0) {s = S_Up;}
    else if(input == 1) {s = S_Down;}
    else if(input == 2) {s = S_Right;}
    else if(input == 3) {s = S_Left;}
    else if(input == 8) {s = S_UpRight;}
    else if(input == 9) {s = S_UpLeft;}
    else if(input == 16) {s = S_DownRight;}
    else if(input == 17) {s = S_DownLeft;}
    else {s = S_Up;}
    //Create output table
    switch(s){
        case(S_Up): set_direction(Up);
        case(S_Down): set_direction(Down);
        case(S_Left): set_direction(Left);
        case(S_Right): set_direction(Right);
        case(S_UpRight): set_direction(UpRight);
        case(S_UpLeft): set_direction(UpLeft);
        case(S_DownRight): set_direction(DownRight);
        case(S_DownLeft): set_direction(DownLeft);
    }
    set_direction(Up); //If state machine fails, fish swims upwards
}

//Function to implement the state of being of the fish and to choose
// the fish's next state of being
void brain::decisionState(){
    int driver;
    srand(time(NULL));
    driver = rand() % 8;
    //moveState(driver);
    switch(driver){
        case(0):
            currentState = Idle;
            break;
        case(1):
        case(2):
        case(3):
        case(4):
        case(5):
        case(6):
        case(7):
            currentState = Move;
            break;
        default:
            currentState = Move;
    }
}

Move_Type brain::decisionDirection(){
    int driver;
    srand(time(NULL));
    driver = rand() % 10;
    //moveTypeState(driver);
    switch(driver){
        case(0):
            direction = Up;
            break;
        case(1):
            direction = Down;
            break;
        case(2):
            direction = Right;
            break;
        case(3):
            direction = Left;
            break;
        case(4):
            direction = UpLeft;
            break;
        case(5):
            direction = UpRight;
            break;
        case(6):
            direction = DownLeft;
            break;
        case(7):
            direction = DownRight;
            break;
        case(8):
        case(9):
            direction = direction;
            break;
        default:
            direction = Up;
    }
    return direction;
}

//Function to return where the top of the fish is currently
int brain::getTop(){
    return y_att;
}

//Function to find where the bottom of the fish is currently
int brain::getBottom(){
    return (y_att + fish_height);
}

//Function to find where the leftmost point of the fish is currently
int brain::getLeft(){
    return x_att;
}

//Function to find where the rightmost point of the fish is currently
int brain::getRight(){
    return (x_att + fish_width);
}

Move_State brain::getState(){
    return currentState;
}

Move_Type brain::getDirection(){
    return direction;
}

void brain::set_state(Move_State state){
    currentState = state;
}

void brain::set_direction(Move_Type direction){
    this->direction = direction;
}
