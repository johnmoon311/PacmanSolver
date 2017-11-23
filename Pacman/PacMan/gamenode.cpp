#include "gamenode.h"

GameNode::GameNode(int spriteSelection, int pebbleSelection, int row, int colum, int ghostSkill):pebble(pebbleSelection){
    for(int i=0; i<4; i++){
        mysprite[i]=nullptr;
    }
    for(int i=0; i<4; i++){
        link[i]=nullptr;
    }

    spriteCount=0;

    linkCount=0;

    currentPosition.SetPosition(colum, row);

    switch(spriteSelection){
    case Empty:
        break;
    case Pacman:
        mysprite[spriteCount]=new PacMan('P');
        spriteCount++;
        break;

    case GhostSet:
        mysprite[spriteCount]=new Ghost('G', ghostSkill);
        spriteCount++;
        break;


    }




}

GameNode::~GameNode(){
    for(int i=0; i<spriteCount; i++){
        if(this->mysprite[i]!=nullptr){
            delete mysprite[i];
        }
    }
}

void GameNode::LinkNodes(GameNode* &linkThis){
    this->link[linkCount]=linkThis;
    linkCount++;

    linkThis->link[linkThis->linkCount]=this;
    linkThis->linkCount++;
}

vector<GameNode*> GameNode::findGhostOnMap(GameNode* gameBoard[][MAX_COLUM]){
    vector<GameNode*> ghostPosition;

    for(int i=0; i<MAX_ROW; i++){
        for(int j=0; j<MAX_COLUM; j++){
            if(gameBoard[i][j]!=nullptr){
                if(!gameBoard[i][j]->isSpriteEmpty()){

                    for(int k=0; k<gameBoard[i][j]->spriteCount; k++){

                        if(gameBoard[i][j]->mysprite[k]->getFace()=='G'){

                            if(gameBoard[i][j]->mysprite[k]->spriteMood!=Runaway){

                                ghostPosition.push_back(gameBoard[i][j]);
                            }

                        }
                    }
                }
            }
        }
    }
    return ghostPosition;
}


vector<GameNode*> GameNode::getGhostPositionInCheckedList(GameNode* gameBoard[][MAX_COLUM]){

    vector<GameNode*> ghostPosition=findGhostOnMap(gameBoard);

    vector<GameNode*> checkedList;

    vector<GameNode*> tempCheckList;

    vector<GameNode*> ghostPath;

    vector<GameNode*> toSearchList;

    for(int i=0; i<linkCount; i++){
        toSearchList.push_back(link[i]);
    }


    for(int i=0; i< ghostPosition.size(); i++){

        tempCheckList.clear();

        ghostPath.clear();

        tempCheckList.push_back(this);


        findClosestGhost(toSearchList, tempCheckList, ghostPath, ghostPosition[i]);


        if(ghostPath.size()<4){

            for(int k=ghostPath.size()-1; k>=0; k--){

                checkedList.insert(checkedList.begin(), ghostPath[k]);
            }

        }



    }



    return checkedList;
}



void GameNode::findClosestGhost(vector<GameNode *> &toSearchList, vector<GameNode *> &checkedList, vector<GameNode*> &ghostPath, GameNode* &findThisGhost){
    for(vector<GameNode*>::iterator it = toSearchList.begin(); it != toSearchList.end(); ++it){
        if(!(*it)->isSpriteEmpty()){
            if((*it)==findThisGhost){
                ghostPath.insert(ghostPath.begin(), (*it));
                return;
            }
        }
    }

    vector<GameNode*> newSearchList=getNewSearchList(toSearchList, checkedList);


    findClosestGhost(newSearchList, checkedList, ghostPath, findThisGhost);

    for(vector<GameNode*>::iterator chked=checkedList.begin(); chked!=checkedList.end(); ++chked){
        for(int i=0; i<(*chked)->linkCount; i++){
            if((*chked)->link[i]==ghostPath[0]){
                ghostPath.insert(ghostPath.begin(),(*chked));
                return;
            }
        }
    }
}


