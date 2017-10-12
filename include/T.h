/*
 * File:   T.h
 * Author: juan
 *
 * Created on 19 de septiembre de 2017, 11:28 PM
 */
#include <SDL2/SDL.h>

#include "Piece.h"

#ifndef T_H
#define	T_H

class T:public Piece {
public:


    SDL_Texture* paintShape();

    void setState0();
    void setState1();
    void setState2();
    void setState3();

    T();
    T(const T& orig);
    T(int x, int y, int squareSize, int color, SDL_Surface* gScreenSurface);
    virtual ~T();
private:

};

#endif	/* T_H */

