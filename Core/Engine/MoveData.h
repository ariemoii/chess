#pragma once
#include "model/Piece.h"
#include <array>

class MoveData {
  public:
    enum Direction { N=16, E=1, S=-16, W=-1, NE=17, SE=-15, SW=-17, NW=15 };

  public:
    static std::array<int, 256> attackArray;

    //store the squares a piece can move to
    //so a rook can move 1..8 to the north, so store 1*N, 2*N, etc.

    static std::array<int, 64> bishopMoves;
    static std::array<int, 64> rookMoves;
    static std::array<int, 64> queenMoves;
    static std::array<int, 64> kingMoves;
    static std::array<int, 64> knightMoves;
    static std::array<int, 64> blackPawnMoves;
    static std::array<int, 64> whitePawnMoves;

  private:
    static void PreComputeMoveData();

};