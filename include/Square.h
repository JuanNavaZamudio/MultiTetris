/*
 * File:   Square.h
 * Author: juan
 *
 * Created on 19 de septiembre de 2017, 11:28 PM
 */
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>

#ifndef SQUARE_H
#define	SQUARE_H

class Square {
public:

    int x;
    int y;
    int size;
    int color;
    SDL_Surface* image = NULL; //the image to put in the renderer

    Square();
    Square(const Square& orig);
    Square(int x, int y, int size, SDL_Surface* image);
    virtual ~Square();

    void selectRandom();
    void selectGray();
    void selectFromColor(int col);
    bool loadFromFile(std::string path);
    void paint(SDL_Surface* gScreenSurface);
    void free();

    //test colors
    void selectGreen();
    void selectRed();

private:

};

#endif	/* SQUARE_H */

