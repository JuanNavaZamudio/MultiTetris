/*
 * File:   Board.cpp
 * Author: juan
 *
 * Created on 19 de septiembre de 2017, 11:23 PM
 */
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <random>
#include <time.h>

#include "Board.h"

enum {PIECE_O,PIECE_L,PIECE_J,PIECE_T,PIECE_S,PIECE_Z,PIECE_I};

Board::Board() {
}

Board::Board(const Board& orig) {
}

Board::~Board() {
}

//constructor receives the width, height, color and surface to paint the board
Board::Board(int x, int y, int width, int height, int color, SDL_Surface* gScreenSurface) {

    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->color = color;
    this->gScreenSurface = gScreenSurface;

    this->squareSize = width / (SQUARES_TO_THE_WIDTH + 2) ;

    //initialize the random numbers
    srand(time(NULL));

    //printf("Board created in %d,%d w,h %d,%d col %d size%d\n",
    //       this->x,this->y,this->width,this->height,this->color,this->squareSize);
}

void Board::setup() {

    square = Square(this->x,this->y,this->squareSize,NULL);
    bottom = Square(this->x,this->y,this->squareSize,NULL);

    square.selectGray();
    bottom.selectFromColor(color);

    fillBorders();

    //pointers for the coordinates x,y to initialize each square
    int actX = this->x + squareSize;
    int actY = this->y + squareSize;

    //initialize the game board
    for(int i = 0; i < SQUARES_TO_THE_HEIGHT; i++){
        for(int j = 0; j < SQUARES_TO_THE_WIDTH; j++){
            boardPieces[j][i] = Square(actX,actY,squareSize,NULL);
            //pieces[j][i].selectRandom();
            actX += squareSize;
        }
        actX = this->x + squareSize;
        actY += squareSize;
    }

}

void Board::clean(){
    for(int i = 0; i < SQUARES_TO_THE_HEIGHT; i++){
        for(int j = 0; j < SQUARES_TO_THE_WIDTH; j++){
            boardPieces[j][i].color = -1;
            boardPieces[j][i].image = NULL;
        }
    }
}

/*if the method returns
 * -1 the piece will be moved to the left board
 * 0 the piece remains in the actual board
 * 1 the piece moves to the rigth board
 */
int Board::movePiece(Piece* piece) {

    //move to collision
    if(!piece->ckeckIfHasFallen(this->boardPieces) )
        piece->y += piece->actVelY;
    else
        piece->y -= piece->actVelY;

    //board
    int sigBoard = KEEP_ACTUAL_BOARD;
    if(piece->moving || piece->repMov < 1 ){ //when the button is hold, a counter will be descending

        int leftBorder = this->boardPieces[0][0].x;
        int rightBorder = (boardPieces[9][0].x + boardPieces[9][0].size);
        int sigPos = piece->x + piece->actVelX;


        // if the piece will not exit from the borders of the board
        //move the piece and indicate if the piece will change of board
        //actVel < 0 left, actVel > 0 right
        if((( piece->actVelX < 0 && sigPos >= leftBorder ) &&
             !piece->isCollidingToTheLeft(this->boardPieces))
           ||
            ( piece->actVelX > 0 && sigPos + piece->calculateWidth() <= rightBorder &&
             !piece->isCollidingToTheRight(this->boardPieces))
            ){

            piece->x = sigPos;

            piece->moving = false;
            sigBoard = KEEP_ACTUAL_BOARD;
        }
        if ( sigPos < leftBorder) {
                sigBoard = MOVE_LEFT_BOARD;
        }
        if ((piece->x + piece->actVelX + piece->calculateWidth()) > rightBorder) {
                sigBoard = MOVE_RIGHT_BOARD;
            }
    }
    return sigBoard;
}

void Board::fillBorders() {

    square.x = this->x;
    square.y = this->y;

    //printf("painting borders.. actual square: \n");
    for (int i = 0; i < SQUARES_TO_THE_WIDTH + 1; i++) {
        square.paint(gScreenSurface);
        square.x += (square.size);
    }

    for (int i = 0; i < SQUARES_TO_THE_HEIGHT + 2; i++) {
        square.paint(gScreenSurface);
        square.y += square.size;
    }
    //paint the bottom from the corresponding color of pieces
    square.y -=square.size;
    square.x -=square.size;

    bottom.x = square.x;
    bottom.y = square.y;

    for (int i = SQUARES_TO_THE_WIDTH; i > 0 ; i--) {
        bottom.paint(gScreenSurface);
        bottom.x -= (bottom.size);
    }
    square.x = bottom.x;
    square.y = bottom.y;
    for (int i = SQUARES_TO_THE_HEIGHT + 2; i > 0 ; i--) {
        square.paint(gScreenSurface);
        square.y -= (square.size);
    }
}

