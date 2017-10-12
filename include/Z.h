/*
 * File:   Z.h
 * Author: juan
 *
 * Created on 19 de septiembre de 2017, 11:28 PM
 */
#include <SDL2/SDL.h>

#include "Piece.h"

#ifndef Z_H
#define	Z_H

class Z:public Piece {
public:

    SDL_Texture* paintShape();

    void setState0();
    void setState1();
    void setState2();
    void setState3();

    Z();
    Z(const Z& orig);
    Z(int x, int y, int squareSize, int color, SDL_Surface* gScreenSurface);
    virtual ~Z();
private:

};

#endif	/* Z_H */

