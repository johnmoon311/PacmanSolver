#include "gameboard.h"

GameBoard::GameBoard():PacManAnimatedSprite(sf::seconds(0.2), true, false), pacmanAnimation()
{   int row=0;
    int colum=0;
    int ghostSkill=0;
    pebbleCount=0;
    superPebbleCount=0;
    restartGame=false;

    PacManAnimatedSprite.setScale(sf::Vector2f(1.5, 1.5));
    PacManAnimatedSprite.setAnimation(*(pacmanAnimation.currentAnimation));

    srand(time(NULL));


    for(int i=0; i<MAX_ROW; i++){
        for(int j=0; j<MAX_COLUM; j++){
            gameBoardGraphic[i][j].setSize(sf::Vector2f(BOX_SIZE-1, BOX_SIZE-1));
            gameBoardGraphic[i][j].setOutlineColor(sf::Color::Black);
            gameBoardGraphic[i][j].setOutlineThickness(1);
            gameBoardGraphic[i][j].setPosition(((SCREEN_LENGTH-(MAX_COLUM*BOX_SIZE))/2)+(j*BOX_SIZE), ((SCREEN_HEIGHT-(MAX_ROW*BOX_SIZE))/2)+(i*BOX_SIZE));
        }
    }



    int test=1;

    fstream file;

    file.open("test.rtf");

    if(file.fail()){
        cout<<"file failed to open!!!"<<endl;
    }

    while(!file.eof()){
        char input=file.get();

        cout<<input<<" ";

        if(input=='|'){
            gameBoard[row][colum]=nullptr;
            gameBoardGraphic[row][colum].setFillColor(sf::Color::Red);
            colum++;
        }

        else if(input=='X'){
            gameBoard[row][colum]=nullptr;
            gameBoardGraphic[row][colum].setFillColor(sf::Color::Black);
            colum++;
        }

        else if (input=='#'){

            //creates a new node
            gameBoard[row][colum]=new GameNode(Empty, Pebble, row, colum, ghostSkill);

            //sets the space color to black
            gameBoardGraphic[row][colum].setFillColor(sf::Color::Black);

            sf::CircleShape tempPebble;
            //sets the pebbles in empty spaces
            tempPebble.setRadius(2);
            tempPebble.setPosition((gameBoardGraphic[row][colum].getPosition().x)+(BOX_SIZE/2),(gameBoardGraphic[row][colum].getPosition().y)+(BOX_SIZE/2));
            tempPebble.setFillColor(sf::Color::White);

            pebbleGraphic.push_back(tempPebble);
            pebbleCount++;



            //sets the links!!!!!!
            if(isInBound(row-1, colum)){
                gameBoard[row][colum]->LinkNodes(gameBoard[row-1][colum]);
            }

            if(isInBound(row, colum-1)){
                gameBoard[row][colum]->LinkNodes(gameBoard[row][colum-1]);
            }



            colum++;

        }

        else if (input=='!'){

            //creates a new node
            gameBoard[row][colum]=new GameNode(Empty, SuperPebble, row, colum, ghostSkill);

            //sets the space color to black
            gameBoardGraphic[row][colum].setFillColor(sf::Color::Black);

            sf::CircleShape tempPebble;
            //sets the pebbles in empty spaces
            tempPebble.setRadius(3);
            tempPebble.setPosition((gameBoardGraphic[row][colum].getPosition().x)+(BOX_SIZE/2),(gameBoardGraphic[row][colum].getPosition().y)+(BOX_SIZE/2));
            tempPebble.setFillColor(sf::Color::White);

            pebbleGraphic.push_back(tempPebble);
            superPebbleCount++;




            //sets the links!!!!!!
            if(isInBound(row-1, colum)){
                gameBoard[row][colum]->LinkNodes(gameBoard[row-1][colum]);
            }

            if(isInBound(row, colum-1)){
                gameBoard[row][colum]->LinkNodes(gameBoard[row][colum-1]);
            }



            colum++;

        }

        else if (input=='>'){

            //creates a new node
            gameBoard[row][colum]=new GameNode(Empty, Pebble, row, colum, ghostSkill);

            //sets the space color to black
            gameBoardGraphic[row][colum].setFillColor(sf::Color::Black);

            sf::CircleShape tempPebble;
            //sets the pebbles in empty spaces
            tempPebble.setRadius(2);
            tempPebble.setPosition((gameBoardGraphic[row][colum].getPosition().x)+(BOX_SIZE/2),(gameBoardGraphic[row][colum].getPosition().y)+(BOX_SIZE/2));
            tempPebble.setFillColor(sf::Color::White);

            pebbleGraphic.push_back(tempPebble);
            pebbleCount++;



            //sets the links!!!!!!
            if(isInBound(row-1, colum)){
                gameBoard[row][colum]->LinkNodes(gameBoard[row-1][colum]);
            }

            if(isInBound(row, colum-1)){
                gameBoard[row][colum]->LinkNodes(gameBoard[row][colum-1]);
            }

            gameBoard[row][colum]->LinkNodes(gameBoard[row][0]);


            colum++;

        }
        else if (input=='@'){

            //creates a new node
            gameBoard[row][colum]=new GameNode(Empty, NoPebble, row, colum, ghostSkill);

            //sets the space color to black
            gameBoardGraphic[row][colum].setFillColor(sf::Color::Black);



            //sets the links!!!!!!
            if(isInBound(row-1, colum)){
                gameBoard[row][colum]->LinkNodes(gameBoard[row-1][colum]);
            }

            if(isInBound(row, colum-1)){
                gameBoard[row][colum]->LinkNodes(gameBoard[row][colum-1]);
            }



            colum++;

        }

        else if(input =='+'){
            //creates a new node!!!
            //PAC MAN!!!!
            gameBoard[row][colum]=new GameNode(Pacman, NoPebble, row, colum, ghostSkill);

            //sets space for yellow represents pacman
            gameBoardGraphic[row][colum].setFillColor(sf::Color::Yellow);

            PacManAnimatedSprite.setPosition(gameBoardGraphic[row][colum].getPosition().x, gameBoardGraphic[row][colum].getPosition().y);

            //links the nodes on top and left
            if(isInBound(row-1, colum)){
                gameBoard[row][colum]->LinkNodes(gameBoard[row-1][colum]);
            }

            if(isInBound(row, colum-1)){
                gameBoard[row][colum]->LinkNodes(gameBoard[row][colum-1]);
            }

            colum++;
        }

        else if (input== '-'){
            //creates a new node!!!
            gameBoard[row][colum]=new GameNode(GhostSet, NoPebble, row, colum, ghostSkill);

            //sets space for yellow represents pacman
            if(ghostSkill==Follower){
                gameBoardGraphic[row][colum].setFillColor(sf::Color::Blue);
            }
            else if(ghostSkill==Ambush){
                gameBoardGraphic[row][colum].setFillColor(sf::Color::Green);
            }
            else if(ghostSkill==Dumb){
                gameBoardGraphic[row][colum].setFillColor(sf::Color::Cyan);
            }
            else if(ghostSkill==Dumber){
                gameBoardGraphic[row][colum].setFillColor(sf::Color::Magenta);
            }

            //links the nodes on top and left
            if(isInBound(row-1, colum)){
                gameBoard[row][colum]->LinkNodes(gameBoard[row-1][colum]);
            }

            if(isInBound(row, colum-1)){
                gameBoard[row][colum]->LinkNodes(gameBoard[row][colum-1]);
            }

            colum++;
            ghostSkill++;
        }


        //if the colums are at max, go to next row
        if(colum==MAX_COLUM){
            row++;
            colum=0;
        }

    }
    file.close();


}