//stacks the pieces square by square in the board matrix
// each square is in pos = x + squareX * (size)
// so the number of square putted in this board is a multiple of the size
// numInX = (Xcoord - xOfTheBoard) / (size+1)

bool Board::stackPiece(Piece* piece) {

    int posX, posY;

    for (int i = 0; i < 4; i++) {

        posX = (piece->shape[i].x - this->x) / (piece->shape[i].size) - 1;
        posY = (piece->shape[i].y - this->y) / (piece->shape[i].size) - 1;

        //printf("stacking in %d,%d\n",posX,posY);
        if(!(posY < 0)){
            boardPieces[posX][posY].image = piece->shape[i].image;
            boardPieces[posX][posY].color = piece->shape[i].color;
        }else
            return true;
    }
    return false;
}
//this will be ckecking each row, if all the elements are
//from the same color as the board
//return the points gained
int Board::checkRowsFilled() {
    bool rowFilled;
    int numRow;
    int newPoints = 0;

    for (int i = 0; i < SQUARES_TO_THE_HEIGHT; i++) {
        rowFilled = false;
        for (int j = 0; j < SQUARES_TO_THE_WIDTH; j++) {
                //if(boardPieces[j][i].image != NULL)
                //printf("has image and color %d board: %d \n",boardPieces[j][i].color,this->color);
            if ( boardPieces[j][i].image != NULL && boardPieces[j][i].color == color) {
                rowFilled = true;
                numRow = i;
            } else{
                j = SQUARES_TO_THE_WIDTH;
                rowFilled = false;
            }
        }
        if (rowFilled){
            printf("row %d filled!!!!!!! ~( ._.)~\n",numRow);
            unstackRow(numRow);
            newPoints += 100;
        }
    }
    return newPoints;
}

//erase the row indicated
void Board::unstackRow(int rowNum){
    for(int j = 0; j < SQUARES_TO_THE_WIDTH; j++) //x coordinate
        for(int i = rowNum; i > 0; i--){    //Y coordinate
            downPeceToFrom(j,i,j,i-1);
        }
}

void Board::downPeceToFrom(int x1, int y1, int x2, int y2){
    boardPieces[x1][y1].color = boardPieces[x2][y2].color;
    boardPieces[x1][y1].image = boardPieces[x2][y2].image;

    boardPieces[x2][y2].color = -1;
    boardPieces[x2][y2].image = NULL;
}

bool Board::tryToErase(int xPos, int yPos){

    int coordX = (xPos - this->x) / squareSize - 1;
    int coordY = (yPos - this->y) / squareSize - 1;

    if(coordX < SQUARES_TO_THE_WIDTH && coordX >= 0
        && coordY < SQUARES_TO_THE_HEIGHT && coordY >= 0)
    {
        boardPieces[coordX][coordY].color = -1;
        boardPieces[coordX][coordY].image = NULL;
        return true;
    }else
        return false;
}

bool Board::spaceIsFree(Piece* piece){

    piece->updatePos();

    bool isAllFree;

    for(int  i = 0; i < 4; i++){
        int coordX = (piece->shape[i].x - this->x) / squareSize - 1;
        int coordY = (piece->shape[i].y - this->y) / squareSize - 1;

        //printf("piece: %d %d coords %d %d \n",piece->x,piece->y,coordX,coordY);

        if(boardPieces[coordX][coordY].image == NULL
        && boardPieces[coordX][coordY].color == -1){
            isAllFree = true;
        }else{
            isAllFree = false;
            i = 4;
        }
    }
    return isAllFree;
}

void Board::paintBoard() {

    fillBorders();

    for (int i = 0; i < SQUARES_TO_THE_HEIGHT; i++) {
        for (int j = 0; j < SQUARES_TO_THE_WIDTH; j++) {
            boardPieces[j][i].paint(gScreenSurface);
        }
    }

}

Piece* Board::generatePiece(){

    int sel = rand() % 7;

    int pieceColor = rand() % 3;
    int posX = this->x + (SQUARES_TO_THE_WIDTH / 2 * squareSize);
    int posY = this->y - squareSize * 5;

    switch(sel){
        case PIECE_O: return new O(posX, posY, squareSize, pieceColor, gScreenSurface);
        case PIECE_L: return new L(posX, posY, squareSize, pieceColor, gScreenSurface);
        case PIECE_J: return new J(posX, posY, squareSize, pieceColor, gScreenSurface);
        case PIECE_T: return new T(posX, posY, squareSize, pieceColor, gScreenSurface);
        case PIECE_S: return new S(posX, posY, squareSize, pieceColor, gScreenSurface);
        case PIECE_Z: return new Z(posX, posY, squareSize, pieceColor, gScreenSurface);
        case PIECE_I: return new I(posX, posY, squareSize, pieceColor, gScreenSurface);
        default: return new O(posX,posY,squareSize,pieceColor,gScreenSurface);
    }
    //by default will be a perfect game with squares
}

