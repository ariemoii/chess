#include "Board.h"

#include <iostream>

Board::Board(){};

void Board::addPiece(std::unique_ptr<Piece> piece) {
  theBoard[piece->getRank()][piece->getFile()] = std::move(piece);
} 

void Board::printBoard() {
  for(int i = 7; i >= 0; i--) {
    for(int j = 0; j < 8; j++) {
      if(theBoard[i][j]->getType() == NIKS) {
        std::cout << '9';
      } else {
        std::cout << theBoard[i][j]->getType();
      }
    }
    std::cout << '\n';
  } 
}

void Board::initBoard() {
  for(int i = 7; i >= 0; i--) {
    for(int j = 0; j < 8; j++) {
      theBoard[i][j] = std::make_unique<Piece>();
    }
  }
}