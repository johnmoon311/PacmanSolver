#ifndef PACMAN_H
#define PACMAN_H
#include "spriteclass.h"

enum PacManMood{GetPebble, AvoidGhost, ChaseGhost, GetSuperPebble};

class PacMan: public SpriteClass
{
public:
    PacMan(char face);



};

#endif // PACMAN_H
