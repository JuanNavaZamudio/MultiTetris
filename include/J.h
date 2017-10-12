/*
 * File:   J.h
 * Author: juan
 *
 * Created on 19 de septiembre de 2017, 11:28 PM
 */
#include <SDL2/SDL.h>

#include "Piece.h"

#ifndef J_H
#define	J_H

class J:public Piece {
public:


    SDL_Texture* paintShape();

    void setState0();
    void setState1();
    void setState2();
    void setState3();

    J();
    J(const J& orig);
    J(int x, int y, int squareSize, int color, SDL_Surface* gScreenSurface);
    virtual ~J();
private:

};

#endif	/* J_H */

