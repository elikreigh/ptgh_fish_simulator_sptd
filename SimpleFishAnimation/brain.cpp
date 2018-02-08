/*
 * Author: Matt Westjohn
 * Version 1.1 11/27/17
 * Version 1.2 11/29/17
 * Version 1.3 12/1/17
 * Purpose: Implement the fish's movement ability, decision making ability,
 *  and what each of those decisons does for the fish
 * Collision detection in another file (probably mainwindow)
 *
 * Author: Adam Griswold
 * Version 1.4 1/16/18
 * Purpose: Implement more states for the fish and to change timing for movement
 * decisions
 * Fish selects final destination and pathfinds to that destination
 * rather than moving one "tile" at a time before another decision occurs
 */
#include "brain.h"
#include <stdlib.h>
#include <time.h>

//Default constructor
brain::brain(){
    destination.setX(0);
    destination.setY(0);
    destdepth = 0;
    place.setX(50);
    place.setY(10);
    max_width = 1151;
    max_height = 621;
    fish_width = 100;
    fish_height = 50;
    hunger = 0;
    bob_counter = 0;
    fish_speed = 1;
    current_state = Idle;
    direction = Up;
    depth = 5;
    prevdepth = depth;
}

//Constructor to create a new fish based on parameters
brain::brain(int width, int height){
    destination.setX(0);
    destination.setY(0);
    destdepth = 0;
    place.setX(50);
    place.setY(10);
    max_width = width-131;
    max_height = height;
    hunger = .25;
    bob_counter = 0;
    fish_speed = 1;
    current_state = Idle;
    direction = Up;
    depth = 5;
    prevdepth = depth;
}

//Constructor to create a new fish that is exactly like the old fish
brain::brain(brain *other){
    place.setX(other->place.x());
    place.setY(other->place.y());
    this->setDestination(other->get_destination(), other->getDepth());
    max_width = other->max_width;
    max_height = other->max_height;
    fish_height = other->fish_height;
    fish_width = other->fish_width;
    bob_counter = other->bob_counter;
    fish_speed = other->fish_speed;
    current_state = other->getState();
    direction = other->getDirection();
    depth = other->getDepth();
    prevdepth = other->getPrevDepth();
}

void brain::set_fwidth(int width){
    fish_width = width;
}

void brain::set_fheight(int height){
    fish_height = height;
}

//Function to return the current x attribute of the fish
int brain::getX(){
    return place.x()+fish_width/2;
}

//Function to return the current y attribute of the fish
int brain::getY(){
    return place.y()+fish_height/2;
}

float brain::getDepth(){
    return depth;
}

float brain::getPrevDepth(){
    return prevdepth;
}

float brain::getDestDepth(){
    return destdepth;
}

float brain::getHunger(){
    return hunger;
}

//Function to change the x attribute of the fish
void brain::setX(int new_x){
    if (new_x < 10+fish_width) place.setX(10+fish_width);
    else if (new_x > max_width-fish_width-10){
        place.setX(max_width-fish_width-10);
    }
    else place.setX(new_x);
}

//Function to change the y attribute of the fish
void brain::setY(int new_y){
    if (new_y < 10+fish_height) place.setY(10+fish_height);
    else if (new_y > max_height-fish_height-100){
        place.setY(max_height-fish_height-100);
    }
    else place.setY(new_y);
}

void brain::setDepth(float dpth){
    if (this->getDepth() <= 9 && this->getDepth() >= 0){
        prevdepth = depth;
        depth = dpth;
    }
    else {
        depth-=.2;
        prevdepth = depth;
    }
}

void brain::resetPrevDepth(){
    prevdepth = depth;
}

void brain::setDestination(){
    destination.setX(rand()%(max_width-fish_width*2));
    destination.setY(rand()%(max_height-fish_height*2));
    destdepth = (rand()%10);
}

void brain::setDestination(QPoint dest, float destdepth){
    destination.setX(dest.x()%(max_width-fish_width*2));
    destination.setY(dest.y()%(max_height-fish_height*2));
    this->destdepth = destdepth;
}

void brain::setDestination(Interferences* pile[4]){
    destination.setX(pile[2]->get_left());
    destination.setY(pile[2]->get_top()-10);
    destdepth = pile[2]->get_depth();
}

