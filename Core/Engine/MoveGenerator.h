#pragma once

#include "PseudoLegalMoveGenerator.h"
#include <vector>


class MoveGenerator {
  public:
    

    MoveGenerator();

  private:
    PseudoLegalMoveGenerator pseudoLegalMoveGenerator;
    MoveData moveData;
    bool resultsInCheck(Board* board);

  public:
    std::vector<Move> generateLegalMoves(Board* board);


  private:


};