/*
 * File:   O.h
 * Author: juan
 *
 * Created on 19 de septiembre de 2017, 11:29 PM
 */
#include <SDL2/SDL.h>

#include "Piece.h"

#ifndef O_H
#define	O_H

class O:public Piece {
public:


    SDL_Texture* paintShape();

    void setState0();
    void setState1();
    void setState2();
    void setState3();

    O();
    O(const O& orig);
    O(int x, int y, int squareSize, int color, SDL_Surface* gScreenSurface);
    virtual ~O();
private:

};

#endif	/* O_H */

