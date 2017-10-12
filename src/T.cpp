/*
 * File:   T.cpp
 * Author: juan
 *
 * Created on 19 de septiembre de 2017, 11:28 PM
 */

#include "T.h"

T::T() {
}

T::T(const T& orig) {
}

T::~T() {
}

T::T(int x, int y, int squareSize, int color, SDL_Surface* gScreenSurface)
    :Piece(x,y,squareSize,color,gScreenSurface){
        this->maxStates = 4;
        printf("generated done\n");
}

//the sizes are relatives to the before for fun*
void T::setState0(){
    shape[0].x = topLeftX();
    shape[0].y = topLeftY();

    shape[1].x = midCenterX();
    shape[1].y = midCenterY();

    shape[2].x = topCenterX();
    shape[2].y = topCenterY();

    shape[3].x = topRightX();
    shape[3].y = topRightY();
}

void T::setState1(){
    shape[0].x = topLeftX();
    shape[0].y = topLeftY();

    shape[1].x = midLeftX();
    shape[1].y = midLeftY();

    shape[2].x = midCenterX();
    shape[2].y = midCenterY();

    shape[3].x = botLeftX();
    shape[3].y = botLeftY();
}
void T::setState2(){
    shape[0].x = topCenterX();
    shape[0].y = topCenterY();

    shape[1].x = midLeftX();
    shape[1].y = midLeftY();

    shape[2].x = midCenterX();
    shape[2].y = midCenterY();

    shape[3].x = midRightX();
    shape[3].y = midRightY();
}
void T::setState3(){
    shape[0].x = midLeftX();
    shape[0].y = midLeftY();

    shape[1].x = topCenterX();
    shape[1].y = topCenterY();

    shape[2].x = midCenterX();
    shape[2].y = midCenterY();

    shape[3].x = botCenterX();
    shape[3].y = botCenterY();
}

