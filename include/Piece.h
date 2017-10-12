/*
 * File:   Piece.h
 * Author: juan
 *
 * Created on 19 de septiembre de 2017, 11:28 PM
 */
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>

#include "Square.h"


#ifndef PIECE_H
#define	PIECE_H

class Piece {
public:

    int x;
    int y;

    int VEL = 2;
    //the time in cycles by second when holding the direction of displacement, the piece will move fast
    int CICLES_TO_HOLD_BUTTON = 30;

    int actVelX = 0;
    int actVelY = VEL;

    int repMov = CICLES_TO_HOLD_BUTTON;

    int squareSize = 0;
    SDL_Surface* gScreenSurface;

    int color;
    Square shape[4];
    void paint();

    //flag to indicate when stop the mov in the x axis
    bool moving;

    //the state number will indicate the rotated position
    int state = 0;
    int maxStates;

    Piece();
    Piece(const Piece& orig);
    Piece(int x, int y, int squareSize, int color, SDL_Surface* gScreenSurface);
    virtual ~Piece();

    bool ckeckIfHasFallen(Square boardPieces[10][20]);
    bool isCollidingToTheLeft(Square boardPieces[10][20]);
    bool isCollidingToTheRight(Square boardPieces[10][20]);

    void handleMovement( SDL_Event& e );
    void handleVelocityAndSpin( SDL_Event& e );
    void spinClock();
    void spinAntiClock();
    void updatePos();
    int calculateWidth();
    int calculateHeight();

    void setTexture(SDL_Surface* image);

    //this states will arrange the squares for
    virtual void setState0(){};
    virtual void setState1(){};
    virtual void setState2(){};
    virtual void setState3(){};


    //all this functions return the coordinates for each location
    int topLeftX();
    int topLeftY();
    int topCenterX();
    int topCenterY();
    int topRightX();
    int topRightY();

    int top2RightX();
    int top2RightY();

    int midLeftX();
    int midLeftY();
    int midCenterX();
    int midCenterY();
    int midRightX();
    int midRightY();

    int botLeftX();
    int botLeftY();
    int botCenterX();
    int botCenterY();
    int botRightX();
    int botRightY();

    int bot2LeftX();
    int bot2LeftY();
private:

};

#endif	/* PIECE_H */