GameBoard::~GameBoard(){
    for(int i=0; i<MAX_ROW; i++){
        for(int j=0; j<MAX_COLUM; j++){
            if(gameBoard[i][j]!=nullptr){
                delete gameBoard[i][j];
            }
        }

    }
}



bool GameBoard::isInBound(int i, int j){
    //tells if the node is a free space or a wall
    if(gameBoard[i][j]!=nullptr){
        return true;
    }
    return false;
}

void GameBoard::CheckPacmanSuperPebble(){
    bool isSuperPebbleDone=false;

    //checks if the pacman is still a super pebble
    for(int i=0; i<MAX_ROW; i++){
        for(int j=0; j<MAX_COLUM; j++){
            if(gameBoard[i][j]!=nullptr){
                if(!gameBoard[i][j]->isSpriteEmpty()){

                    for(int k=0; k<gameBoard[i][j]->spriteCount; k++){

                        if(gameBoard[i][j]->mysprite[k]->getFace()=='P'){
                            if(gameBoard[i][j]->mysprite[k]->moveCount==30){
                                gameBoard[i][j]->mysprite[k]->moveCount=0;
                                gameBoard[i][j]->mysprite[k]->spriteMood=GetPebble;
                                isSuperPebbleDone=true;
                            }
                        }
                    }
                }
            }
        }
    }

    //if the super pebble has worn out,
    //go back to regular ghosts
    if(isSuperPebbleDone){
        for(int i=0; i<MAX_ROW; i++){
            for(int j=0; j<MAX_COLUM; j++){
                if(gameBoard[i][j]!=nullptr){
                    if(!gameBoard[i][j]->isSpriteEmpty()){

                        for(int k=0; k<gameBoard[i][j]->spriteCount; k++){

                            if(gameBoard[i][j]->mysprite[k]->getFace()=='G'){
                                gameBoard[i][j]->mysprite[k]->spriteMood=ChasePacman;
                            }
                        }
                    }
                }
            }
        }
    }
}

