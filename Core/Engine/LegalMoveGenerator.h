#pragma once

#include "model/Move.h"
#include "model/Piece.h"
#include "model/Board.h"
#include "MoveData.h"

#include <vector>
#include <array>

class LegalMoveGenerator {
  public:

  private:
    MoveData moveData;

  public:
    LegalMoveGenerator();
    void generateLegalMoves(Board* board, std::vector<Move>& legalMoves);

  private:
    void generateSlidingPieceMoves(int startSquare, Piece::PieceType type, Board* board, std::vector<Move>& moveVector);
    void generateKnightMoves(int startSquare, Board* board, std::vector<Move>& moveVector);
    void generateKingMoves(int startSquare, Board* board, std::vector<Move>& moveVector);
    void generatePawnMoves(int startSquare, Board* board, std::vector<Move>& moveVector);
    void generatePromotionMoves(std::vector<Move>& moveVector, Move move);
    bool isLegalCapture(Move move, Board* board);
    void calculateAttackData(Board* board);
    void calculateKingDangerSquares(Board* board, std::array<int, 64>& kingDangerSquares);
};