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
}

//Constructor to create a new fish based on parameters
brain::brain(int x, int y, int width, int height, int fwidth, int fheight){
    x_att = x;
    y_att = y;
    max_width = width;
    max_height = height;
    fish_height = fheight;
    fish_width = fwidth;
}

//Constructor to create a new fish that is exactly like the old fish
brain::brain(brain *other){
    x_att = other->x_att;
    y_att = other->y_att;
    max_width = other->max_width;
    max_height = other->max_height;
    fish_height = other->fish_height;
    fish_width = other->fish_width;
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
    if (new_x < 0) x_att = 0;
    else if (new_x > max_width) x_att = max_width;
    else x_att = new_x;
}

//Function to change the y attribute of the fish
void brain::setY(int new_y){
    if (new_y < 0) y_att = 0;
    else if (new_y > max_height) y_att = max_height;
    else y_att = new_y;
}

//Function to move the fish straight left
void brain::moveLeft(){
    setX(x_att - 1);
}

//Functino to move the fish straight right
void brain::moveRight(){
    setX(x_att + 1);
}

//Function to move the fish straight up
void brain::moveUp(){
    setY(y_att - 1);
}

//Function to move the fish sraight down
void brain::moveDown(){
    setY(y_att + 1);
}

//Function to move the fish diagonally up and right
void brain::moveUpRight(){
    setX(x_att + 1);
    setY(y_att - 1);
}

//Function to move the fish diagonally up and left
void brain::moveUpLeft(){
    setX(x_att - 1);
    setY(y_att - 1);
}

//Function to move the fish diagonally down and right
void brain::moveDownRight(){
    setX(x_att + 1);
    setY(y_att + 1);
}

//Function to move the fush diagonally down and left
void brain::moveDownLeft(){
    setX(x_att - 1);
    setY(y_att + 1);
}

//Function to choose the next state of the fish
Move_State brain::moveState(int input){
    typedef enum {S_Move, S_Idle, S_Feed} SMove;
    static SMove s = S_Idle;
    //Create state transitions
         if((s == S_Idle) && (isFood)) {s = S_Feed;}
    else if((s == S_Move) && (isFood)) {s = S_Feed;}
    else if((s == S_Idle) && (input == 0) && (!isFood)) {s = S_Idle;}
    else if((s == S_Idle) && (input == 1) && (!isFood)) {s = S_Move;}
    else if((s == S_Move) && (input == 0) && (!isFood)) {s = S_Idle;}
    else if((s == S_Move) && (input == 1) && (!isFood)) {s = S_Move;}
    else if((s == S_Feed) && (!isFood)) {s = S_Idle;}
    else{s = s;}
    //Create output table
    switch(s){
        case(S_Idle): return Idle;
        case(S_Move): return Move;
        case(S_Feed): return Feed;
    }
    return Idle; //If state machine fails, fish goes to Idle state
}

