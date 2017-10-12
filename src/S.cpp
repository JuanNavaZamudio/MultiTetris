/*
 * File:   S.cpp
 * Author: juan
 *
 * Created on 19 de septiembre de 2017, 11:28 PM
 */

#include "S.h"

S::S() {
}

S::S(const S& orig) {
}

S::~S() {
}

S::S(int x, int y, int squareSize, int color, SDL_Surface* gScreenSurface)
    :Piece(x,y,squareSize,color,gScreenSurface){
        this->maxStates = 2;
        printf("generated done\n");
}

//S::~S(){}

//the sizes are relatives to the before for fun*
void S::setState0(){
    shape[0].x = topCenterX();
    shape[0].y = topCenterY();

    shape[1].x = midCenterX();
    shape[1].y = midCenterY();

    shape[2].x = midLeftX();
    shape[2].y = midLeftY();

    shape[3].x = topRightX();
    shape[3].y = topRightY();
}

void S::setState1(){
    shape[0].x = topLeftX();
    shape[0].y = topLeftY();

    shape[1].x = midLeftX();
    shape[1].y = midLeftY();

    shape[2].x = midCenterX();
    shape[2].y = midCenterY();

    shape[3].x = botCenterX();
    shape[3].y = botCenterY();
}
void S::setState2(){

}
void S::setState3(){

}

