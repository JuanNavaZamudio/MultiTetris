/*
 * File:   O.cpp
 * Author: juan
 *
 * Created on 19 de septiembre de 2017, 11:29 PM
 */
#include <SDL2/SDL.h>

#include "O.h"

O::O() {
}

O::O(const O& orig) {
}

O::~O() {
}

O::O(int x, int y, int squareSize, int color, SDL_Surface* gScreenSurface)
    :Piece(x,y,squareSize,color,gScreenSurface){
        this->maxStates = 1;
        printf("generated done\n");
}

//the sizes are relatives to the before for fun*
void O::setState0(){
    shape[0].x = topLeftX();
    shape[0].y = topLeftY();

    shape[1].x = topCenterX();
    shape[1].y = topCenterY();

    shape[2].x = midLeftX();
    shape[2].y = midLeftY();

    shape[3].x = midCenterX();
    shape[3].y = midCenterY();
}

void O::setState1(){

}
void O::setState2(){

}
void O::setState3(){

}

