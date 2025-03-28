#include "FENparser.h"
#include <iostream>


FENparser::FENparser(){};

NewPiece::Piece_Type FENparser::pieceTypeFromSymbol(char i) {
  switch(i) {
    case 'k':
      return NewPiece::KING;
    case 'n':
      return NewPiece::KNIGHT;
    case 'b':
      return NewPiece::BISHOP;
    case 'r':
      return NewPiece::ROOK;
    case 'q':
      return NewPiece::QUEEN;
    case 'p':
      return NewPiece::PAWN;
    default:
      perror("invalid FEN!");
      exit(EXIT_FAILURE);
      return NewPiece::PAWN;
  }
}

/**
 * help on splitting a string: https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-chttps://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
 */
void FENparser::parseFenOnBoard(std::string fen, NewBoard *board) {
  std::string space = " ";
  std::string boardFEN = fen.substr(0, fen.find(space));
  int file = 0, rank = 7;

  for(auto &i : boardFEN) {
    if(i == '/') {
      //new rank;
      file = 0;
      rank--;
    } else {
      if(isdigit(i)) {
        file += i-'0';
      } else {
        NewPiece::Team pieceColour = (isupper(i)) ? NewPiece::WHITE : NewPiece::BLACK;
        NewPiece::Piece_Type pieceType = pieceTypeFromSymbol(tolower(i));
        int piece = pieceType | pieceColour;
        board->theBoard[rank][file] = piece;
        file++;
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
  ungetc(c, stdout);
  std::string fen;
  getline(std::cin, fen);
  return fen;
}