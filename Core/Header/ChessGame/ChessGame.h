#pragma once
#include "WindowHandler.h"
#include "FENparser.h"
#include "Board.h"
#include "MoveMaker.h"

class ChessGame {
  


  public:
    ChessGame();
    void runChess();

    private:
    //render board
    void renderAll(WindowHandler* windowHandler, Board* board);
};