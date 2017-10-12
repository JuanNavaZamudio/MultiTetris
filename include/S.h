/*
 * File:   S.h
 * Author: juan
 *
 * Created on 19 de septiembre de 2017, 11:28 PM
 */
#include <SDL2/SDL.h>

#include "Piece.h"

#ifndef S_H
#define	S_H

class S :public Piece{
public:


    SDL_Texture* paintShape();

    void setState0();
    void setState1();
    void setState2();
    void setState3();

    S();
    S(const S& orig);
    S(int x, int y, int squareSize, int color, SDL_Surface* gScreenSurface);
    virtual ~S();
private:

};

#endif	/* S_H */

