#include "MoveMaker.h"

//delete iostream at some point
#include <iostream>

MoveMaker::MoveMaker(){};


void MoveMaker::tryMakeMove(Move move, Board* board, Piece::Team humanTeam) {
  int fromFile, fromRank;
  int toFile, toRank;

  if(humanTeam == Piece::WHITE) {
    fromFile = 7-move.fromSquare.file;
    fromRank = 7-move.fromSquare.rank;
    toFile = 7-move.toSquare.file;
    toRank = 7-move.toSquare.rank;
  } else {
    fromFile = move.fromSquare.file;
    fromRank = move.fromSquare.rank;
    toFile = move.toSquare.file;
    toRank = move.toSquare.rank;
  }
  int piece = board->theBoard[fromRank*16 + fromFile];
  if(piece == 0) {
    //no piece here
    return;
  }
  board->theBoard[fromRank*16+ fromFile] = 0;
  board->theBoard[toRank*16 + toFile] = piece;



  return;
}