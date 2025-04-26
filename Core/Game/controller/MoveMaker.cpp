#include "MoveMaker.h"

//delete iostream at some point
#include <iostream>

MoveMaker::MoveMaker() : 
moveGenerator(MoveGenerator()){
  
};


void MoveMaker::makeMove(Move move, Board* board) {
  int piece = board->theBoard[move.fromSquare];
  std::vector<Move> pseudoLegalMoves = moveGenerator.generatePseudolegalMoves(board, move.fromSquare);
  if(isLegalMove(move, pseudoLegalMoves)) {
    std::cout << "move is legal " << std::endl;
  } else {
    std::cout << "move is NOT legal " << std::endl;
  }
  if(piece == 0) {
    //no piece here
    return;
  }
  board->theBoard[move.fromSquare] = 0;
  board->theBoard[move.toSquare] = piece;

  return;
}

void MoveMaker::tryMakeMove(Move move, Board* board) {
  int piece = board->theBoard[move.fromSquare];
  if(Piece::isSlidingPiece(piece)) {
    std::vector<Move> pseudoLegalMoves = moveGenerator.generatePseudolegalMoves(board, move.fromSquare);
    if(isLegalMove(move, pseudoLegalMoves)) {
      makeMove(move, board);
    }
  }
}

bool MoveMaker::isLegalMove(Move move, std::vector<Move> moveList) {
  for(auto &i : moveList) {
    if(i == move) {
      return true;
    }
  }
  return false;
}