void GameNode::setMoveDirection(int spriteIndex, GameNode* nextPathNode){
    Position nextPosition=nextPathNode->currentPosition;

    if(this->currentPosition.row>nextPosition.row){
        this->mysprite[spriteIndex]->spriteMoveDirection=Up;
    }
    else if(this->currentPosition.row<nextPosition.row){
        this->mysprite[spriteIndex]->spriteMoveDirection=Down;
    }
    else if(this->currentPosition.colum<nextPosition.colum){
        this->mysprite[spriteIndex]->spriteMoveDirection=Right;
    }
    else if(this->currentPosition.colum>nextPosition.colum){
        this->mysprite[spriteIndex]->spriteMoveDirection=Left;
    }


}





vector<GameNode*> GameNode::getSearchList(vector<GameNode*> &checkedList){
    vector<GameNode*> toSearchList;

    for(int i=0; i<this->linkCount; i++){
        bool isLinkThere=false;

        for(int j=0; j<checkedList.size(); j++){
            if(link[i]==checkedList[j]){
                isLinkThere=true;
            }
        }

        if(!isLinkThere){
            toSearchList.push_back(link[i]);
        }

    }
    return toSearchList;

}


//moves the sprite
//depending if the sprite is a pacman or ghost
void GameNode::Move(GameNode* gameBoard[][MAX_COLUM], int pebbleCount, int superPebbleCount){



    for(int i=0; i<spriteCount; i++){

        if(!this->mysprite[i]->getHasMoved()){


            switch(this->mysprite[i]->getFace()){


            case 'P':
                //if there are pebbles to chase
                if(pebbleCount>NoPebble){

                    vector<GameNode*> checkedList;


                    this->mysprite[i]->path.clear();


                    checkedList=getGhostPositionInCheckedList(gameBoard);

                    if(!checkedList.empty()){
                        mysprite[i]->spriteMood=AvoidGhost;


                    }
                    else{
                        mysprite[i]->spriteMood=GetPebble;


                    }




                    if(this->mysprite[i]->spriteMood==GetPebble){



                        vector<GameNode*> checkedList;


                        checkedList.insert(checkedList.begin(), this);


                        vector<GameNode*> toSearchList=getSearchList(checkedList);


                        if(!toSearchList.empty()){
                            findClosestPebble(toSearchList, checkedList, i, Pebble);


                            GameNode* nextPath=getNextPath(i);

                            this->mysprite[i]->moveCount++;




                            if(nextPath!=nullptr){
                                setMoveDirection(i, nextPath);



                                this->MoveToPosition(nextPath, i);
                            }
                        }
                        else{

                            GameNode* nextPath=link[rand()%linkCount];
                            setMoveDirection(i, nextPath);
                            this->MoveToPosition(nextPath, i);
                        }



                    }


                    else if (this->mysprite[i]->spriteMood==AvoidGhost){



                        vector<GameNode*> toSearchList=getSearchList(checkedList);





                        if(!toSearchList.empty()){


                            GameNode* nextPath=toSearchList[rand()%toSearchList.size()];

                            setMoveDirection(i, nextPath);

                            this->MoveToPosition(nextPath, i);

                        }
                        else{



                            GameNode* nextPath=link[rand()%linkCount];
                            setMoveDirection(i, nextPath);
                            this->MoveToPosition(nextPath, i);
                        }





                    }
                    else if (this->mysprite[i]->spriteMood==ChaseGhost){


                        vector<GameNode*> checkedList;


                        checkedList.insert(checkedList.begin(), this);


                        vector<GameNode*> toSearchList=getSearchList(checkedList);


                        findClosestPebble(toSearchList, checkedList, i, Pebble);


                        GameNode* nextPath=getNextPath(i);


                        setMoveDirection(i, nextPath);

                        this->mysprite[i]->moveCount++;


                        this->MoveToPosition(nextPath, i);

                    }

                }




                else{
                    GameNode* nextPath=link[rand()%linkCount];
                    setMoveDirection(i, nextPath);
                    this->MoveToPosition(nextPath, i);
                }



                break;




            case 'G':


                if(mysprite[i]->spriteMood!=Runaway){

                    if(mysprite[i]->moveCount%2==0){
                        mysprite[i]->spriteMood=ChasePacman;
                        mysprite[i]->moveCount=0;
                    }
                    else{
                        mysprite[i]->spriteMood=MoveRandom;
                    }
                }



                if(this->mysprite[i]->path.empty()){


                    if(mysprite[i]->spriteMood==ChasePacman&&mysprite[i]->getGhostIntellegence()==Follower){


                        vector<GameNode*> toSearchList;

                        for(int i=0; i<linkCount; i++){
                            toSearchList.push_back(link[i]);
                        }

                        vector<GameNode*> checkedList;

                        checkedList.insert(checkedList.begin(), this);

                        findClosestPathToPacMan(toSearchList, checkedList, i);

                        mysprite[i]->moveCount++;


                    }


                    else if(mysprite[i]->spriteMood==Runaway){
                        vector<GameNode*> toSearchList;

                        for(int i=0; i<linkCount; i++){
                            toSearchList.push_back(link[i]);
                        }

                        vector<GameNode*> checkedList;

                        checkedList.insert(checkedList.begin(), this);

                        findClosestPathToPacMan(toSearchList, checkedList, i);

                        vector<GameNode*> pacManPath=this->mysprite[i]->path;

                        this->mysprite[i]->path.clear();

                        if(pacManPath.size()<3){

                            vector<GameNode*> nextPath=getSearchList(pacManPath);

                            this->mysprite[i]->path.push_back(nextPath[rand()%nextPath.size()]);
                        }
                        else{
                            generateRandomPath(i, gameBoard);
                        }

                    }





                    else if(mysprite[i]->spriteMood==MoveRandom||mysprite[i]->getGhostIntellegence()!=Follower) {


                        generateRandomPath(i, gameBoard);

                        mysprite[i]->moveCount++;


                    }


                }


                GameNode* nextPath=getNextPath(i);

                if(nextPath!=nullptr){
                    setMoveDirection(i, nextPath);



                    this->MoveToPosition(nextPath, i);
                }

                else{

                    this->MoveToPosition(link[rand()%linkCount], i);
                }




                break;

            }
        }
    }
}






