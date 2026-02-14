#pragma once
#include "view/WindowHandler.h"
#include "model/Board.h"
#include "view/WindowHandler.h"
#include "MoveGenerator.h"

constexpr unsigned int SCREEN_HEIGHT = 800;
constexpr unsigned int SCREEN_WIDTH = 800;

class ChessGame {
  
  public:
    ChessGame();
    virtual void runChess() = 0;

    protected:
      //render board
      void renderAll(WindowHandler* windowHandler, Board* board);
      void printCheckMate(Board &theBoard);

    protected:
      Board board;
      WindowHandler windowHandler;
      MoveGenerator moveGenerator;

    private:
      Board initBoard();
};