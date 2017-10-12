/*close, init and methods are from the Lazy Foo' tutorial
 * http://www.lazyfoo.net/tutorials/SDL
 *
 * main take some parts
 */

//Using SDL, standard IO, and strings
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>


#include "Hud.h"
#include "Board.h"

//Screen dimension constants
const int SCREEN_WIDTH = 720; //720
const int SCREEN_HEIGHT = 600; //600
//boards of the game
static const int TOT_BOARDS = 3;
//heigth of the hud in squares
const int SQUARES_HUD_HEIGHT = 6;
//points given per row completed
const int POINTS_PER_ROW = 100;

const std::string INSTRUCTIONS_BUTTON_TEXT = "Instructions";
const std::string START_BUTTON_TEXT = "Start";
const std::string SCORE_TEXT = "Score ";

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

//loads the board and the colors for each one
bool loadComponents();
//use a random function to pick one color
void generateColors();
//update the image of all the boards created
void updateScreen();
//asign the loaded textures to the generated pieces
void setPieceTexture(Piece* piece);

//prepare a new piece to let fall
void generateNewPiece();

//change the position of the actual piece
//to the left
void changeToLeftBoard();
//to the right
void changeToRightBoard();

//control of the gameplay
bool startGame();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface;

//adapt the images to the screen surface
//SDL_surface* optimizeSurface(SDL_surface* loadedSurface);

//each square contains the color and image to paint the next figures
//and save the register of the asigned color in each board

Square squareType1;
Square squareType2;
Square squareType3;

//this square will paint the borders
Square graySquare;

//information bar with score, next piece and instructions button
Hud* hud = NULL;

//the boards of the screen
Board* boards[TOT_BOARDS];

//the board who has the active piece
int focusedBoard = TOT_BOARDS / 2;

//the middle board
int middleBoard = TOT_BOARDS / 2;

//the sum of points in the actual game
int totPoints;
//the gained points
int points;
//the number of squares to erase clicking
int squaresToErase;

//the flag for start or stop the current game
bool gameOver;

//the piece to move
Piece* actualPiece = NULL;
//the waiting piece
Piece* nextPiece = NULL;

//count the time to stack the piece once that fell
int timer;

//Event handler
SDL_Event e;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "MultiTetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface( gWindow );
		}

	}

	return success;
}

void close() {

    //free the window surface
    SDL_FreeSurface( gScreenSurface );
    gScreenSurface = NULL;

    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}
/*
SDL_surface* optimizeSurface(SDL_surface* loadedSurface) {

    //Convert surface to screen format
        loadedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, NULL );
		if( loadedSurface == NULL )
		{
			printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

    retun loadedSurface;
}
*/
bool loadComponents() {

    bool success = true;

    generateColors();

    //calculate the dimensions for all the boards
    int board_width = SCREEN_WIDTH * (SQUARES_TO_THE_WIDTH + 2) / ( (SQUARES_TO_THE_WIDTH + 2) * TOT_BOARDS);
    int board_height = SCREEN_HEIGHT * (SQUARES_TO_THE_HEIGHT + 2) / (SQUARES_TO_THE_HEIGHT + 2 + SQUARES_HUD_HEIGHT);
    int hud_heigth = SCREEN_HEIGHT * SQUARES_HUD_HEIGHT / (SQUARES_TO_THE_HEIGHT + 2 + SQUARES_HUD_HEIGHT);


    hud = new Hud(0, 0, SCREEN_WIDTH, hud_heigth, SCORE_TEXT, INSTRUCTIONS_BUTTON_TEXT, gScreenSurface);


    printf("creating boards...\n");
    boards[0] = new  Board(
            0 * board_width, //coordinate x
            hud_heigth, //coordinate y
            board_width, //width
            board_height, //heigth
            squareType1.color,
            gScreenSurface
        );

    boards[1] = new  Board(
            1 * board_width, //coordinate x
            hud_heigth, //coordinate y
            board_width, //width
            board_height, //heigth
            squareType2.color,
            gScreenSurface
        );

    boards[2] = new Board(
            2 * board_width, //coordinate x
            hud_heigth, //coordinate y
            board_width, //width
            board_height, //heigth
            squareType3.color,
            gScreenSurface
            );
    for(int i = 0; i < TOT_BOARDS; i++)
        boards[i]->setup();

    generateNewPiece();

    printf("painting the game board...\n");
    updateScreen();

    return success;
}
/*generate a piece and put his texture
* restart the timer for wait a second after the
* piece fall
*/
void generateNewPiece(){

    //printf("generating piece...\n");
    if(nextPiece == NULL)
        nextPiece = boards[middleBoard]->generatePiece();

    actualPiece = nextPiece;
    nextPiece = boards[middleBoard]->generatePiece();

    //put the actual piece just above the board
    actualPiece->y = actualPiece->y - actualPiece->calculateHeight();
    actualPiece->updatePos();

    setPieceTexture(actualPiece);
    setPieceTexture(nextPiece);

    focusedBoard = TOT_BOARDS/2;
    timer = 60;
}

/*put the image on the generated piece
* from the preloaded colors
*/
void setPieceTexture(Piece* piece){

    if(piece->color == squareType1.color){
        printf("color %d\n",squareType1.color);
        piece->setTexture(squareType1.image);
    }
    if(piece->color == squareType2.color){
        piece->setTexture(squareType2.image);
        printf("color %d\n",squareType2.color);
    }
    if(piece->color == squareType3.color){
        piece->setTexture(squareType3.image);
        printf("color %d\n",squareType3.color);
    }
}