void brain::setDestination(int new_x, int new_y){
    if (new_x < 10) destination.setX(10);
    else if (new_x > max_width-10){
        destination.setX(max_width-10);
    }
    else destination.setX(new_x);

    if (new_y < 10) destination.setY(10);
    else if (new_y > max_height-175){
        destination.setY(max_height-175);
    }
    else destination.setY(new_y);

    destdepth= rand()%10;
}

//Used in click events
//Placement of click will determine opposite position around fishes current location
//Distance away will be determined by closeness of click to current position
void brain::runFromMouseClick(QPoint dest){
    int distanceX = (abs(dest.x()-getX()));
    int distanceY = (abs(dest.y()-getY()));

    int runDistX = rand()%390+50;
    int runDistY = rand()%390+50;

    //Destination will follow this pattern with values corresponding
    //to distance away from mouse 180 deg around fish location
    if(dest.x() <= getX()+fish_width/2) {
        if(dest.y() <= getY()+fish_height/2) {
            setDestination(getX()+runDistX, getY()+runDistY);
        }
        else {
            setDestination(getX()+runDistX, getY()-runDistY);
        }
    }
    else {
        if(dest.y() <= getY()+fish_height/2) {
            setDestination(getX()-runDistX, getY()+runDistY);
        }
        else {
            setDestination(getX()-runDistX, getY()-runDistY);
        }

    }

    //Runs back to depths 5 to 9
    destdepth = rand()%6 + 4;
}

void brain::increase_hunger(){
    if ((hunger+.0001) <= .9999) hunger += .0001;
    else hunger = 1;
}

void brain::reduce_hunger(){
    if ((hunger-.25) > 0) hunger -= .25;
    else hunger = 0;
}

//State machine to choose the next movement direction of the fish
void brain::moveTypeState(int input){
    typedef enum {S_Up, S_Down, S_Left, S_Right, S_UpRight, S_UpLeft, S_DownRight, S_DownLeft,
                  S_AUp, S_ADown, S_ALeft, S_ARight, S_AUpRight, S_AUpLeft, S_ADownRight, S_ADownLeft,
                  S_TUp, S_TDown, S_TLeft, S_TRight, S_TUpRight, S_TUpLeft, S_TDownRight, S_TDownLeft} S_Move_Type;
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
    else if(input == 0) {s = S_AUp;}
    else if(input == 1) {s = S_ADown;}
    else if(input == 2) {s = S_ARight;}
    else if(input == 3) {s = S_ALeft;}
    else if(input == 8) {s = S_AUpRight;}
    else if(input == 9) {s = S_AUpLeft;}
    else if(input == 16) {s = S_ADownRight;}
    else if(input == 17) {s = S_ADownLeft;}
     else if(input == 0) {s = S_TUp;}
     else if(input == 1) {s = S_TDown;}
     else if(input == 2) {s = S_TRight;}
     else if(input == 3) {s = S_TLeft;}
     else if(input == 8) {s = S_TUpRight;}
     else if(input == 9) {s = S_TUpLeft;}
     else if(input == 16) {s = S_TDownRight;}
     else if(input == 17) {s = S_TDownLeft;}
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
        case(S_AUp): set_direction(AUp);
        case(S_ADown): set_direction(ADown);
        case(S_ALeft): set_direction(ALeft);
        case(S_ARight): set_direction(ARight);
        case(S_AUpRight): set_direction(AUpRight);
        case(S_AUpLeft): set_direction(AUpLeft);
        case(S_ADownRight): set_direction(ADownRight);
        case(S_ADownLeft): set_direction(ADownLeft);
        case(S_TUp): set_direction(TUp);
        case(S_TDown): set_direction(TDown);
        case(S_TLeft): set_direction(TLeft);
        case(S_TRight): set_direction(TRight);
        case(S_TUpRight): set_direction(TUpRight);
        case(S_TUpLeft): set_direction(TUpLeft);
        case(S_TDownRight): set_direction(TDownRight);
        case(S_TDownLeft): set_direction(TDownLeft);
    }
    this->set_direction(Up); //If state machine fails, fish swims upwards
}

//fish bob idle_animation
void brain::idle_ani(){
    /*if(bob_counter <= 4 || (bob_counter > 14 && bob_counter <=19)){
        this->move(Up);
    }
    else if(bob_counter > 4 && bob_counter <= 14){
        this->move(Down);
    }
    else{
        bob_counter = 0;
        this->move(Up);
    }
    bob_counter++;*/
}

