#include "FENparser.h"
#include <iostream>


FENparser::FENparser(){};

Piece_Type FENparser::pieceTypeFromSymbol(char i) {
  switch(i) {
    case 'k':
      return KING;
    case 'n':
      return KNIGHT;
    case 'b':
      return BISHOP;
    case 'r':
      return ROOK;
    case 'q':
      return QUEEN;
    case 'p':
      return PAWN;
    default:
      perror("invalid FEN!");
      exit(EXIT_FAILURE);
      return PAWN;
  }
}

/**
 * help on splitting a string: https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-chttps://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
 */
void FENparser::parseFenOnBoard(std::string fen, Board *board) {
  std::string space = " ";
  std::string boardFEN = fen.substr(0, fen.find(space));
  int file = 0, rank = 7;

  std::vector<Piece> pieceVector;

  for(auto &i : boardFEN) {
    if(i == '/') {
      //new rank;
      file = 0;
      rank--;
    } else {
      if(isdigit(i)) {
        file += i-'0';
      } else {
        Team pieceColour = (isupper(i)) ? WHITE : BLACK;
        Piece_Type pieceType = pieceTypeFromSymbol(tolower(i));
        Piece piece(pieceType, pieceColour, file, rank);
        pieceVector.push_back(piece);
        file++;
      }
    }
  }
  for(auto &i : pieceVector) {
    std::unique_ptr<Piece> piece;
    switch(i.getType()) {
      case KING:
        piece = std::make_unique<King>(i.getTeam(), i.getFile(), i.getRank());
        break;
      case KNIGHT:
        piece = std::make_unique<Knight>(i.getTeam(), i.getFile(), i.getRank());
        break;
      case PAWN:
        piece = std::make_unique<Pawn>(i.getTeam(), i.getFile(), i.getRank());
        break;
      case BISHOP:
        piece = std::make_unique<Bishop>(i.getTeam(), i.getFile(), i.getRank());
        break;
      case QUEEN:
        piece = std::make_unique<Queen>(i.getTeam(), i.getFile(), i.getRank());
        break;
      case ROOK:
        piece = std::make_unique<Rook>(i.getTeam(), i.getFile(), i.getRank());
        break;
      default:
        perror("something went wrong parsing FEN\n");
        piece = std::make_unique<Piece>();
        break;
    }
    board->addPiece(std::move(piece));
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