//counts all the pebble
void GameBoard::CountPebble(){
    pebbleCount=0;
    for(int i=0; i<MAX_ROW; i++){
        for(int j=0; j<MAX_COLUM; j++){
            if(gameBoard[i][j]!=nullptr){
                if(gameBoard[i][j]->pebble==Pebble){
                    pebbleCount++;
                }
            }
        }
    }
}


//next step
void GameBoard::Step(){


    CountPebble();//counts the pebble

    for(int i=0; i<MAX_ROW; i++){
        for(int j=0; j<MAX_COLUM; j++){
            if(gameBoard[i][j]!=nullptr){

                if(!gameBoard[i][j]->isSpriteEmpty()){

                    if(!restartGame){

                        gameBoard[i][j]->Move(gameBoard, pebbleCount, superPebbleCount); //moves the sprite

                        while(!hasFinishedMove()){}//move the animation

                        CheckCollision();//checks collision

                    }



                }
            }




        }
    }

    ResetGraphics();//reset graphics

    CheckPacmanSuperPebble();//checks if the pacman taken super pebble





}


//counts the super pebble
//if the super pebble count is more than the temp super pebble count then pacman has eaten a super pebble
//sets the ghost to runaway, sets pacman to chase ghosts

void GameBoard::CountSuperPebble(int tempSuperPebbleCount){

    if(tempSuperPebbleCount<superPebbleCount){
        for(int i=0; i<MAX_ROW; i++){

            for(int j=0; j<MAX_COLUM; j++){

                if(gameBoard[i][j]!=nullptr){


                    if(!gameBoard[i][j]->isSpriteEmpty()){

                        for(int k=0; k<gameBoard[i][j]->spriteCount; k++){

                            if(gameBoard[i][j]->mysprite[k]->getFace()=='P'){
                                gameBoard[i][j]->mysprite[k]->spriteMood=ChaseGhost;
                                gameBoard[i][j]->mysprite[k]->moveCount=0;
                            }
                            else if(gameBoard[i][j]->mysprite[k]->getFace()=='G'){
                                gameBoard[i][j]->mysprite[k]->spriteMood=Runaway;
                            }
                        }

                    }
                }
            }
        }
        superPebbleCount=tempSuperPebbleCount;
    }
}


