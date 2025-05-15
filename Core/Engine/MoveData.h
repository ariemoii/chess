#pragma once
#include "model/Piece.h"
#include <array>

class MoveData {
  public:
    enum Direction { N=16, E=1, S=-16, W=-1, NE=17, SE=-15, SW=-17, NW=15 };
    enum AttackPieceType { AKING = 0b1, AQUEEN = 0b10, AROOK = 0b100, ABISHOP = 0b1000, AKNIGHT = 0b10000, AWPAWN = 0b100000, ABPAWN = 0b1000000};

    MoveData();

    //used for debugging
    void printAttackArray();

    bool canAttack(AttackPieceType type, int fromSquare, int toSquare);

  public:

    //store the direction squares a piece can move to


    std::array<int, 64> bishopMoves;
    std::array<int, 64> rookMoves;
    std::array<int, 64> queenMoves;
    std::array<int, 64> kingMoves;
    std::array<int, 64> knightMoves;
    std::array<int, 64> blackPawnMoves;
    std::array<int, 64> whitePawnMoves;

  private:
    //attack array from 
    //https://web.archive.org/web/20071027053053/http://www.brucemo.com/compchess/programming/0x88.htm,
    std::array<int, 265> attackArray{};


  private:
    void preComputeMoveData();
    void preComputeAttackArray();
    void preComputeAttackSlidingPiece(std::array<int, 64> slidingPieceArray, AttackPieceType type);
};