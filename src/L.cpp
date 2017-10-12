/*
 * File:   L.cpp
 * Author: juan
 *
 * Created on 19 de septiembre de 2017, 11:28 PM
 */

#include "L.h"

L::L() {
}

L::L(const L& orig) {
}

L::~L() {
}

L::L(int x, int y, int squareSize, int color, SDL_Surface* gScreenSurface)
    :Piece(x,y,squareSize,color,gScreenSurface){
       this-> maxStates = 4;
       printf("generated done\n");
}

//L::~L(){}

//the sizes are relatives to the before for fun*
void L::setState0(){
    shape[0].x = topLeftX();
    shape[0].y = topLeftY();

    shape[1].x = midLeftX();
    shape[1].y = midLeftY();

    shape[2].x = botLeftX();
    shape[2].y = botLeftY();

    shape[3].x = botCenterX();
    shape[3].y = botCenterY();
}

void L::setState1(){
    shape[0].x = midLeftX();
    shape[0].y = midLeftY();

    shape[1].x = midCenterX();
    shape[1].y = midCenterY();

    shape[2].x = midRightX();
    shape[2].y = midRightY();

    shape[3].x = topRightX();
    shape[3].y = topRightY();
}
void L::setState2(){
    shape[0].x = topLeftX();
    shape[0].y = topLeftY();

    shape[1].x = topCenterX();
    shape[1].y = topCenterY();

    shape[2].x = midCenterX();
    shape[2].y = midCenterY();

    shape[3].x = botCenterX();
    shape[3].y = botCenterY();
}
void L::setState3(){
    shape[0].x = topLeftX();
    shape[0].y = topLeftY();

    shape[1].x = topCenterX();
    shape[1].y = topCenterY();

    shape[2].x = topRightX();
    shape[2].y = topRightY();

    shape[3].x = midLeftX();
    shape[3].y = midLeftY();
}


