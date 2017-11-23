#ifndef GHOST_H
#define GHOST_H
#include "spriteclass.h"

enum intellegence{Follower, Ambush, Dumb, Dumber};

enum GhostMood{ChasePacman, MoveRandom, Runaway};

class Ghost: public SpriteClass
{
public:
    Ghost(char face, int ghostSkill);

    int getGhostIntellegence(){return ghostIntellegence;}//ghosts intellegence level


private:
    int ghostIntellegence;//the ghosts intellegence
};

#endif // GHOST_H
