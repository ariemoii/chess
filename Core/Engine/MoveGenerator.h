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
    std::vector<Move> generatePseudolegalMoves(Board* board);

  private:
    void generateSlidingPieceMoves(int startSquare, Piece::PieceType type, Board* board, std::vector<Move>& moveVector);
    void generateKnightMoves(int startSquare, Board* board, std::vector<Move>& moveVector);
    void generateKingMoves(int startSquare, Board* board, std::vector<Move>& moveVector);
    void generatePawnMoves(int startSquare, Board* board, std::vector<Move>& moveVector);
    bool isLegalCapture(Move move, Board* board);

};