void brain::move(Move_Type dir){
    switch(dir){
        case(Up):
            place.setY(place.y() - fish_speed);
            place.setX(place.x());
            break;
        case(Down):
            place.setY(place.y() + fish_speed);
            place.setX(place.x());
            break;
        case(Left):
            place.setX(place.x() - fish_speed);
            place.setY(place.y());
            break;
        case(Right):
            place.setX(place.x() + fish_speed);
            place.setY(place.y());
            break;
        case(UpLeft):
            place.setX(place.x() - fish_speed);
            place.setY(place.y() - fish_speed);
            break;
        case(UpRight):
            place.setX(place.x() + fish_speed);
            place.setY(place.y() - fish_speed);
            break;
        case(DownLeft):
            place.setX(place.x() - fish_speed);
            place.setY(place.y() + fish_speed);
            break;
        case(DownRight):
            place.setX(place.x() + fish_speed);
            place.setY(place.y() + fish_speed);
            break;
        case(AUp):
            place.setY(place.y() - fish_speed);
            place.setX(place.x());
            this->setDepth(this->getDepth()+.2);
            break;
        case(ADown):
            place.setY(place.y() + fish_speed);
            place.setX(place.x());
            this->setDepth(this->getDepth()+.2);
            break;
        case(ALeft):
            place.setX(place.x() - fish_speed);
            place.setY(place.y());
            this->setDepth(this->getDepth()+.2);
            break;
        case(ARight):
            place.setX(place.x() + fish_speed);
            place.setY(place.y());
            this->setDepth(this->getDepth()+.2);
            break;
        case(AUpLeft):
            place.setX(place.x() - fish_speed);
            place.setY(place.y() - fish_speed);
            this->setDepth(this->getDepth()+.2);
            break;
        case(AUpRight):
            place.setX(place.x() + fish_speed);
            place.setY(place.y() - fish_speed);
            this->setDepth(this->getDepth()+.2);
            break;
        case(ADownLeft):
            place.setX(place.x() - fish_speed);
            place.setY(place.y() + fish_speed);
            this->setDepth(this->getDepth()+.2);
            break;
        case(ADownRight):
            place.setX(place.x() + fish_speed);
            place.setY(place.y() + fish_speed);
            this->setDepth(this->getDepth()+.2);
            break;
        case(TUp):
            place.setY(place.y() - fish_speed);
            place.setX(place.x());
            this->setDepth(this->getDepth()-.2);
            break;
        case(TDown):
            place.setY(place.y() + fish_speed);
            place.setX(place.x());
            this->setDepth(this->getDepth()-.2);
            break;
        case(TLeft):
            place.setX(place.x() - fish_speed);
            place.setY(place.y());
            this->setDepth(this->getDepth()-.2);
            break;
        case(TRight):
            place.setX(place.x() + fish_speed);
            place.setY(place.y());
            this->setDepth(this->getDepth()-.2);
            break;
        case(TUpLeft):
            place.setX(place.x() - fish_speed);
            place.setY(place.y() - fish_speed);
            this->setDepth(this->getDepth()-.2);
            break;
        case(TUpRight):
            place.setX(place.x() + fish_speed);
            place.setY(place.y() - fish_speed);
            this->setDepth(this->getDepth()-.2);
            break;
        case(TDownLeft):
            place.setX(place.x() - fish_speed);
            place.setY(place.y() + fish_speed);
            this->setDepth(this->getDepth()-.2);
            break;
        case(TDownRight):
            place.setX(place.x() + fish_speed);
            place.setY(place.y() + fish_speed);
            this->setDepth(this->getDepth()-.2);
            break;
    }
    this->direction = dir;
    this->increase_hunger();
}

