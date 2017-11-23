#ifndef PACMANANIMATION_H
#define PACMANANIMATION_H

#include <SFML/Graphics.hpp>
#include "animatedsprite.h"
#include <iostream>
#include "spriteclass.h"



class PacManAnimation
{
public:
    PacManAnimation();

    void setPacManDirection(int direction);//sets the direction of the animation


    sf::Texture texture;//the texture sheet of animations


    Animation walkingAnimation[4];//the array of animations-> left, right, up, down

    Animation* currentAnimation;//current animations
};

#endif // PACMANANIMATION_H
