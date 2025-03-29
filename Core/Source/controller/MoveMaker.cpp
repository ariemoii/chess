#include "MoveMaker.h"

//delete iostream at some point
#include <iostream>

MoveMaker::MoveMaker(){};


void MoveMaker::makeMove(Move move, Board* board, Piece::Team humanTeam) {
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
  int piece = board->theBoard[fromFile][fromRank];
  if(piece == 0) {
    //no piece here
    return;
  }
  board->theBoard[fromFile][fromRank] = 0;
  board->theBoard[toFile][toRank] = piece;


  // if(humanTeam == Piece::WHITE) {
  //   int piece = board->theBoard[7-fromFile][7-fromRank];
  //   board->theBoard[7-fromFile][7-fromRank] = 0;
  //   board->theBoard[7-toFile][7-toRank] = piece;
  // } else {
  //   int piece = board->theBoard[fromFile][fromRank];
  //   board->theBoard[fromFile][fromRank] = 0;
  //   board->theBoard[toFile][toRank] = piece;
  // }
  return;
}