//resets all the graphics
void GameBoard::ResetGraphics(){
    int tempSuperPebbleCount=0;
    pebbleGraphic.clear();

    if(restartGame){

        restartGame=false;
    }


    for(int i=0; i<MAX_ROW; i++){

        for(int j=0; j<MAX_COLUM; j++){

            if(gameBoard[i][j]!=nullptr){



                if(!gameBoard[i][j]->isSpriteEmpty()){

                    for(int k=0; k<gameBoard[i][j]->spriteCount; k++){


                        //sets all the sprites back to has not moved
                        gameBoard[i][j]->mysprite[k]->setHasMoved();

                        //if the game has reset, set all the sprites resets back to false
                        if(gameBoard[i][j]->mysprite[k]->hasResetSprite){
                            gameBoard[i][j]->mysprite[k]->setResetSprite();
                        }



                        //if pacman set the new animation direction
                        if(gameBoard[i][j]->mysprite[k]->getFace()=='P'){

                            SetAnimatedDirection(i, j, k);


                        }

                        //if ghosts set the color of the current ghost
                        else if(gameBoard[i][j]->mysprite[k]->getFace()=='G'){

                            if(gameBoard[i][j]->mysprite[k]->spriteMood!=Runaway){
                                if(gameBoard[i][j]->mysprite[k]->getGhostIntellegence()==Follower){
                                    gameBoardGraphic[i][j].setFillColor(sf::Color::Blue);
                                }
                                else if(gameBoard[i][j]->mysprite[k]->getGhostIntellegence()==Ambush){
                                    gameBoardGraphic[i][j].setFillColor(sf::Color::Green);
                                }
                                else if(gameBoard[i][j]->mysprite[k]->getGhostIntellegence()==Dumb){
                                    gameBoardGraphic[i][j].setFillColor(sf::Color::Cyan);
                                }
                                else if(gameBoard[i][j]->mysprite[k]->getGhostIntellegence()==Dumber){
                                    gameBoardGraphic[i][j].setFillColor(sf::Color::Magenta);
                                }
                            }
                            //if the ghost is running set it to white
                            else{
                                gameBoardGraphic[i][j].setFillColor(sf::Color::White);
                            }
                        }



                    }

                }
                //black is empty space
                else{
                    gameBoardGraphic[i][j].setFillColor(sf::Color::Black);
                }

                //draws the pebble
                if(gameBoard[i][j]->getPebble()==Pebble){
                    sf::CircleShape tempPebble;

                    tempPebble.setRadius(2);

                    tempPebble.setPosition((gameBoardGraphic[i][j].getPosition().x)+(BOX_SIZE/2),(gameBoardGraphic[i][j].getPosition().y)+(BOX_SIZE/2));

                    tempPebble.setFillColor(sf::Color::White);

                    pebbleGraphic.push_back(tempPebble);

                }
                //draws the super pebble
                else if(gameBoard[i][j]->getPebble()==SuperPebble){
                    sf::CircleShape tempPebble;

                    tempPebble.setRadius(3);

                    tempPebble.setPosition((gameBoardGraphic[i][j].getPosition().x)+(BOX_SIZE/2),(gameBoardGraphic[i][j].getPosition().y)+(BOX_SIZE/2));

                    tempPebble.setFillColor(sf::Color::White);

                    pebbleGraphic.push_back(tempPebble);

                    tempSuperPebbleCount++;
                }




            }




        }
    }

    //counts the super pebble
    CountSuperPebble(tempSuperPebbleCount);
}

