#ifndef SPRITECLASS_H
#define SPRITECLASS_H
#include <vector>

enum direction{Up, Down, Left, Right};

class GameNode;



class SpriteClass
{
public:
    SpriteClass(char face);

    char getFace(){return spriteface;}//gets the current face of sprite

    bool getHasMoved(){return hasMoved;}//returns if sprite has moved

    void setHasMoved(){(hasMoved==false)?hasMoved=true:hasMoved=false;}//sets if the sprite has moved

    void setIsDead(){(isDead==false)?isDead=true:isDead=false;}//sets if the sprite is dead

    void setResetSprite(){(hasResetSprite==false)?hasResetSprite=true:hasResetSprite=false;}//sets the reset



    virtual int getGhostIntellegence(){}//do nothing




    std::vector<GameNode*> path;//the path to the next node

    int spriteMood;//the mood of the sprite

    int spriteMoveDirection;//0 = UP, 1 = DOWN, 2 = LEFT, 3 = RIGHT

    int moveCount;//the move count of the sprite when pac man eats pebble, or when ghosts change mood

    bool hasResetSprite;//tells if i have already reset the sprite


private:
    char spriteface;
    bool hasMoved;
    bool isDead;

};


#endif // SPRITECLASS_H