void brain::move(Interferences* pile[4]){
    brain *test = new brain(this);

        test->move(this->getDirection());
        if(test->no_over_lap(pile)){
            switch(this->getDirection()){
                case(Up):
                    place.setY(place.y() - fish_speed);
                    place.setX(place.x());
                    break;
                case(Down):
                    place.setY(place.y() + fish_speed);
                    place.setX(place.x());
                    break;
                case(Left):
                    place.setX(place.x() - fish_speed);
                    place.setY(place.y());
                    break;
                case(Right):
                    place.setX(place.x() + fish_speed);
                    place.setY(place.y());
                    break;
                case(UpLeft):
                    place.setX(place.x() - fish_speed);
                    place.setY(place.y() - fish_speed);
                    break;
                case(UpRight):
                    place.setX(place.x() + fish_speed);
                    place.setY(place.y() - fish_speed);
                    break;
                case(DownLeft):
                    place.setX(place.x() - fish_speed);
                    place.setY(place.y() + fish_speed);
                    break;
                case(DownRight):
                    place.setX(place.x() + fish_speed);
                    place.setY(place.y() + fish_speed);
                    break;
                case(AUp):
                    place.setY(place.y() - fish_speed);
                    place.setX(place.x());
                    this->setDepth(this->getDepth()+.2);
                    break;
                case(ADown):
                    place.setY(place.y() + fish_speed);
                    place.setX(place.x());
                    this->setDepth(this->getDepth()+.2);
                    break;
                case(ALeft):
                    place.setX(place.x() - fish_speed);
                    place.setY(place.y());
                    this->setDepth(this->getDepth()+.2);
                    break;
                case(ARight):
                    place.setX(place.x() + fish_speed);
                    place.setY(place.y());
                    this->setDepth(this->getDepth()+.2);
                    break;
                case(AUpLeft):
                    place.setX(place.x() - fish_speed);
                    place.setY(place.y() - fish_speed);
                    this->setDepth(this->getDepth()+.2);
                    break;
                case(AUpRight):
                    place.setX(place.x() + fish_speed);
                    place.setY(place.y() - fish_speed);
                    this->setDepth(this->getDepth()+.2);
                    break;
                case(ADownLeft):
                    place.setX(place.x() - fish_speed);
                    place.setY(place.y() + fish_speed);
                    this->setDepth(this->getDepth()+.2);
                    break;
                case(ADownRight):
                    place.setX(place.x() + fish_speed);
                    place.setY(place.y() + fish_speed);
                    this->setDepth(this->getDepth()+.2);
                    break;
                case(TUp):
                    place.setY(place.y() - fish_speed);
                    place.setX(place.x());
                    this->setDepth(this->getDepth()-.2);
                    break;
                case(TDown):
                    place.setY(place.y() + fish_speed);
                    place.setX(place.x());
                    this->setDepth(this->getDepth()-.2);
                    break;
                case(TLeft):
                    place.setX(place.x() - fish_speed);
                    place.setY(place.y());
                    this->setDepth(this->getDepth()-.2);
                    break;
                case(TRight):
                    place.setX(place.x() + fish_speed);
                    place.setY(place.y());
                    this->setDepth(this->getDepth()-.2);
                    break;
                case(TUpLeft):
                    place.setX(place.x() - fish_speed);
                    place.setY(place.y() - fish_speed);
                    this->setDepth(this->getDepth()-.2);
                    break;
                case(TUpRight):
                    place.setX(place.x() + fish_speed);
                    place.setY(place.y() - fish_speed);
                    this->setDepth(this->getDepth()-.2);
                    break;
                case(TDownLeft):
                    place.setX(place.x() - fish_speed);
                    place.setY(place.y() + fish_speed);
                    this->setDepth(this->getDepth()-.2);
                    break;
                case(TDownRight):
                    place.setX(place.x() + fish_speed);
                    place.setY(place.y() + fish_speed);
                    this->setDepth(this->getDepth()-.2);
                    break;
            }
        }
        else {
            this->setDepth(this->getDepth()+.2);
        }
        this->increase_hunger();
}

