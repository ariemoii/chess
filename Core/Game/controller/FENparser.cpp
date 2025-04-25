#include "FENparser.h"
#include <iostream>


FENparser::FENparser(){};

Piece::PieceType FENparser::pieceTypeFromSymbol(char i) {
  switch(i) {
    case 'k':
      return Piece::KING;
    case 'n':
      return Piece::KNIGHT;
    case 'b':
      return Piece::BISHOP;
    case 'r':
      return Piece::ROOK;
    case 'q':
      return Piece::QUEEN;
    case 'p':
      return Piece::PAWN;
    default:
      perror("invalid FEN!");
      exit(EXIT_FAILURE);
      return Piece::PAWN;
  }
}

/**
 * help on splitting a string: https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-chttps://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
 */
void FENparser::parseFenOnBoard(std::string fen, Board *board) {
  std::string space = " ";
  std::string boardFEN = fen.substr(0, fen.find(space));
  int file = 7, rank = 7;
  for(auto &i : boardFEN) {
    if(i == '/') {
      //new rank;
      file = 7;
      rank--;
    } else {
      if(isdigit(i)) {
        file -= i-'0';
      } else {
        Piece::Team pieceColour = (isupper(i)) ? Piece::WHITE : Piece::BLACK;
        Piece::PieceType pieceType = pieceTypeFromSymbol(tolower(i));
        int piece = pieceType | pieceColour;
        board->theBoard[rank*16 + file] = piece;
        file--;
      }
    }
  }
}

std::string FENparser::requestFEN() {
  std::cout << "enter FEN to load from position, or press 'enter' for standard game:\n";
  char c = getchar();
  if(c == '\n') {
    return std::string("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
  }
  ungetc(c, stdin);
  std::string fen;
  getline(std::cin, fen);
  return fen;
}