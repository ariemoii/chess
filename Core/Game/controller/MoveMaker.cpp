#include "MoveMaker.h"

//delete iostream at some point
#include <iostream>

MoveMaker::MoveMaker() : 
moveGenerator(MoveGenerator()){
  
};


void MoveMaker::makeMove(Move move, Board* board) {
  int piece = board->theBoard[move.fromSquare];
  if(piece == 0) {
    //no piece here
    return;
  }
  board->theBoard[move.fromSquare] = 0;
  board->theBoard[move.toSquare] = piece;

  //handle castling moves
  if(move.isCastleKing) {
    board->theBoard[move.fromSquare-3] = 0;
    board->theBoard[move.fromSquare-1] = board->sideToMove | Piece::ROOK;
  }
  if(move.isCastleQueen) {
    board->theBoard[move.fromSquare+4] = 0;
    board->theBoard[move.fromSquare+1] = board->sideToMove | Piece::ROOK;
  }
  if(move.isCastleKing || move.isCastleQueen) {
    //revoke this colors castling rights
    if(board->sideToMove == Piece::WHITE) {
      board->whiteCastleRights = 0;
    } else {
      board->blackCastleRights = 0;
    }
  }

  //we need to change the side to move
  if(board->sideToMove == Piece::WHITE) {
    board->sideToMove = Piece::BLACK;
  } else {
    board->sideToMove = Piece::WHITE;
  }
  
  return;
}

void MoveMaker::tryMakeMove(Move move, Board* board) {
  int piece = board->theBoard[move.fromSquare];
  std::vector<Move> pseudoLegalMoves = moveGenerator.generatePseudolegalMoves(board);
  if(isLegalMove(&move, pseudoLegalMoves)) {
    std::cout << "move is legal " << std::endl;
    makeMove(move, board);
  } else {
    std::cout << "move is NOT legal " << std::endl;
  }
  std::cout << "square " << move.fromSquare << std::endl;
}

bool MoveMaker::isLegalMove(Move *move, std::vector<Move> moveList) {
  for(auto i : moveList) {
    if(i == *move) {
      *move = i;
      return true;
    }
  }
  return false;
}