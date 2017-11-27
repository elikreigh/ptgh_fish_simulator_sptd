#include "brain.h"
#include <stdlib.h>
#include <time.h>

brain::brain()
{

}

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
    return Idle;
}

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
    return Up;
}

void brain::decision(){
    int driver;
    srand(time(NULL));
    driver = rand() % 2;
    currentState = moveState(driver);
    switch(currentState){
        case(Idle):
            break;
        case(Move):
            driver = rand() % 26;
            direction = moveTypeState(driver);
            break;
        case(Feed):
            isFood = false;
            break;
    }
}
