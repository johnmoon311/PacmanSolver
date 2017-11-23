//John Moon
//Pac man Path Finding
//PROJECT DONE

#include <iostream>
#include "gameboard.h"

using namespace std;

int main()
{   GameBoard test;

    sf::Font MarioFont;
    if (!MarioFont.loadFromFile("RealMarioFont.ttf"))
        cout<<"Font file not found!"<<endl;

    sf::Text GameOver;
    GameOver.setFont(MarioFont);
    GameOver.setString("YOU WIN!!!");
    GameOver.setCharacterSize(100);
    GameOver.setColor(sf::Color::White);
    GameOver.setStyle(sf::Text::Bold | sf::Text::Underlined);
    GameOver.setPosition((SCREEN_LENGTH/2)-250, (SCREEN_HEIGHT/2)-100);


    sf::RenderWindow window;
    window.create(sf::VideoMode(SCREEN_LENGTH, SCREEN_HEIGHT), "PAC MAN");
    window.setFramerateLimit(7);

    test.Show();

    bool gameOver=false;

    sf::Clock frameClock;

    while(window.isOpen()){
        sf::Event event;



        while(window.pollEvent(event)){


            if(event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Escape)
                    window.close();

                if(event.key.code == sf::Keyboard::Return){
                    test.Step();


                }

            }
        }
        sf::Time frameTime = frameClock.restart();


        if(!gameOver){
            test.Step();


            test.PacManAnimatedSprite.play(*(test.pacmanAnimation.currentAnimation));
            test.PacManAnimatedSprite.update(frameTime);

            window.clear(sf::Color::Black);
            for(int i=0; i<MAX_ROW; i++){
                for(int j=0; j<MAX_COLUM; j++){
                    window.draw(test.gameBoardGraphic[i][j]);
                }
            }

            for(int i=0; i<test.pebbleGraphic.size(); i++){
                window.draw(test.pebbleGraphic[i]);
            }
            window.draw(test.PacManAnimatedSprite);

            window.display();

            if(test.pebbleCount==0){
                gameOver=true;
                test.PacManAnimatedSprite.stop();

            }
        }
        else{
            window.draw(GameOver);
            window.display();
        }






    }



    return 0;
}

