#pragma once

#include "AllPieces.h"

#include <array>
#include <memory>

#define BOARDTYPE std::array<std::array<std::unique_ptr<Piece>, 8>, 8>

class Board {
  private:

  public:
    Board();
    BOARDTYPE theBoard;
    void addPiece(std::unique_ptr<Piece> piece);
    void printBoard();
    void initBoard();
};

