#pragma once
#include "view/WindowHandler.h"
#include "model/Board.h"

constexpr unsigned int SCREEN_HEIGHT = 800;
constexpr unsigned int SCREEN_WIDTH = 800;

class ChessGame {
  


  public:
    ChessGame();
    virtual void runChess() = 0;

    protected:
      //render board
      void renderAll(WindowHandler* windowHandler, Board* board);
};