#include "MoveData.h"

  //knightMoveDelta on the 128 square board
  //knightMoves are unique in that they are not a sliding piece
std::array<int, 64> MoveData::knightMoves = { 31, 33, 18, -14, -31, -33, -18, 14, 0 };

std::array<int, 64> MoveData::bishopMoves = { NE, SE, SW, NW, 0 };
std::array<int, 64> MoveData::rookMoves = { N, E, S, W, 0 };
std::array<int, 64> MoveData::queenMoves = { N, E, S, W, NE, SE, SW, NW, 0 };

//king moves like a queen but 1 square
std::array<int, 64> MoveData::kingMoves = { N, E, S, W, NE, SE, SW, NW, 0 };

void MoveData::PreComputeMoveData() {
  //knightMoveDelta on the 128 square board
  //knightMoves are unique in that they are not a sliding piece
  knightMoves = { 31, 33, 18, -14, -31, -33, -18, 14, 0 };

  bishopMoves = { NE, SE, SW, NW, 0 };
  rookMoves = { N, E, S, W, 0 };
  queenMoves = { N, E, S, W, NE, SE, SW, NW, 0 };

  //king moves like a queen but 1 square
  kingMoves = { N, E, S, W, NE, SE, SW, NW, 0 };

}