#pragma once

#include "model/Move.h"
#include "model/Board.h"
#include "MoveData.h"
#include <vector>

class MoveGenerator {
  public:

  private:

  public:
    MoveGenerator();
    std::vector<Move> generatePeudolegalMoves(Board* board, int startSquare);

  private:
    std::vector<Move> generateSlidingPieceMoves(int startSquare, Piece::PieceType type, Board* board);

};