//State machine to choose the next movement direction of the fish
Move_Type brain::moveTypeState(int input){
    typedef enum {S_Up, S_Down, S_Left, S_Right, S_Forward, S_Back,
                  S_UpBack, S_UpForward, S_UpRight, S_UpLeft, S_UpBackRight, S_UpBackLeft, S_UpForwardRight,
                  S_UpForwardLeft, S_DownBack, S_DownForward, S_DownRight, S_DownLeft, S_DownBackRight,
                  S_DownBackLeft, S_DownForwardRight, S_DownForwardLeft, S_ForwardRight, S_ForwardLeft,
                  S_BackRight, S_BackLeft} S_Move_Type;
    static S_Move_Type s = S_Up;

    //Create state transitions
         if(input == 0) {s = S_Up;}
    else if(input == 1) {s = S_Down;}
    else if(input == 2) {s = S_Right;}
    else if(input == 3) {s = S_Left;}
    else if(input == 4) {s = S_Back;}
    else if(input == 5) {s = S_Forward;}
    else if(input == 6) {s = S_UpBack;}
    else if(input == 7) {s = S_UpForward;}
    else if(input == 8) {s = S_UpRight;}
    else if(input == 9) {s = S_UpLeft;}
    else if(input == 10) {s = S_UpBackRight;}
    else if(input == 11) {s = S_UpBackLeft;}
    else if(input == 12) {s = S_UpForwardRight;}
    else if(input == 13) {s = S_UpForwardLeft;}
    else if(input == 14) {s = S_DownBack;}
    else if(input == 15) {s = S_DownForward;}
    else if(input == 16) {s = S_DownRight;}
    else if(input == 17) {s = S_DownLeft;}
    else if(input == 18) {s = S_DownBackRight;}
    else if(input == 19) {s = S_DownBackLeft;}
    else if(input == 20) {s = S_DownForwardRight;}
    else if(input == 21) {s = S_DownForwardLeft;}
    else if(input == 22) {s = S_ForwardRight;}
    else if(input == 23) {s = S_ForwardLeft;}
    else if(input == 24) {s = S_BackRight;}
    else if(input == 25) {s = S_BackLeft;}
    else {s = s;}
    //Create output table
    switch(s){
        case(S_Up): return Up;
        case(S_Down): return Down;
        case(S_Left): return Left;
        case(S_Right): return Right;
        case(S_Forward): return Forward;
        case(S_Back): return Back;
        case(S_UpBack): return UpBack;
        case(S_UpForward): return UpForward;
        case(S_UpRight): return UpRight;
        case(S_UpLeft): return UpLeft;
        case(S_UpBackRight): return UpBackRight;
        case(S_UpBackLeft): return UpBackLeft;
        case(S_UpForwardRight): return UpForwardRight;
        case(S_UpForwardLeft): return UpForwardLeft;
        case(S_DownBack): return DownBack;
        case(S_DownForward): return DownForward;
        case(S_DownRight): return DownRight;
        case(S_DownLeft): return DownLeft;
        case(S_DownBackRight): return DownBackRight;
        case(S_DownBackLeft): return DownBackLeft;
        case(S_DownForwardRight): return DownForwardRight;
        case(S_DownForwardLeft): return DownForwardLeft;
        case(S_ForwardRight): return ForwardRight;
        case(S_ForwardLeft): return ForwardLeft;
        case(S_BackRight): return BackRight;
        case(S_BackLeft): return BackLeft;
    }
    return Up; //If state machine fails, fish swims upwards
}

//Function to implement the state of being of the fish and to choose
// the fish's next state of being
void brain::decision(){
    int driver;
    srand(time(NULL));
    driver = rand() % 2;
    currentState = moveState(driver);
    switch(currentState){
        case(Idle):
            break;
        case(Move):
            driver = rand() % 30;
            direction = moveTypeState(driver);
            switch(direction){
                case(Up):
                    moveUp();
                    break;
                case(Down):
                    moveDown();
                    break;
                case(Left):
                    moveLeft();
                    break;
                case(Right):
                    moveRight();
                    break;
                case(UpLeft):
                    moveUpLeft();
                    break;
                case(UpRight):
                    moveUpRight();
                    break;
                case(DownLeft):
                    moveDownLeft();
                    break;
                case(DownRight):
                    moveDownRight();
                    break;
                default:
                    currentState = Idle;
            }
            break;
        case(Feed):
            isFood = false;
            break;
        default:
            currentState = Idle;
    }
}

//Function to return where the top of the fish is currently
int brain::getTop(){
    return y_att;
}

//Function to find where the bottom of the fish is currently
int brain::getBottom(){
    return (y_att + fish_height);
}

//Function to find where the laftmost point of the fish is currently
int brain::getLeft(){
    return x_att;
}

//Function to find where the rightmost point of the fish is currently
int brain::getRight(){
    return (x_att + fish_width);
}
