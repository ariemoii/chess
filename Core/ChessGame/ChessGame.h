#pragma once
#include "view/WindowHandler.h"
#include "controller/FENparser.h"
#include "model/Board.h"
#include "controller/MoveMaker.h"
#include "MoveGenerator.h"
#include "MoveData.h"

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