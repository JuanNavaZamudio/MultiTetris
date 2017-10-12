/*
 * File:   Board.h
 * Author: juan
 *
 * Created on 19 de septiembre de 2017, 11:23 PM
 */
#include <SDL2/SDL.h>

#include "I.h"
#include "J.h"
#include "L.h"
#include "O.h"
#include "S.h"
#include "T.h"
#include "Z.h"

#define MOVE_LEFT_BOARD -1
#define KEEP_ACTUAL_BOARD 0
#define MOVE_RIGHT_BOARD 1
#define HAS_FALLEN 2

#define SQUARES_TO_THE_WIDTH 10
#define SQUARES_TO_THE_HEIGHT 20

#ifndef BOARD_H
#define	BOARD_H

class Board {
public:

    //static const int SQUARES_TO_THE_WIDTH = 10;
    //static const int SQUARES_TO_THE_HEIGHT = 20;

    //coordinates of the board
    int x;
    int y;

    int width;
    int height;

    int squareSize;

    //in this board have the active piece
    bool haveThePiece;
    //the color of the stacked pieces in this board
    int color;
    //the screen of the main program
    SDL_Surface* gScreenSurface;
    //this square will be used to paint the gray borders of the board
    Square square;
    //this square will paint the bottom of the board to indicate his corresponding color
    Square bottom;

    //here will be stored the stacked pieces
    Square boardPieces[SQUARES_TO_THE_WIDTH][SQUARES_TO_THE_HEIGHT];

    Board();
    Board(const Board& orig);
    Board(int x, int y, int width, int height, int color, SDL_Surface* gScreenSurface);
    virtual ~Board();

    void setup();
    void clean();
    void startBoard();
    void fillBorders();
    bool stackPiece(Piece* piece);  //if return true the game has finish
    void unstackRow(int rowNum);
    void downPeceToFrom(int x1, int y1, int x2, int y2);
    void paintBoard();
    int checkRowsFilled();
    int movePiece(Piece* piece);

    bool tryToErase(int xPos, int yPos);
    bool spaceIsFree(Piece* piece);

    Piece* generatePiece();

private:

};

#endif	/* BOARD_H */

