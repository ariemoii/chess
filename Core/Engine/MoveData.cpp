#include "MoveData.h"
#include <iostream>
#include <bitset>

#define DELTA_OFFSET 128

MoveData::MoveData() {
  preComputeMoveData();
  preComputeAttackArray();
  //printAttackArray();
  
}

void MoveData::preComputeMoveData() {
  //knightMoveDelta on the 128 square board
  //knightMoves are unique in that they are not a sliding piece
  knightMoves = { 31, 33, 18, -14, -31, -33, -18, 14, 0 };

  bishopMoves = { NE, SE, SW, NW, 0 };
  rookMoves = { N, E, S, W, 0 };
  queenMoves = { N, E, S, W, NE, SE, SW, NW, 0 };

  //king moves like a queen but 1 square
  kingMoves = { N, E, S, W, NE, SE, SW, NW, 0 };

}

void MoveData::preComputeAttackArray() {
  //sliding pieces
  preComputeAttackSlidingPiece(bishopMoves, ABISHOP);
  preComputeAttackSlidingPiece(rookMoves, AROOK);
  preComputeAttackSlidingPiece(queenMoves, AQUEEN);

  //knight moves
  for(auto &dir : knightMoves) {
    if(dir == 0) break;
    attackArray[DELTA_OFFSET + dir] |= AKNIGHT;
  }

  //king moves
  for(auto &dir : kingMoves) {
    if(dir == 0) break;
    attackArray[DELTA_OFFSET + dir] |= AKING;
  }

  //white pawn attacks
  attackArray[DELTA_OFFSET + NE] |= AWPAWN;
  attackArray[DELTA_OFFSET + NW] |= AWPAWN;

  //black pawn attacks
  attackArray[DELTA_OFFSET + SE] |= ABPAWN;
  attackArray[DELTA_OFFSET + SW] |= ABPAWN;
}

void MoveData::preComputeAttackSlidingPiece(std::array<int, 64> slidingPieceArray, AttackPieceType type) {
  for(auto &dir : slidingPieceArray) {
    if(dir == 0) break;
    //a board has 8 squares on both sides, so generate delta for all of them
    for(int i = 1; i <= 8; i++) {
      
      attackArray[DELTA_OFFSET + (dir*i)] |= type;
    }
  }
}

void MoveData::printAttackArray() {
  int j = 0;
  for(auto &sq : attackArray) {
    if(j%8 == 0) {
      putchar('\n');
    }
    std::bitset<8> binary(sq);
    std::cout << binary << " ";
    j++;
  }
}

bool MoveData::canAttack(AttackPieceType type, int fromSquare, int toSquare) {
  return attackArray[DELTA_OFFSET + fromSquare-toSquare] & type;
}