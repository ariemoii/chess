#pragma once

#include "PseudoLegalMoveGenerator.h"
#include "controller/MoveMaker.h"
#include "MoveData.h"
#include "model/Board.h"

#include <vector>
#include <array>
#include <unordered_set>


class MoveGenerator {
  public:
    

    MoveGenerator();

  private:
    PseudoLegalMoveGenerator pseudoLegalMoveGenerator;
    MoveData moveData;
    MoveMaker moveMaker;

  public:
    void generateLegalMoves(Board* board, std::vector<Move>& legalMoves);
    bool isCheckMate(Board* board);
    bool isInCheck(Board* board, Piece::Team team, int square = -1);
    void generateKingDangerSquares(Piece::Team ourTeam, Board* board, std::unordered_set<int>& kingDangerSquares);

  private:
    bool isLeftInCheck(Move move, Piece::Team ourTeam, Board* board);
    
    void kingDangerSquaresSlidingPieces(const std::array<int, 64>& slidingPieceMovement, 
      std::unordered_set<int>& kingDangerSquares, Board* board, int fromSquare, Piece::Team ourTeam);

};