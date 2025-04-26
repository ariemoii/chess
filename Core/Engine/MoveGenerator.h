#pragma once

#include "model/Move.h"
#include "model/Board.h"
#include "MoveData.h"
#include <vector>

class MoveGenerator {
  public:

  private:
    MoveData moveData;

  public:
    MoveGenerator();
    std::vector<Move> generatePseudolegalMoves(Board* board, int startSquare);

  private:
    std::vector<Move> generateSlidingPieceMoves(int startSquare, Piece::PieceType type, Board* board);

};