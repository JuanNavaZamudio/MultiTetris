/*
 * File:   Z.cpp
 * Author: juan
 *
 * Created on 19 de septiembre de 2017, 11:28 PM
 */

#include "Z.h"

Z::Z() {
}

Z::Z(const Z& orig) {
}

Z::~Z() {
}

Z::Z(int x, int y, int squareSize, int color, SDL_Surface* gScreenSurface)
    :Piece(x,y,squareSize,color,gScreenSurface){
        this->maxStates = 2;
        printf("generated done\n");
}

//the sizes are relatives to the before for fun*
void Z::setState0(){
    shape[0].x = topLeftX();
    shape[0].y = topLeftY();

    shape[1].x = topCenterX();
    shape[1].y = topCenterY();

    shape[2].x = midCenterX();
    shape[2].y = midCenterY();

    shape[3].x = midRightX();
    shape[3].y = midRightY();
}

void Z::setState1(){
    shape[0].x = topCenterX();
    shape[0].y = topCenterY();

    shape[1].x = midCenterX();
    shape[1].y = midCenterY();

    shape[2].x = midLeftX();
    shape[2].y = midLeftY();

    shape[3].x = botLeftX();
    shape[3].y = botLeftY();
}
void Z::setState2(){

}
void Z::setState3(){

}

