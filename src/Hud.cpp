#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <sstream>

#include "Hud.h"

Hud::Hud()
{
    //ctor
}

Hud::Hud(int x, int y, int width, int height,std::string scoreText,std::string textButton, SDL_Surface* screenSurface)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->gScreenSurface = screenSurface;
    this->scoreText = new Text(20,30,36,scoreText);

    std::string initNumber = "0";

    this->scoreNumber = new Text(this->scoreText->x + this->scoreText->textSurface->w + 5, 30, //x and y
                                 36,initNumber.c_str());

    std::string squares = "Squares to erase";
    this->squaresToErase = new Text(20,70,20,squares);

    this->instructionsButton = new InstructionsButton(width - 300, 30 , 12 * 20, 4 * 20, textButton, 36);
}

Hud::~Hud()
{
    //dtor
}

void Hud::updateInformation(int score,int freeSquares, Piece* nextPiece){

    std::ostringstream tempText;
    std::ostringstream tempSqrs;

    tempText << score ;
    this->scoreNumber->setText(tempText.str());
    this->scoreNumber->loadFromRenderedText();

    tempSqrs << "Squares to erase " << freeSquares;
    this->squaresToErase->setText(tempSqrs.str());
    this->squaresToErase->loadFromRenderedText();

    this->nextPiece = nextPiece;
    this->nextPiece->x = this->width / 2;
    this->nextPiece->y = y + height * 1/6;
    this->nextPiece->updatePos();
}

void Hud::paint(){

    this->scoreText->paint(this->gScreenSurface);
    this->scoreNumber->paint(this->gScreenSurface);
    this->squaresToErase->paint(this->gScreenSurface);
    this->nextPiece->paint();
    this->instructionsButton->text->paint(this->gScreenSurface);
}
