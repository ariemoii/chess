#include "MoveMaker.h"

//delete iostream at some point
#include <iostream>

MoveMaker::MoveMaker(){};


void MoveMaker::makeMove(Move move, Board* board) {
  int fromFile = move.fromSquare.file, fromRank = move.fromSquare.rank;
  int toFile = move.toSquare.file, toRank = move.toSquare.rank;
  int piece = board->theBoard[fromFile][fromRank];

  std::cout << "from " << fromFile << fromRank;
  std::cout << " to " << toFile << toRank;
  std::cout << "piece here = \n";
  if(Piece::getTeam(piece) == Piece::WHITE) {
    std::cout << "white ";
  }
  if(Piece::getTeam(piece) == Piece::BLACK) {
    std::cout << "black ";
  }
  std::cout << Piece::getType(piece) << std::endl;

  board->theBoard[fromFile][fromRank] = 0;
  board->theBoard[toFile][toRank] = piece;
  return;
}