/*
 * File:   J.cpp
 * Author: juan
 *
 * Created on 19 de septiembre de 2017, 11:28 PM
 */

#include "J.h"

J::J() {
}

J::J(const J& orig) {
}

J::~J() {
}

J::J(int x, int y, int squareSize, int color, SDL_Surface* gScreenSurface)
    :Piece(x,y,squareSize,color,gScreenSurface){
        this->maxStates = 4;
        printf("generated done\n");
}

void J::setState0(){
    shape[0].x = topCenterX();
    shape[0].y = topCenterY();

    shape[1].x = midCenterX();
    shape[1].y = midCenterY();

    shape[2].x = botCenterX();
    shape[2].y = botCenterY();

    shape[3].x = botLeftX();
    shape[3].y = botLeftY();
}

void J::setState1(){
    shape[0].x = topLeftX();
    shape[0].y = topLeftY();

    shape[1].x = topCenterX();
    shape[1].y = topCenterY();

    shape[2].x = topRightX();
    shape[2].y = topRightY();

    shape[3].x = midRightX();
    shape[3].y = midRightY();
}
void J::setState2(){
    shape[0].x = topLeftX();
    shape[0].y = topLeftY();

    shape[1].x = topCenterX();
    shape[1].y = topCenterY();

    shape[2].x = midLeftX();
    shape[2].y = midLeftY();

    shape[3].x = botLeftX();
    shape[3].y = botLeftY();
}
void J::setState3(){
    shape[0].x = topLeftX();
    shape[0].y = topLeftY();

    shape[1].x = midLeftX();
    shape[1].y = midLeftY();

    shape[2].x = midCenterX();
    shape[2].y = midCenterY();

    shape[3].x = midRightX();
    shape[3].y = midRightY();
}

