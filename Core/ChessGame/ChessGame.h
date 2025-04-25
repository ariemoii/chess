#pragma once
#include "view/WindowHandler.h"
#include "controller/FENparser.h"
#include "model/Board.h"
#include "controller/MoveMaker.h"

class ChessGame {
  


  public:
    ChessGame();
    void runChess();

    private:
    //render board
    void renderAll(WindowHandler* windowHandler, Board* board);
};