//checks the collision
//if pacman and ghost are in the same node
//that means there is collision
//if there is collision, check if the ghosts are running or chasing
void GameBoard::CheckCollision(){


    for(int i=0; i<MAX_ROW; i++){

        for(int j=0; j<MAX_COLUM; j++){

            if(gameBoard[i][j]!=nullptr){

                if(!gameBoard[i][j]->isSpriteEmpty()){

                    if(gameBoard[i][j]->spriteCount>1){


                        bool hasPacman=false;
                        bool hasGhost=false;
                        int ghostMood=0;

                        for(int k=0; k<gameBoard[i][j]->spriteCount; k++){


                            if(gameBoard[i][j]->mysprite[k]->getFace()=='P'){
                                hasPacman=true;
                            }
                            else if(gameBoard[i][j]->mysprite[k]->getFace()=='G'){
                                hasGhost=true;
                                ghostMood=gameBoard[i][j]->mysprite[k]->spriteMood;
                            }
                            //there is pacman and ghost in the same node
                            if(hasPacman&&hasGhost){

                                //if the ghosts are runing away
                                if(ghostMood==Runaway){

                                    ResetGhost(i, j);//resets the ghost

                                }
                                //if the ghosts are not running away
                                else if(ghostMood!=Runaway){

                                    ResetGame();//resets the whole game
                                }
                            }
                        }

                    }
                }
            }
        }
    }


}
//resets the ghost and pacman
void GameBoard::ResetGame(){
    restartGame=true;

    for(int i=0; i<MAX_ROW; i++){
        for(int j=0; j<MAX_COLUM; j++){
            if(gameBoard[i][j]!=nullptr){

                if(!gameBoard[i][j]->isSpriteEmpty()){

                    ResetPacMan(i , j);
                    ResetGhost(i, j);


                }
            }
        }
    }
}

//resets pac man to original position
void GameBoard::ResetPacMan(int row, int colum){
    for(int i=0; i<gameBoard[row][colum]->spriteCount; i++){
        if(gameBoard[row][colum]->mysprite[i]->getFace()=='P'){
            if(!gameBoard[row][colum]->mysprite[i]->hasResetSprite){
                PacManAnimatedSprite.setPosition(gameBoardGraphic[17][11].getPosition().x, gameBoardGraphic[17][11].getPosition().y);
                gameBoard[row][colum]->mysprite[i]->setResetSprite();
                gameBoard[17][11]->mysprite[gameBoard[17][11]->spriteCount]=gameBoard[row][colum]->mysprite[i];
                gameBoard[17][11]->spriteCount++;
                gameBoard[row][colum]->mysprite[i]=nullptr;

            }


        }
    }
    int j=0;
    for(int i=0; i<gameBoard[row][colum]->spriteCount; i++){
        if(gameBoard[row][colum]->mysprite[i]!=nullptr){
            gameBoard[row][colum]->mysprite[j] = gameBoard[row][colum]->mysprite[i];
            j++;


        }
    }
    gameBoard[row][colum]->spriteCount=j;

}


//checks if the animation has moved
//teleports the animation if the node goes to the other side
bool GameBoard::hasFinishedMove(){
    for(int i=0; i<MAX_ROW; i++){
        for(int j=0; j<MAX_COLUM; j++){
            if(gameBoard[i][j]!=nullptr){
                for(int k=0; k<gameBoard[i][j]->spriteCount; k++){

                    if(gameBoard[i][j]->mysprite[k]->getFace()=='P'){

                        if(gameBoardGraphic[10][0].getPosition().x==PacManAnimatedSprite.getPosition().x
                                &&gameBoardGraphic[10][0].getPosition().y==PacManAnimatedSprite.getPosition().y
                                &&i==10&&j==22){

                            PacManAnimatedSprite.setPosition(gameBoardGraphic[10][22].getPosition().x, gameBoardGraphic[10][22].getPosition().y);
                            pacmanAnimation.setPacManDirection(Left);
                            gameBoard[i][j]->pebble=NoPebble;

                            return true;
                        }
                        else if(gameBoardGraphic[10][22].getPosition().x==PacManAnimatedSprite.getPosition().x
                                &&gameBoardGraphic[10][22].getPosition().y==PacManAnimatedSprite.getPosition().y
                                &&i==10&&j==0){
                            PacManAnimatedSprite.setPosition(gameBoardGraphic[10][0].getPosition().x, gameBoardGraphic[10][0].getPosition().y);
                            pacmanAnimation.setPacManDirection(Right);
                            gameBoard[i][j]->pebble=NoPebble;
                            return true;
                        }


                        if(PacManAnimatedSprite.getPosition().x+BOX_SIZE/2==gameBoardGraphic[i][j].getPosition().x+BOX_SIZE/2
                                &&PacManAnimatedSprite.getPosition().y+BOX_SIZE/2==gameBoardGraphic[i][j].getPosition().y+BOX_SIZE/2){
                            gameBoard[i][j]->pebble=NoPebble;
                            return true;
                        }
                        else{
                            MoveSprite(i, j, k);
                            return false;
                        }
                    }
                }
            }
        }
    }
}


