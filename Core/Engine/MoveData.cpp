#include "MoveData.h"

MoveData::MoveData() {
  preComputeMoveData();
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