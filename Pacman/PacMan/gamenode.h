#ifndef GAMENODE_H
#define GAMENODE_H
#include "spriteclass.h"
#include "pacman.h"
#include "ghost.h"
#include <iostream>

using namespace std;

const int MAX_ROW=23;
const int MAX_COLUM=23;
const int BOX_SIZE=24;
const int SCREEN_LENGTH=800;
const int SCREEN_HEIGHT=600;
const int MAX=60;

enum spriteType{Empty, Pacman, GhostSet};

struct Position{
    int row, colum;

    Position():row(-1), colum(-1){}

    Position(int x, int y):row(y), colum(x){}

    void SetPosition(int x, int y){row=y, colum=x;}
};

enum pebbleType{NoPebble, Pebble, SuperPebble};

class GameNode
{
public:


    GameNode(int spriteSelection, int pebbleSelection, int row, int colum, int ghostSkill);

    ~GameNode();

    void LinkNodes(GameNode* &linkThis);//links the nodes, connects the path for sprites

    void Move(GameNode* gameBoard[][MAX_COLUM], int pebbleCount, int superPebbleCount);//moves the sprite, ghost and pac man

    bool isSpriteEmpty(){return spriteCount==0;}//returns the current count of sprite

    vector<GameNode*> findGhostOnMap(GameNode* gameBoard[][MAX_COLUM]);//finds all the ghosts in the map

    vector<GameNode*> getGhostPositionInCheckedList(GameNode* gameBoard[][MAX_COLUM]);// this will put the ghost in pac mans radar if the ghosts are close enough

    vector<GameNode*> getSearchList(vector<GameNode *> &checkedList);//gets the next search list of the nodes

    GameNode* getNextPath(int spriteIndex);//gets the next path in the pac man

    void generateRandomPath(int spriteIndex, GameNode* gameBoard[][MAX_COLUM]);//generates a path to a random node on the board

    void setMoveDirection(int spriteIndex, GameNode *nextPathNode);//sets the move direction of the sprite

    void MoveToPosition(GameNode *&moveHere, int spriteIndex);//moves to the next node

    void findClosestPathToPosition(vector<GameNode *> &toSearchList, vector<GameNode *> &checkedList, int spriteIndex, GameNode *findThisPosition);//finds closest path to position

    void findClosestPebble(vector<GameNode *> &toSearchList, vector<GameNode *> &checkedList, int spriteIndex, int pebbleType);//finds closest path to a pebble

    void findClosestSuperPebble(vector<GameNode *> &toSearchList, vector<GameNode *> &checkedList, int spriteIndex);//finds the closest super pebble

    void findClosestPathToPacMan(vector<GameNode *> &toSearchList, vector<GameNode *> &checkedList, int spriteIndex);//find path to the closest ghost

    void findClosestGhost(vector<GameNode *> &toSearchList, vector<GameNode *> &checkedList, vector<GameNode *> &ghostPath, GameNode* &findThisGhost);//finds the position of the ghost to look for

    vector<GameNode*> getNewSearchList(vector<GameNode *> &toSearchList, vector<GameNode *> &checkedList);//gets new list to search for the object

    friend ostream& operator <<(ostream& outs, GameNode& outputThis){
        outs<<outputThis.pebble;
    }

    int getPebble(){return pebble;}//returns if the current node has a pebble




    Position currentPosition;//current position of the node, row an colum
    int pebble;//pebble on the node, no pebble, super pebble, or regular pebble

    SpriteClass* mysprite[4];//array of sprites
    int spriteCount;//sprite count

    GameNode* link[4];//the links to the next node
    int linkCount;//the link count

};







#endif // GAMENODE_H
