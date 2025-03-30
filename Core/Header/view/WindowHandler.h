#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Board.h"
#include "PieceDrawer.h"
#include "Move.h"

/**
 * Class that handles the window
 */
class WindowHandler {
  private:
    const int SCREEN_WIDTH;
    static constexpr int NUM_SQUARES_SIDE = 8;
    const int SCREEN_HEIGHT;
    const int PIXEL_SQUARE_WIDTH;
    PieceDrawer pieceDrawer;
  
    public:
    

    /**
     * constructor
     */
  public:
    WindowHandler(int screenHeight, int screenWidth);

    int getPixelSquareWidth() { return PIXEL_SQUARE_WIDTH; };

    sf::RenderWindow window;
    void drawBoard(Board *board, Piece::Team bottomTeam);
    void drawBoardBackground();
    Move getMove(int squarePressed);
    int whatSquare(int xCoord, int yCoord);

  private:
    /**
     * draw a square on the board
     */
    void drawSquare(bool isLightSquare, int xCoord, int yCoord);

    

};