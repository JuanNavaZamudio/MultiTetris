/*
 * File:   Piece.cpp
 * Author: juan
 *
 * Created on 19 de septiembre de 2017, 11:28 PM
 */

#include "Piece.h"

Piece::Piece() {
}

Piece::Piece(const Piece& orig) {
}

Piece::Piece(int x, int y, int squareSize,int color, SDL_Surface* gScreenSurface){
    this->x = x;
    this->y = y;
    this->squareSize = squareSize;
    for(int i = 0; i < 4; i++){
        this->shape[i].size = squareSize;
        this->shape[i].color = color;
    }
    this->color = color;
    this->gScreenSurface = gScreenSurface;

    actVelX = 0;
    actVelY = VEL;
    state = 0;
}

Piece::~Piece() {
}

void Piece::setTexture(SDL_Surface* image){
    for(int i = 0; i < 4; i++){
        shape[i].image = image;
    }
}

//check if the piece falled against some square
bool Piece::ckeckIfHasFallen(Square boardPieces[10][20] ){

    bool collided = false;
    for(int i = 0; i < 20; i++){//rows
        for(int j = 0; j< 10; j++ ){//columns
            //if the space is empty ignore it
            if(boardPieces[j][i].image != NULL){
                for(int k = 0; k < 4; k++){  //squares of the figure
                //compare if each square has fallen with the actual board's piece
                    if( shape[k].x == boardPieces[j][i].x &&
                        shape[k].y + shape[k].size >= boardPieces[j][i].y &&
                        shape[k].y < boardPieces[j][i].y + squareSize
                        )
                    {
                        collided = true;
                        //printf("has fell :0 x %d x %d y %d y %d \n",shape[k].x, boardPieces[j][i].x, shape[k].y + shape[k].size, boardPieces[j][i].y);
                    }
                }
            }
        }
    }

    //collision against the floor
    int bottom = boardPieces[0][19].y;
    int piece = 0;
    for(int i = 0; i< 4 ;i++){
        piece = shape[i].y;
        if(piece > bottom ){
            collided = true;
        }
    }
    return collided;
}

bool Piece::isCollidingToTheLeft(Square boardPieces[10][20]){
    for(int i = 0; i < 20; i++){//rows
        for(int j = 0; j< 10; j++ ){//columns
            if(boardPieces[j][i].image != NULL){
                for(int k = 0; k < 4; k++){  //squares of the figure
                    if( shape[k].x == boardPieces[j][i].x + squareSize &&
                       ((shape[k].y >= boardPieces[j][i].y &&
                         shape[k].y < boardPieces[j][i].y + squareSize)
                        ||
                        (shape[k].y + shape[k].size >= boardPieces[j][i].y &&
                         shape[k].y + shape[k].size < boardPieces[j][i].y + squareSize)
                        )){
                        return true;
                        }
                }
            }
        }
    }

    return false;
}

bool Piece::isCollidingToTheRight(Square boardPieces[10][20]){
    for(int i = 0; i < 20; i++){//rows
        for(int j = 0; j< 10; j++ ){//columns
            if(boardPieces[j][i].image != NULL){
                for(int k = 0; k < 4; k++){  //squares of the figure
                    if( shape[k].x + squareSize == boardPieces[j][i].x &&
                       ((shape[k].y >= boardPieces[j][i].y &&
                        shape[k].y < boardPieces[j][i].y + squareSize)
                        ||
                        (shape[k].y + shape[k].size > boardPieces[j][i].y &&
                         shape[k].y + shape[k].size < boardPieces[j][i].y + squareSize)
                        )){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

//update the spin state
void Piece::spinAntiClock(){

    if(state < maxStates){
        state++;
    }
    if(state == maxStates)
        state = 0;

    updatePos();
}

void Piece::spinClock(){

    if(state > 0)
        state--;
    if(state == 0)
        state = maxStates - 1;

    updatePos();
}

void Piece::updatePos(){
    switch(state){
        case 0:
            setState0();
            break;
        case 1:
            setState1();
            break;
        case 2:
            setState2();
            break;
        case 3:
            setState3();
            break;
    }
}
//paint this piece
void Piece::paint(){
    for(int i = 0; i< 4; i++){
        shape[i].paint(gScreenSurface);
    }
}

//calculate the width for the horizontal change of board
int Piece::calculateWidth(){
    int maxX = shape[0].x;
    for(int i = 1; i < 4; i++)
        if(shape[i].x > maxX)
            maxX = shape[i].x;


    return (maxX + this->squareSize) - this->x ;
}

//calculate the height
int Piece::calculateHeight(){
    int maxY = shape[0].y;
    for(int i = 1; i < 4; i++)
        if(shape[i].y > maxY)
            maxY = shape[i].y;


    return (maxY + this->squareSize) - this->y ;
}

void Piece::handleMovement( SDL_Event& e ){
	if( e.type == SDL_KEYDOWN ){
        switch( e.key.keysym.sym ){
            case SDLK_LEFT: repMov-=1; actVelX = -squareSize; moving = true; break;
            case SDLK_RIGHT: repMov-=1; actVelX = squareSize; moving = true; break;
            case SDLK_DOWN: actVelY = VEL * 4; break;
        }
    }
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 ){
        switch( e.key.keysym.sym ){
            case SDLK_LEFT: repMov = CICLES_TO_HOLD_BUTTON; actVelX = 0; break;
            case SDLK_RIGHT: repMov = CICLES_TO_HOLD_BUTTON; actVelX = 0; break;
            case SDLK_DOWN: actVelY = VEL; break;
        }
    }
}
/*
void Piece::handleVelocityAndSpin( SDL_Event& e ){

    //If a key was pressed wiil do something of the actions
    //change state, fall faster,
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
        switch( e.key.keysym.sym ){
            case SDLK_UP: spinAntiClock();  break;

        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 ){
        //Adjust the velocity
        switch( e.key.keysym.sym ){
            //updateState rotate the falling piece
            case SDLK_UP:  updatePos();  break;

        }
    }
}
*/
int Piece::topLeftX(){return this->x; }
int Piece::topLeftY(){return this->y; }

int Piece::topCenterX(){return this->x + squareSize; }
int Piece::topCenterY(){return this->y; }

int Piece::topRightX(){return this->x + squareSize * 2; }
int Piece::topRightY(){return this->y; }

int Piece::top2RightX(){return this->x + squareSize * 3; }
int Piece::top2RightY(){return this->y; }

int Piece::midLeftX(){return this->x; }
int Piece::midLeftY(){return this->y + squareSize; }

int Piece::midCenterX(){return this->x + squareSize; }
int Piece::midCenterY(){return this->y + squareSize; }

int Piece::midRightX(){return this->x + squareSize * 2; }
int Piece::midRightY(){return this->y + squareSize; }

int Piece::botLeftX(){return this->x; }
int Piece::botLeftY(){return this->y + squareSize * 2; }

int Piece::botCenterX(){return this->x + squareSize; }
int Piece::botCenterY(){return this->y + squareSize * 2; }

int Piece::botRightX(){return this->x + squareSize * 2; }
int Piece::botRightY(){return this->y + squareSize * 2; }

int Piece::bot2LeftX(){return this->x; }
int Piece::bot2LeftY(){return this->y + squareSize * 3; }