//Function to choose the next state of the fish
void brain::changeState(int input, Interferences *pile[4]){
    typedef enum {S_Move, S_Idle, S_DecideMove, S_Feeding, S_Scared, S_Caught} SMove;
    static SMove s = S_Idle;
    //Create state transitions
         if(hunger > .50 &&
                 pile[2]->get_label()->isVisible())  {s = S_Feeding;}
    else if((input <= 3) && (current_state == Idle)) {s = S_Idle;}
    else if((input > 3) && (current_state == Idle))  {s = S_DecideMove;}
    else if(current_state == DecideMove)             {s = S_Move;}
    else if(((place.x() == destination.x()) && (place.y() == destination.y()))
                 && (current_state == Move))         {s = S_Idle;}
    else if(((place.x() != destination.x()) || (place.y() != destination.y()))
                 && (current_state == Move))         {s = S_Move;}
    else if(current_state == FightOrFlight)          {s = S_Scared;}
    else if((((place.x() <= destination.x()+25) && (place.x() >= destination.x()-25)) &&
                ((place.y() <= destination.y()+25) && (place.y() >= destination.y()-25))) &&
                (current_state == Scared)+25)        {s = S_DecideMove;}
    else if(((place.x() != destination.x()) && (place.y() != destination.y()))
                      && (current_state == Scared))   {s = S_Scared;}
    else if((((place.x() <= destination.x()+25) && (place.x() >= destination.x()-25)) &&
                ((place.y() <= destination.y()+25) && (place.y() >= destination.y()-25))) &&
                (current_state == Feeding))          {s = S_DecideMove;}
    else if(!(((place.x() <= destination.x()+25) && (place.x() >= destination.x()-25)) &&
                ((place.y() <= destination.y()+25) && (place.y() >= destination.y()-25))) &&
                (current_state == Feeding))          {s = S_Feeding;}
    else if(current_state == Caught)                 {s = S_Caught;}
    else {s = S_Idle;}//If state machine fails, fish goes to Idle state

    //Create output table
    switch(s){
        case(S_Idle): this->set_state(Idle);
                      break;
        case(S_Move): this->set_state(Move);
                      break;
        case(S_DecideMove): this->set_state(DecideMove);
                      break;
        case(S_Feeding): this->set_state(Feeding);
                      break;
        case(S_Scared): this->set_state(Scared);
                      break;
        case(S_Caught): this->set_state(Caught);
                      break;
    }
}

//Function to implement the state of being of the fish and to choose
// the fish's next state of being
void brain::decisionState(Interferences* pile[4]){
    //can be moved to game logic class and passed as a paramater through decisionState call
    int driver;
    srand(time(NULL));
    //driver = rand()%5;
    driver = rand()%5;

    switch (current_state) {
        case (Idle):
            fish_speed = 1;
            if(bob_counter <= 4 || (bob_counter > 14 && bob_counter <=19)){
                this->move(Up);
            }
            else if(bob_counter > 4 && bob_counter <= 14){
                this->move(Down);
            }
            else{
                bob_counter = 0;
                this->move(Up);
            }
            bob_counter++;
            qDebug() << "hunger" << hunger;
            //qDebug() << "After Idle" << this->getX() << " " << this->getY() << "\nFish Dest: " << this->get_destination().x() << " " << this->get_destination().y();
                    break;
        case (DecideMove):
            fish_speed = 1;
            this->setDestination();
                    break;
        case (Move):
            this->decisionDirection();
            this->move(pile);
            //qDebug() << "After Move\nFish Pos: " << this->getX() << " " << this->getY() << "\nFish Dest: " << this->get_destination().x() << " " << this->get_destination().y();
            //start moving towards destination
            qDebug() << "hunger " << hunger;
                    break;
        case (FightOrFlight):
            //FightOrFlight is for another rendition of the game where the fish
            //would decide weather to break through the glass and attach the person tapping or
            //to run away
            //not actually, but there was more functionality than changing the speed of the fish
            fish_speed = 3;
                    break;
        case (Scared):
            //Scared is for another rendition of the game where scared would
            //reactively run behind an object in the pile.
            //since the logic was set up this way, rework would lead to the
            //same functionality for a missed amount of time
            this->decisionDirection();
            this->move(pile);
            qDebug() << "hunger " << hunger;
                    break;
        case (Feeding):
            fish_speed = 2;
            this->setDestination(pile);
            this->decisionDirection();
            this->move(pile);
            qDebug() << "hunger " << hunger;
                    break;
        case (Caught):
            //A "buddy system" would have been implemented if more time was alloted
            //This would make it so that the fish would not dictate its own moves, but it
            //would move in conjumction when the hook was pulled up.
            fish_speed = 3;
            this->move(Up);
                    break;
    }
    this->changeState(driver, pile);
}