//an ungly version for pick diferent colors :/
void generateColors(){

    printf("generating colors\n");
    squareType1.selectRandom();
    squareType2.selectRandom();
    squareType3.selectRandom();

    while(squareType1.color == squareType2.color)
        squareType2.selectRandom();

    printf("first and second ready\n");

    while(squareType1.color == squareType3.color || squareType2.color == squareType3.color)
        squareType3.selectRandom();

    printf("colors generated\n");
}

void updateScreen() {
    //update hud status
    hud->updateInformation(totPoints, squaresToErase, nextPiece);
    hud->paint();
    //update the image of the falling piece
    if(actualPiece->x >= boards[0]->x && actualPiece->y >= boards[0]->y &&
       actualPiece->x + actualPiece->calculateWidth()
       <=
       boards[TOT_BOARDS - 1]->x + boards[TOT_BOARDS - 1]->width &&
       actualPiece->y + actualPiece->calculateHeight()
       <=
       boards[TOT_BOARDS - 1]->y + boards[TOT_BOARDS - 1]->height)
        actualPiece->paint();
    //update the images of the boards and his stacked pieces
    for (int i = 0; i < TOT_BOARDS; i++) {
        boards[i]->paintBoard();
    }
}
/*moved can be -1, 0 or 1
* the piece will moved to the left, stay in the same or right board respectibly
 */
void moveBetweenBoards(int moved) {
    //printf("updating actual board ._.\n");
    if (moved == MOVE_LEFT_BOARD){
        //move the figure to the left board if isn't the most left
        if (focusedBoard > 0) {

            changeToLeftBoard();
            if( !boards[focusedBoard]->spaceIsFree(actualPiece)){
                changeToRightBoard();
            }

            actualPiece->moving = false;

        }
    }
    if (moved == MOVE_RIGHT_BOARD)
        //move the figure to the right board if isn't the most right
        if (focusedBoard < TOT_BOARDS -1 ) {

            changeToRightBoard();
            if( !boards[focusedBoard]->spaceIsFree(actualPiece)){
                changeToLeftBoard();
            }

            actualPiece->moving = false;

        }
        //printf("actual board: %d\n",focusedBoard);
}

void changeToLeftBoard(){
    focusedBoard--;
    actualPiece->x = boards[focusedBoard]->x + boards[focusedBoard]->width - actualPiece->squareSize - actualPiece->calculateWidth();
}

void changeToRightBoard(){
    focusedBoard++;
    actualPiece->x = boards[focusedBoard]->x + actualPiece->squareSize;
}

void cleanOneSquare(SDL_Event& e){
    //Get mouse position int x, y; SDL_GetMouseState( &x, &y );
    if( e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP ) {
        if(squaresToErase > 0){

            //Get mouse position
            bool removed = false;
            int x, y;
            SDL_GetMouseState( &x, &y );

            for(int i = 0; i < TOT_BOARDS; i++){
                removed = boards[i]->tryToErase(x,y);
                if(removed)
                    i = TOT_BOARDS;
            }
            if(removed){
                squaresToErase--;
                printf("squares %d\n",squaresToErase);
            }
        }
    }
}

void cleanGame(){
    gameOver = false;
    totPoints = 0;
    points = 0;
    squaresToErase = 0;

    for(int i = 0; i < TOT_BOARDS ; i++)
        boards[i]->clean();
}

bool startGame(){


    //if the falling piece has collided
    bool falled;
    //indicates the direction of the focused board
    int moved = 0;

    while(!gameOver){

        //Handle events on queue
        while(SDL_PollEvent(&e) != 0) {
            //User requests quit
            if (e.type == SDL_QUIT) {
                return true;
            }
            else
                if(e.type == SDL_MOUSEBUTTONDOWN)
                    cleanOneSquare(e);
            else
                if(!falled){
                    //If a key was pressed wiil do something of the actions
                    //change state, fall faster,
                    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym==SDLK_UP){
                        actualPiece->spinAntiClock();
                        if(!boards[focusedBoard]->spaceIsFree(actualPiece))
                            actualPiece->spinClock();
                    }

                }

                //actualPiece->handleVelocityAndSpin(e);
                //we can move the piece once it fell
                actualPiece->handleMovement(e);


        }

        moved = boards[focusedBoard]->movePiece(actualPiece);

        //update the num of the board with the falling piece
        moveBetweenBoards(moved);

        actualPiece->updatePos();

        falled = actualPiece->ckeckIfHasFallen( boards[focusedBoard]->boardPieces );

        if (falled) {
            timer--;
            if(timer == 0 ){

            gameOver = boards[focusedBoard]->stackPiece(actualPiece);
            points = boards[focusedBoard]->checkRowsFilled();

            totPoints += points;
            squaresToErase += points / POINTS_PER_ROW;

            generateNewPiece();
            }
        }
        if(gameOver)
            printf("Game over\n");

        //update the boards' image
        updateScreen();


        //Update the surface
        SDL_UpdateWindowSurface(gWindow);

        //clean the screen before paint it again in the next cycle
        SDL_FillRect(gScreenSurface, NULL, 0x000000);

        //Wait 1/60 of second
        SDL_Delay( 1000 / 60 );
    }
    return false;
}


int main(int argc, char* args[]) {
    //Start up SDL and create window
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        //Load the components of the game
        if (!loadComponents()) {
            printf("Failed to load media!\n");
        } else {

            //Main loop flag
            bool quit = false;

            //While application is running
            while (!quit) {
                cleanGame();
                quit = startGame();
            }

        }
    }

    //Free resources and close SDL
    close();

    return 0;
}

