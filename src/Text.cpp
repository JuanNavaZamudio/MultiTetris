#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>

#include "Text.h"

Text::Text()
{
    init();
}

Text::Text(int x,int y, int fontSize, std::string text)
{
    printf("text building.. %d %d, %d %s.\n",x,y,fontSize,text.c_str());

    this->x = x;
    this->y = y;
    this-> fontSize = fontSize;

    init();
    this->textColor = {255, 255, 255};

    this->text = text;
    //this->width = text.size() * 20;
    //this->height = fontSize * 2;

    if( !loadFromRenderedText() )
        printf( "Failed to render text texture!\n" );
}

void Text::init(){

    //Initialize SDL_ttf
    if( TTF_Init() == -1 ){
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
    }else
        if(loadMedia())
            printf("font successful charged! \n");
}

Text::~Text()
{
    free();
}

bool Text::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Open the font
	this->gFont = TTF_OpenFont( "font/arcadeclassic.ttf", this->fontSize );
	if( gFont == NULL )
	{
		printf( "Failed to load arcade font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
	    printf("true type loaded! \n");
		//Render text
		/*if( !loadFromRenderedText() )
		{
			printf( "Failed to render text texture!\n" );
			success = false;
		}*/
	}

	return success;
}


bool Text::loadFromRenderedText(){

	//Render text surface
	textSurface = TTF_RenderText_Solid( this->gFont, this->text.c_str(), this->textColor );
	if( textSurface == NULL )
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	//Return success
	return textSurface != NULL;
}

void Text::free()
{
	//Free texture if it exists
	if( textSurface != NULL )
	{
		SDL_FreeSurface(textSurface);
		printf("llega\n");
	}
}

void Text::paint(SDL_Surface* gScreenSurface){

    SDL_Rect stretchRect;
    stretchRect.x = this->x;
    stretchRect.y = this->y;
    stretchRect.w = this->textSurface->w;
    stretchRect.h = this->textSurface->h;

    SDL_BlitScaled( this->textSurface, NULL, gScreenSurface, &stretchRect );


}

void Text::setText(std::string text){
    this->text = text;
}