void brain::decisionDirection(){
    if(destination.x() < place.x() && destination.y() < place.y() && (destdepth >= depth-.1 && destdepth <= depth+1)){
        direction = UpLeft;
    }
    else if(destination.x() == place.x() && destination.y() < place.y() && (destdepth >= depth-.1 && destdepth <= depth+1)){
        direction = Up;
    }
    else if(destination.x() > place.x() && destination.y() < place.y() && (destdepth >= depth-.1 && destdepth <= depth+1)){
        direction = UpRight;
    }
    else if(destination.x() > place.x() && destination.y() == place.y() && (destdepth >= depth-.1 && destdepth <= depth+1)){
        direction = Right;
    }
    else if(destination.x() > place.x() && destination.y() > place.y() && (destdepth >= depth-.1 && destdepth <= depth+1)){
        direction = DownRight;
    }
    else if(destination.x() == place.x() && destination.y() > place.y() && (destdepth >= depth-.1 && destdepth <= depth+1)){
        direction = Down;
    }
    else if(destination.x() < place.x() && destination.y() > place.y() && (destdepth >= depth-.1 && destdepth <= depth+1)){
        direction = DownLeft;
    }
    else if(destination.x() < place.x() && destination.y() == place.y() && (destdepth >= depth-.1 && destdepth <= depth+1)){
        direction = Left;
    }
    else if(destination.x() < place.x() && destination.y() < place.y() && destdepth > depth){
        direction = AUpLeft;
    }
    else if(destination.x() == place.x() && destination.y() < place.y() && destdepth > depth){
        direction = AUp;
    }
    else if(destination.x() > place.x() && destination.y() < place.y() && destdepth > depth){
        direction = AUpRight;
    }
    else if(destination.x() > place.x() && destination.y() == place.y() && destdepth > depth){
        direction = ARight;
    }
    else if(destination.x() > place.x() && destination.y() > place.y() && destdepth > depth){
        direction = ADownRight;
    }
    else if(destination.x() == place.x() && destination.y() > place.y() && destdepth > depth){
        direction = ADown;
    }
    else if(destination.x() < place.x() && destination.y() > place.y() && destdepth > depth){
        direction = ADownLeft;
    }
    else if(destination.x() < place.x() && destination.y() == place.y() && destdepth > depth){
        direction = ALeft;
    }
    else if(destination.x() < place.x() && destination.y() < place.y() && destdepth < depth){
        direction = TUpLeft;
    }
    else if(destination.x() == place.x() && destination.y() < place.y() && destdepth < depth){
        direction = TUp;
    }
    else if(destination.x() > place.x() && destination.y() < place.y() && destdepth < depth){
        direction = TUpRight;
    }
    else if(destination.x() > place.x() && destination.y() == place.y() && destdepth < depth){
        direction = TRight;
    }
    else if(destination.x() > place.x() && destination.y() > place.y() && destdepth < depth){
        direction = TDownRight;
    }
    else if(destination.x() == place.x() && destination.y() > place.y() && destdepth < depth){
        direction = TDown;
    }
    else if(destination.x() < place.x() && destination.y() > place.y() && destdepth < depth){
        direction = TDownLeft;
    }
    else if(destination.x() < place.x() && destination.y() == place.y() && destdepth < depth){
        direction = TLeft;
    }
}

Move_Type brain::decisionDirection(int driver){
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
    return place.y();
}

//Function to find where the bottom of the fish is currently
int brain::getBottom(){
    return (place.y() + fish_height);
}

//Function to find where the leftmost point of the fish is currently
int brain::getLeft(){
    return place.x();
}

//Function to find where the rightmost point of the fish is currently
int brain::getRight(){
    return (place.x() + fish_width);
}

Move_State brain::getState(){
    return current_state;
}

Move_Type brain::getDirection(){
    return direction;
}

QPoint brain::get_destination(){
    return destination;
}

void brain::set_state(Move_State state){
    current_state = state;
}

void brain::set_direction(Move_Type direction){
    this->direction = direction;
}

bool brain::no_over_lap(Interferences* pile[4]){
    bool ans = true;
    for(int i = 0; i <= 3; i++){
        if(pile[i]->get_type() == Obstical){
            int pile_right = pile[i]->get_right();
            int pile_left = pile[i]->get_left();
            int pile_top = pile[i]->get_top();
            int pile_depth = pile[i]->get_depth();
            if(((this->getLeft() == pile_right && this->getBottom() >= pile_top) ||
                    (this->getRight() == pile_left && this->getBottom() >= pile_top) ||
                    (this->getBottom() == pile_top && this->getRight() >= pile_left && this->getLeft() <= pile_right))
                    && this->getDepth() == pile_depth){
                ans = false;
            }
        }
    }
    return ans;
}
