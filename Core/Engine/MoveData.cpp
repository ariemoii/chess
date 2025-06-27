#include "MoveData.h"
#include <iostream>
#include <bitset>

#define DELTA_OFFSET 128

MoveData::MoveData() {
  preComputeMoveData();
  preComputeAttackArray();
  preComputeDirectionArray();
  preComputeSquaresTillEdge();
  preComputeMoveBitboards();
  //printAttackArray();
}

void MoveData::preComputeSquaresTillEdge() {
  for(int i = 0; i < 64; i++) {
    int rank = i/8;
    int file = i%8;

    //north
    squaresTillEdge[i][0] = 7-rank;
    //east
    squaresTillEdge[i][1] = 7-file;
    //south
    squaresTillEdge[i][2] = rank;
    //west
    squaresTillEdge[i][3] = file;
  }
}

void MoveData::preComputeMoveBitboards() {
  //rook
  for(int i = 0; i < 64; i++) {
    //north
    for(int j = 1; j <= squaresTillEdge[i][0]; j++) {
      rookMoves[i] |= 1ULL << (i + 8*j);
    }
    //east
    for(int j = 1; j <= squaresTillEdge[i][1]; j++) {
      rookMoves[i] |= 1ULL << (i + 1*j);
    }
    //south
    for(int j = 1; j <= squaresTillEdge[i][2]; j++) {
      rookMoves[i] |= 1ULL << (i + -8*j);
    }
    //west
    for(int j = 1; j <= squaresTillEdge[i][3]; j++) {
      rookMoves[i] |= 1ULL << (i + -1*j);
    }
  }
}

void MoveData::preComputeMoveData() {
  //knightMoveDelta on the 128 square board
  //knightDirections are unique in that they are not a sliding piece
  knightDirections = { 31, 33, 18, -14, -31, -33, -18, 14, 0 };

  bishopDirections = { NE, SE, SW, NW, 0 };
  rookDirections = { N, E, S, W, 0 };
  queenDirections = { N, E, S, W, NE, SE, SW, NW, 0 };

  //king moves like a queen but 1 square
  kingDirections = { N, E, S, W, NE, SE, SW, NW, 0 };

}

void MoveData::preComputeAttackArray() {
  //sliding pieces
  preComputeAttackSlidingPiece(bishopDirections, ATTACK_BISHOP);
  preComputeAttackSlidingPiece(rookDirections, ATTACK_ROOK);
  preComputeAttackSlidingPiece(queenDirections, ATTACK_QUEEN);

  //knight moves
  for(auto &dir : knightDirections) {
    if(dir == 0) break;
    attackArray[DELTA_OFFSET + dir] |= ATTACK_KNIGHT;
  }

  //king moves
  for(auto &dir : kingDirections) {
    if(dir == 0) break;
    attackArray[DELTA_OFFSET + dir] |= ATTACK_KING;
  }

  //white pawn attacks
  attackArray[DELTA_OFFSET + NE] |= ATTACK_WHITE_PAWN;
  attackArray[DELTA_OFFSET + NW] |= ATTACK_WHITE_PAWN;

  //black pawn attacks
  attackArray[DELTA_OFFSET + SE] |= ATTACK_BLACK_PAWN;
  attackArray[DELTA_OFFSET + SW] |= ATTACK_BLACK_PAWN;
}

void MoveData::preComputeAttackSlidingPiece(std::array<int, 64> slidingPieceArray, int type) {
  for(auto &dir : slidingPieceArray) {
    if(dir == 0) break;
    //a board has 8 squares on both sides, so generate delta for all of them
    for(int i = 1; i <= 8; i++) {
      attackArray[DELTA_OFFSET + (dir*i)] |= type;
    }
  }
}

void MoveData::preComputeDirectionArray() {
  //direction array rook and queen
  for(int dir : rookDirections) {
    if(dir == 0) {
      break;
    }
    for(int i = 1; i <= 8; i++) {
      directionVector[DELTA_OFFSET + (dir*i)] = dir;
    }
  }

  //direction array bishop and queen
  for(int dir : bishopDirections) {
    if(dir == 0) {
      break;
    }
    for(int i = 1; i <= 8; i++) {
      directionVector[DELTA_OFFSET + (dir*i)] = dir;
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

bool MoveData::canAttack(int piece, int fromSquare, int toSquare, Board* board) {
  int delta = toSquare - fromSquare;
  int type = pieceToAttackPiece[piece];
  if(!(attackArray[delta+DELTA_OFFSET] & type)) {
    //we cannot get there
    return false;
  }
  //if we have a non-sliding piece, we are done
  if(!Piece::isSlidingPiece(piece)) {
    return true;
  }

  //we need to traverse ray
  int direction = directionVector[delta+DELTA_OFFSET];
  while(fromSquare != toSquare) {
    int pieceOnNextSquare = board->theBoard[fromSquare+direction];
    if(pieceOnNextSquare) {
      //there is a piece in the way
      if(Piece::isTeam(piece, Piece::getTeam(pieceOnNextSquare))) {
        //they are the same team
        return false;
      }
      if(fromSquare+direction == toSquare) {
        //only if they are from different teams
        //and we can take it
        return true;
      }
      return false;
    }
    fromSquare += direction;
  }
  return true;
}

int MoveData::squareToInt(std::string square) {
  int file, rank;
  file = square[0] - 'a';
  rank = square[1] - '0' - 1;
  return file+rank*16;
}

std::string MoveData::intToSquare(int square) {
  char file, rank;
  rank = square/16 + '1';
  file = square%8 + 'a';
  std::string returning;
  returning.push_back(file);
  returning.push_back(rank);
  return returning;
}