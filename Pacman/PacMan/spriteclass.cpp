#include "spriteclass.h"

SpriteClass::SpriteClass(char face):spriteface(face)
{
    hasMoved=false;
    hasResetSprite=false;
    isDead=false;
    spriteMood=0;
    spriteMoveDirection=Left;
    moveCount=0;
}


