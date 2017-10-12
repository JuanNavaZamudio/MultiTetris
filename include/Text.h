#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>


#ifndef TEXT_H
#define TEXT_H


class Text
{
    public:

        int x;
        int y;
        int width;
        int height;
        int fontSize;
        std::string text;

        SDL_Color textColor;
        TTF_Font* gFont = NULL;
        SDL_Surface* textSurface; //the image to render

        bool loadFromRenderedText();
        bool loadMedia();

        void paint(SDL_Surface* gScreenSurface);
        void setText(std::string text);


        void init();
        void free();
        Text();
        Text(int x,int y, int fontSize, std::string text);
        virtual ~Text();

    protected:

    private:
};

#endif // TEXT_H