//moves the sprite animation
void GameBoard::MoveSprite(int row, int colum, int spriteIndex){
    switch(gameBoard[row][colum]->mysprite[spriteIndex]->spriteMoveDirection){
    case Up:
        PacManAnimatedSprite.move(0, -1*speed);
        break;
    case Down:
        PacManAnimatedSprite.move(0, speed);
        break;
    case Left:
        PacManAnimatedSprite.move( -1*speed, 0);
        break;
    case Right:
        PacManAnimatedSprite.move(speed, 0);
        break;
    }
}


//sets the animation direction of sprite
void GameBoard::SetAnimatedDirection(int row, int colum, int spriteIndex){
    pacmanAnimation.setPacManDirection(gameBoard[row][colum]->mysprite[spriteIndex]->spriteMoveDirection);
}



//resets the ghost into the box of ghosts
void GameBoard::ResetGhost(int row, int colum){
    for(int i=0; i<gameBoard[row][colum]->spriteCount; i++){

        if(gameBoard[row][colum]->mysprite[i]->getFace()=='G'){
            if(!gameBoard[row][colum]->mysprite[i]->hasResetSprite){
                gameBoard[row][colum]->mysprite[i]->spriteMood=ChasePacman;
                gameBoard[row][colum]->mysprite[i]->moveCount=0;
                gameBoard[row][colum]->mysprite[i]->path.clear();
                gameBoard[row][colum]->mysprite[i]->setResetSprite();

                gameBoard[11][11]->mysprite[gameBoard[11][11]->spriteCount] = gameBoard[row][colum]->mysprite[i];
                gameBoard[11][11]->spriteCount++;
                gameBoard[row][colum]->mysprite[i]=nullptr;

            }
        }
    }
    int j=0;
    for(int i=0; i<gameBoard[row][colum]->spriteCount; i++){
        if(gameBoard[row][colum]->mysprite[i]!=nullptr){
            gameBoard[row][colum]->mysprite[j] = gameBoard[row][colum]->mysprite[i];
            j++;


        }
    }
    gameBoard[row][colum]->spriteCount=j;


}

void GameBoard::Show(){

    for(int i=0; i<MAX_ROW; i++){
        cout<<endl<<endl<<endl<<endl;

        for(int j=0; j<MAX_COLUM; j++){
            cout<<setw(5);
            if(gameBoard[i][j]!=nullptr){

                if(gameBoard[i][j]->isSpriteEmpty()){
                    cout<<gameBoard[i][j]->getPebble();
                }

                else {
                    for(int k=0; k<gameBoard[i][j]->spriteCount; k++){
                        if(gameBoard[i][j]->mysprite[k]->getFace()=='P'){
                            cout<<"X";
                        }
                        else if(gameBoard[i][j]->mysprite[k]->getFace()=='G'){
                            cout<<"G";
                        }
                    }
                }
            }
            else {
                cout<<"||";
            }
        }

    }
}

