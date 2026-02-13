#pragma once

#include "model/Move.h"
#include "model/Piece.h"
#include "model/Board.h"
#include "MoveData.h"

#include <vector>

class PseudoLegalMoveGenerator {
  public:

  private:
    MoveData moveData;

  public:
    PseudoLegalMoveGenerator();
    void generatePseudolegalMoves(Board* board, std::vector<Move>& pseudoLegalMoves);

  private:
    void generateSlidingPieceMoves(int startSquare, Piece::PieceType type, Board* board, std::vector<Move>& moveVector);
    void generateKnightMoves(int startSquare, Board* board, std::vector<Move>& moveVector);
    void generateKingMoves(int startSquare, Board* board, std::vector<Move>& moveVector);
    void generatePawnMoves(int startSquare, Board* board, std::vector<Move>& moveVector);
    void generatePromotionMoves(std::vector<Move>& moveVector, Move move);
    bool isLegalCapture(Move move, Board* board);
};