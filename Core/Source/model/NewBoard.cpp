#include "NewBoard.h"

int NewBoard::theBoard[8][8] = {};

NewBoard::NewBoard() { 
  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {
      theBoard[i][j] = 0;
    }
  }
}

void NewBoard::printBoard() {
  for(int i = 7; i >= 0; i--) {
    for(int j = 0; j < 8; j++) {
      std::cout << NewPiece::getType(theBoard[i][j]) << NewPiece::getTeam(theBoard[i][j]) << " ";
    }
    std::cout << '\n';
  }
}