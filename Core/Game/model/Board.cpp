#include "Board.h"

int Board::theBoard[16*8] = {};

Board::Board() { 
  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {
      theBoard[i*16 + j] = 0;
    }
  }
}

void Board::printBoard() {
  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {
      std::cout << Piece::getType(theBoard[i*16 + j]) << Piece::getTeam(theBoard[i*16 + j]) << " ";
    }
    std::cout << '\n';
  }
}

void Board::askTeam() {
  std::string c;
  while(1) {
    std::cout << "What team would you like to play as? ";
    std::cout << "Enter '1' for white, '2' for black\n";
    getline(std::cin, c);
    if(c[0] != '1' && c[0] != '2') {
      std::cout << "Invalid Option!\n";
    } else {
      break;
    }
  }
  if(c[0] == '1') {
    humanTeam = Piece::WHITE;
  } else {
    humanTeam = Piece::BLACK;
  }
}

void Board::askTypeGame() {
  std::string c;
  while(1) {
    std::cout << "What game would you like to play? ";
    std::cout << "Enter '1' for vs AI (not implemented), '2' for vs human (not implemented)\n";
    std::cin >> c;
    getline(std::cin, c);
    if(c[0] != '2') {
      std::cout << "Invalid Option!\n";
    } else {
      break;
    }
  }
  if(c[0] == '1') {
    typeGame = Board::HumanVAI;
  } else {
    typeGame = Board::HumanVHuman;
    humanTeam = Piece::WHITE;
  }
}