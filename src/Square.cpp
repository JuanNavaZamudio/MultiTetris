/*
 * File:   Square.cpp
 * Author: juan
 *
 * Created on 19 de septiembre de 2017, 11:28 PM
 */
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <sstream>

#include "Square.h"

Square::Square() {

    //x and y in -1 is like the square is uninitialized
    this->x = -1;
    this->y = -1;
    this->size = 0;
    this->color = -1;
}

Square::Square(const Square& orig) {
}

Square::Square(int x, int y, int size, SDL_Surface* image) {
    this->x = x;
    this->y = y;
    this->size = size;
    this->color = -1;

    if (image != NULL)
        this->image = image;

    //initialize the seed to the pseudo random list
    srand( time(NULL) );
}

Square::~Square() {
}

void Square::selectRandom() {

    std::ostringstream name;

    color = rand() % 3; //the images's names are from 0 to
    //printf("pseudorandom: %i\n",color);

    name << "images/" << color << ".bmp" ;
    std::string file = name.str();

    if (!loadFromFile( file )) {
        printf("Failed to load square texture!\n");
    }

}

void Square::selectFromColor(int col) {

    std::ostringstream name;
    name << "images/" << col << ".bmp" ;
    std::string file = name.str();

    if (!loadFromFile( file )) {
        printf("Failed to load square texture!\n");
    }

}

void Square::selectGray() {
    if (!loadFromFile("images/gray.bmp")) {
        printf("Failed to load square texture!\n");
    }
}

void Square::selectGreen() {
    if (!loadFromFile("images/0.bmp")) {
        printf("Failed to load square texture!\n");
    }
}
void Square::selectRed() {
    if (!loadFromFile("images/1.bmp")) {
        printf("Failed to load square texture!\n");
    }
}

bool Square::loadFromFile(std::string path) {

    bool success = false;

    //Load image at specified path
	this->image = SDL_LoadBMP( path.c_str() );
	if( image == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
	}else
        success = true;

    //Return success
    return success;
}

void Square::free() {
    //Free texture if it exists
    if (image != NULL) {
        SDL_FreeSurface(image);
        image = NULL;
        size = 0;
    }
}

//gRenderer is the render from the window
void Square::paint(SDL_Surface* gScreenSurface) {

    SDL_Rect stretchRect;
    stretchRect.x = this->x;
    stretchRect.y = this->y;
    stretchRect.w = size - 1;
    stretchRect.h = size - 1;

    SDL_BlitScaled( image, NULL, gScreenSurface, &stretchRect );

}





/*
 * unimplemented methods whit primitive shapes
 *
 class Color{

public:
    int R, G, B;
    Color(){}
    void generateColor( ){

        srand(time(NULL));
        R = rand() % 255 ;
        G = rand() % 255 ;
        B = rand() % 255 ;
    }
};
void Square::paintSquare(Color* c){

    SDL_Rect fillRect;

    //clear the square
    SDL_SetRenderDrawColor( image, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( image );

    //paint the dark side
    fillRect = { 0, 0, size, size };
    SDL_SetRenderDrawColor( image, 71, 71, 71, 0xFF );
    SDL_RenderFillRect( image, &fillRect );

    //paint the lighted side
    fillRect = { 0,0, size * 19/20, size * 19/20 };
    SDL_SetRenderDrawColor( image, 195, 195, 195, 0xFF );
    SDL_RenderFillRect( image, &fillRect );

    //paint the center
    fillRect = { size * 1/20, size * 1/20, size * 18/20, size * 18/20 };
    SDL_SetRenderDrawColor( image, c->R, c->G, c->B, 0xFF );
    SDL_RenderFillRect( image, &fillRect );

    SDL_CreateSurfaceFromRender

}

void Square::paintRandomSquare(){

    Color *c = new Color();
    c->generateColor();

    paintSquare(c);

}

void Square::paintGraySquare(){

    Color c;
    c.R = 136;
    c.G = 136;
    c.B = 136;
    paintSquare(&c);

}
 */

