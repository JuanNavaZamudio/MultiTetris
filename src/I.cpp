/*
 * File:   I.cpp
 * Author: juan
 *
 * Created on 19 de septiembre de 2017, 11:29 PM
 */

#include "I.h"

I::I() {
}

I::I(const I& orig) {
}

I::I(int x, int y, int squareSize, int color, SDL_Surface* gScreenSurface)
    :Piece(x,y,squareSize,color,gScreenSurface){
       this-> maxStates = 2;
       printf("generated done\n");
}

I::~I() {
}

//the sizes are relatives to the before for fun*
void I::setState0(){
    shape[0].x = topLeftX();
    shape[0].y = topLeftY();

    shape[1].x = midLeftX();
    shape[1].y = midLeftY();

    shape[2].x = botLeftX();
    shape[2].y = botLeftY();

    shape[3].x = bot2LeftX();
    shape[3].y = bot2LeftY();
}

void I::setState1(){
    shape[0].x = topLeftX();
    shape[0].y = topLeftY();

    shape[1].x = topCenterX();
    shape[1].y = topCenterY();

    shape[2].x = topRightX();
    shape[2].y = topRightY();

    shape[3].x = top2RightX();
    shape[3].y = top2RightY();
}
void I::setState2(){

}
void I::setState3(){

}

