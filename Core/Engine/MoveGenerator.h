#pragma once

#include "PseudoLegalMoveGenerator.h"
#include "controller/MoveMaker.h"
#include "model/Board.h"
#include <vector>


class MoveGenerator {
  public:
    

    MoveGenerator();

  private:
    PseudoLegalMoveGenerator pseudoLegalMoveGenerator;
    MoveData moveData;
    MoveMaker moveMaker;

  public:
    std::vector<Move> generateLegalMoves(Board* board);
    bool isCheckMate(Board* board);
    bool isInCheck(Board* board, Piece::Team team);

  private:


};