#include "Board.h"

#include <bitset>
#include <iostream>
#include <string>

#include "model/Piece.h"



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
  std::cout << "bitboards:\n";
  for(int i = 0; i < 32; i++) {
    if(Piece::isTeam(i, Piece::WHITE) || Piece::isTeam(i, Piece::BLACK)) {
      int team = Piece::getTeam(i);
      int type = Piece::getType(i);
      std::cout << "team: " << team << " type: " << type << "\n";
      std::bitset<64> x(this->pieceBitboards[i]);
      std::cout << x << "\n";
    }
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

void Board::switchSideToMove() {
  if(sideToMove == Piece::WHITE) {
    sideToMove = Piece::BLACK;
  } else {
    sideToMove = Piece::WHITE;
  }
}

void Board::switchHumanTeam() {
  humanTeam = (humanTeam == Piece::WHITE) ? Piece::BLACK : Piece::WHITE;
}

