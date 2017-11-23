#include "pacmananimation.h"

PacManAnimation::PacManAnimation()
{

    if (!texture.loadFromFile("PacMan.png"))
    {
        std::cout << "Failed to load player spritesheet!" << std::endl;

    }




    walkingAnimation[Down].setSpriteSheet(texture);
    walkingAnimation[Down].addFrame(sf::IntRect(0, 0, 16, 16));
    walkingAnimation[Down].addFrame(sf::IntRect(16, 0, 16, 16));
    walkingAnimation[Down].addFrame(sf::IntRect(32, 0, 16, 16));


    walkingAnimation[Up].setSpriteSheet(texture);
    walkingAnimation[Up].addFrame(sf::IntRect(0, 16, 16, 16));
    walkingAnimation[Up].addFrame(sf::IntRect(16, 16, 16, 16));
    walkingAnimation[Up].addFrame(sf::IntRect(32, 16, 16, 16));

    walkingAnimation[Left].setSpriteSheet(texture);
    walkingAnimation[Left].addFrame(sf::IntRect(0, 32, 16, 16));
    walkingAnimation[Left].addFrame(sf::IntRect(16, 32, 16, 16));
    walkingAnimation[Left].addFrame(sf::IntRect(32, 32, 16, 16));

    walkingAnimation[Right].setSpriteSheet(texture);
    walkingAnimation[Right].addFrame(sf::IntRect(0, 48, 16, 16));
    walkingAnimation[Right].addFrame(sf::IntRect(16, 48, 16, 16));
    walkingAnimation[Right].addFrame(sf::IntRect(32, 48, 16, 16));




    currentAnimation=&(walkingAnimation[Left]);
}


void PacManAnimation::setPacManDirection(int direction){
    currentAnimation=&(walkingAnimation[direction]);
}
