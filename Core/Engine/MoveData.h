#pragma once
#include "model/Piece.h"
#include <array>

class MoveData {
  public:
    enum Direction { N=16, E=1, S=-16, W=-1, NE=17, SE=-15, SW=-17, NW=15 };

    MoveData();

  public:
    std::array<int, 256> attackArray;

    //store the squares a piece can move to
    //so a rook can move 1..8 to the north, so store 1*N, 2*N, etc.

    std::array<int, 64> bishopMoves;
    std::array<int, 64> rookMoves;
    std::array<int, 64> queenMoves;
    std::array<int, 64> kingMoves;
    std::array<int, 64> knightMoves;
    std::array<int, 64> blackPawnMoves;
    std::array<int, 64> whitePawnMoves;


  private:
    void preComputeMoveData();

};