/*
 * File:   I.h
 * Author: juan
 *
 * Created on 19 de septiembre de 2017, 11:29 PM
 */
#include <SDL2/SDL.h>

#include "Piece.h"

#ifndef I_H
#define	I_H

class I:public Piece {
public:


    SDL_Texture* paintShape();

    void setState0();
    void setState1();
    void setState2();
    void setState3();

    I();
    I(const I& orig);
    I(int x, int y, int squareSize, int color, SDL_Surface* gScreenSurface);
    virtual ~I();
private:

};

#endif	/* I_H */

