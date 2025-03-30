#include "MoveMaker.h"

//delete iostream at some point
#include <iostream>

MoveMaker::MoveMaker(){};


void MoveMaker::makeMove(Move move, Board* board, Piece::Team humanTeam) {
  int fromSquare, toSquare;

  if(humanTeam == Piece::WHITE) {
    //((7*16)+7) is needed because the board is mirrored
    //when looking at it from whites perspective
    fromSquare = ((7*16)+7)-move.fromSquare;
    toSquare = ((7*16)+7)-move.toSquare;
  } else {
    fromSquare = move.fromSquare;
    toSquare = move.toSquare;
  }
  int piece = board->theBoard[fromSquare];
  if(piece == 0) {
    //no piece here
    return;
  }
  board->theBoard[fromSquare] = 0;
  board->theBoard[toSquare] = piece;



  return;
}