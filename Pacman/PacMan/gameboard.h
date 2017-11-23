#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "gamenode.h"
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include <vector>
#include "animatedsprite.h"
#include "pacmananimation.h"



using namespace std;

const float speed=4;



class GameBoard
{
public:
    GameBoard();

    ~GameBoard();

    bool isInBound(int i, int j);//tells if the row and colum is a wall or a free space

    void Step();//next step

    void CheckPacmanSuperPebble();//counts if pac man has eaten the super pebble

    void CountSuperPebble(int tempSuperPebbleCount);//if super pebble is less than before, pac man chases ghost

    void CountPebble();//counts the current pebble

    void ResetGame();//resets the game if pac man loses

    void ResetPacMan(int row, int colum);//resets pacman to original position

    void CheckCollision();//checks the collision of ghosts and pebble

    void ResetGhost(int row, int colum);//resets the ghost in the ghost box

    void ResetGraphics();//resets all the graphics

    void Show();//shows the printed form of the gameboard in console

    void SetAnimatedDirection(int row, int colum, int spriteIndex);//sets the animation direction

    bool hasFinishedMove();//tells if the sprite animation has finished moving to next node

    void MoveSprite(int row, int colum, int spriteIndex);//moves the sprite to the next node



    sf::RectangleShape gameBoardGraphic[MAX_ROW][MAX_COLUM];//game board graphics with sfml
    vector<sf::CircleShape> pebbleGraphic;//the pebbles graphics on the gameboard
    int pebbleCount;//pebble count
    int superPebbleCount;//super pebble count
    bool restartGame;//checks if game has been restarted


    AnimatedSprite PacManAnimatedSprite;//the pac man animation sprite
    PacManAnimation pacmanAnimation;//the current pac man animation


private:
    GameNode* gameBoard[MAX_ROW][MAX_COLUM];
};

#endif // GAMEBOARD_H
