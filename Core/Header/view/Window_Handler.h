#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "NewBoard.h"
#include "Piece_Drawer.h"

/**
 * Class that handles the window
 */
class Window_Handler {
  private:
    const int SCREEN_WIDTH;
    static constexpr int NUM_SQUARES_SIDE = 8;
    const int SCREEN_HEIGHT;
    const int PIXEL_SQUARE_WIDTH;
    Piece_Drawer pieceDrawer;
  
    public:
      sf::Event event;
    

    /**
     * constructor
     */
  public:
    Window_Handler(int screenHeight, int screenWidth);
    sf::RenderWindow window;
    bool nextEvent();
    void draw_board(NewBoard *board);
    void draw_board_background();
    
  private:
    /**
     * draw the background on the window
     */
    

    /**
     * draw a square on the board
     */
    void draw_square(bool isLightSquare, int xCoord, int yCoord);

    

};