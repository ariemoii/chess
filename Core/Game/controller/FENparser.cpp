#include "FENparser.h"
#include <iostream>
#include <sstream>


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
//this function assumes it is getting a legal fen string
void FENparser::parseFen(std::string fen, Board *board) {
  std::istringstream iss(fen);
  std::vector<std::string> words;
  std::string word;
  while(iss >> word) {
    words.push_back(word);
  }
  std::string boardFEN = words[0];
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
        Piece::Team pieceColour = (isupper(i)) ? Piece::WHITE : Piece::BLACK;
        Piece::PieceType pieceType = pieceTypeFromSymbol(tolower(i));
        int piece = pieceType | pieceColour;
        if(piece  == (Piece::WHITE | Piece::KING)) {
          board->whiteKingLoc = rank*16 + file;
        }
        if(piece == (Piece::BLACK | Piece::KING)) {
          board->blackKingLoc = rank*16 + file;
        }
        board->theBoard[rank*16 + file] = piece;
        file++;
      }
    }
  }
  extractBoardState(words, board);
}

void FENparser::extractBoardState(std::vector<std::string> words, Board* board) {
  //extract side to move
  std::string sideToMove = words[1];
  Piece::Team side;
  if(sideToMove == "w") {
    board->sideToMove = Piece::WHITE;
    side = Piece::WHITE;
  } else {
    board->sideToMove = Piece::BLACK;
    side = Piece::BLACK;
  }



  //extract castling rights
  std::string castlingRights = words[2];
  int rights = 0;
  if(castlingRights[0] == '-') {
    //neither side may castle
  } else {
    for(auto &right : castlingRights) {
      if(right == 'Q') {
        rights |= 0b10;
      }
      if(right == 'K') {
        rights |= 0b1;
      }
      if(right == 'q') {
        rights |= 0b1000;
      }
      if(right == 'k') {
        rights |= 0b100;
      }
    }
    GameState::setCastlingRights(rights, board->gameState);
  }

  //extract en passant squares
  std::string enPassant = words[3];
  if(enPassant != "-") {
    int square = MoveData::squareToInt(enPassant);
    if(side == Piece::WHITE) {
      GameState::setEPSquareWhite(square, board->gameState);
    } else {
      GameState::setEPSquareBlack(square, board->gameState);
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