GameNode* GameNode::getNextPath(int spriteIndex){

    for(int i=0; i<this->linkCount; i++){

        for(vector<GameNode*>::iterator it=this->mysprite[spriteIndex]->path.begin(); it!=this->mysprite[spriteIndex]->path.end(); it++){

            if(link[i]==(*it)){

                this->mysprite[spriteIndex]->path.erase(it);

                return link[i];
            }
        }
    }
    return nullptr;
}

void GameNode::findClosestPathToPosition(vector<GameNode *> &toSearchList, vector<GameNode *> &checkedList, int spriteIndex, GameNode* findThisPosition){
    for(vector<GameNode*>::iterator it = toSearchList.begin(); it != toSearchList.end(); ++it){
        if((*it)==findThisPosition){
            this->mysprite[spriteIndex]->path.insert(this->mysprite[spriteIndex]->path.begin(), (*it));
            return;

        }
    }

    vector<GameNode*> newSearchList=getNewSearchList(toSearchList, checkedList);


    findClosestPathToPosition(newSearchList, checkedList, spriteIndex, findThisPosition);

    for(vector<GameNode*>::iterator chked=checkedList.begin(); chked!=checkedList.end(); ++chked){
        for(int i=0; i<(*chked)->linkCount; i++){
            if((*chked)->link[i]==this->mysprite[spriteIndex]->path[0]){
                this->mysprite[spriteIndex]->path.insert(this->mysprite[spriteIndex]->path.begin(), (*chked));
                return;
            }
        }
    }
}

