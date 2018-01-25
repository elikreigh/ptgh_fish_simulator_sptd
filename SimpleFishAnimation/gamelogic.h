#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "bubbles.h"
#include "floatingbubbles.h"
#include "fishfood.h"
#include "pillar.h"

class GameLogic
{
public:
    GameLogic();
    void set_splash_floater();
private:
    //Bubbles for splash screen
    FloatingBubbles *(splash_floater1[]);
    /*FloatingBubbles *splash_floater2;
    FloatingBubbles *splash_floater3;
    FloatingBubbles *splash_floater4;
    FloatingBubbles *splash_floater5;
    FloatingBubbles *splash_floater6;*/

    //Bubbles and food for tank screen
    Bubbles *bubble1;
    Bubbles *bubble2;
    FloatingBubbles *single_bubble1;
    FishFood *food;
    Pillar *pillar1;
    Pillar *pillar2;
};

#endif // GAMELOGIC_H
