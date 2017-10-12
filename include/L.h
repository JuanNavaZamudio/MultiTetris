/*
 * File:   L.h
 * Author: juan
 *
 * Created on 19 de septiembre de 2017, 11:28 PM
 */
#include <SDL2/SDL.h>

#include "Piece.h"

#ifndef L_H
#define	L_H

class L:public Piece {
public:


    SDL_Texture* paintShape();

    void setState0();
    void setState1();
    void setState2();
    void setState3();


    L();
    L(const L& orig);
    L(int x, int y, int squareSize, int color, SDL_Surface* gScreenSurface);
    virtual ~L();
private:

};

#endif	/* L_H */

