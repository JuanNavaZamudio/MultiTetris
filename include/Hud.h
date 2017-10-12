#include <SDL2/SDL.h>

#include "Button.h"
#include "InstructionsButton.h"
#include "Text.h"
#include "Piece.h"

#ifndef HUD_H
#define HUD_H


class Hud
{
    public:

        int x;
        int y;
        int width;
        int height;

        InstructionsButton* instructionsButton; //button of instructions
        Text* scoreText;     //score word
        Text* scoreNumber;   //score in number
        Text* squaresToErase;
        SDL_Surface* gScreenSurface;
        Piece* nextPiece;

        void paint();
        void updateInformation(int score, int freeSquares, Piece* nextPiece);

        Hud();
        Hud(int x, int y, int width, int height,std::string scoreText,std::string textButton, SDL_Surface* screenSurface);
        virtual ~Hud();

    protected:

    private:
};

#endif // HUD_H