void GameNode::generateRandomPath(int spriteIndex, GameNode* gameBoard[][MAX_COLUM]){
    bool getRandomPosition=false;
    int row=0;
    int colum=0;



    while(!getRandomPosition){
        row=rand()%(MAX_ROW);
        colum=rand()%(MAX_COLUM);

        if(gameBoard[row][colum]!=nullptr){
            getRandomPosition=true;
        }

    }




    vector<GameNode *> checkedList;


    vector<GameNode*> toSearchList=getSearchList(checkedList);

    findClosestPathToPosition(toSearchList, checkedList, spriteIndex, gameBoard[row][colum]);






}

void GameNode::findClosestPathToPacMan(vector<GameNode *> &toSearchList, vector<GameNode *> &checkedList, int spriteIndex){
    for(vector<GameNode*>::iterator it = toSearchList.begin(); it != toSearchList.end(); ++it){
        if(!(*it)->isSpriteEmpty()){
            if((*it)->mysprite[((*it)->spriteCount)-1]->getFace()=='P'){
                this->mysprite[spriteIndex]->path.insert(this->mysprite[spriteIndex]->path.begin(), (*it));
                return;
            }
        }
    }

    vector<GameNode*> newSearchList=getNewSearchList(toSearchList, checkedList);


    findClosestPathToPacMan(newSearchList, checkedList, spriteIndex);

    for(vector<GameNode*>::iterator chked=checkedList.begin(); chked!=checkedList.end(); ++chked){
        for(int i=0; i<(*chked)->linkCount; i++){
            if((*chked)->link[i]==this->mysprite[spriteIndex]->path[0]){
                this->mysprite[spriteIndex]->path.insert(this->mysprite[spriteIndex]->path.begin(), (*chked));
                return;
            }
        }
    }
}




void GameNode::findClosestPebble(vector<GameNode*> &toSearchList, vector<GameNode*> &checkedList, int spriteIndex, int pebbleType){
    for(vector<GameNode*>::iterator it = toSearchList.begin(); it != toSearchList.end(); ++it){
        if((*it)->pebble==pebbleType){
            this->mysprite[spriteIndex]->path.insert(this->mysprite[spriteIndex]->path.begin(), (*it));
            return;
        }
    }

    vector<GameNode*> newSearchList=getNewSearchList(toSearchList, checkedList);


    findClosestPebble(newSearchList, checkedList, spriteIndex, pebbleType);

    for(vector<GameNode*>::iterator chked=checkedList.begin(); chked!=checkedList.end(); ++chked){
        for(int i=0; i<(*chked)->linkCount; i++){
            if((*chked)->link[i]==this->mysprite[spriteIndex]->path[0]){
                this->mysprite[spriteIndex]->path.insert(this->mysprite[spriteIndex]->path.begin(), (*chked));
                return;
            }
        }
    }


}




vector<GameNode*> GameNode::getNewSearchList(vector<GameNode *> &toSearchList, vector<GameNode *> &checkedList){
    vector<GameNode*> newSearchList;

    for(vector<GameNode*>::iterator it = toSearchList.begin(); it != toSearchList.end(); ++it){

        for(int i=0; i<(*it)->linkCount; i++){
            bool hasLink=false;

            for(vector<GameNode*>::iterator chked=checkedList.begin(); chked!=checkedList.end(); ++chked){
                if((*it)->link[i]==(*chked)){
                    hasLink=true;
                }
            }
            if(!hasLink){
                newSearchList.push_back((*it)->link[i]);
            }
        }

        checkedList.push_back((*it));
    }
    return newSearchList;
}


void GameNode::MoveToPosition(GameNode* &moveHere, int spriteIndex){

    moveHere->mysprite[moveHere->spriteCount]=this->mysprite[spriteIndex];

    this->mysprite[spriteIndex]->setHasMoved();

    moveHere->spriteCount++;





    if((this->spriteCount-1)==spriteIndex){
        for(int i=0; i<this->spriteCount ;i++){
            this->mysprite[i]=nullptr;
        }
        this->spriteCount=0;
    }



}
