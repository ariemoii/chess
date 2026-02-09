#include "lichess-bot.h"
#include "controller/MoveMaker.h"
#include "controller/FENparser.h"
#include <sstream>
#include "model/Move.h"
#include "AI/Search.h"
#include "MoveData.h"

static FENparser parser;
static MoveMaker moveMaker;

std::string getInput() {
  std::string fen;
  getline(std::cin, fen);
  return fen;
}

void respond(std::string message) {
  std::cout << message << "\n";
  return;
}

Move getRealMove(std::string move, Board* board) {
  Move realMove;
  std::string fromsq, tosq;
  fromsq += move[0];
  fromsq += move[1];
  tosq += move[2];
  tosq += move[3];
  realMove.fromSquare = MoveData::squareToInt(fromsq);
  realMove.toSquare = MoveData::squareToInt(tosq);

  //extract flag

  int piece = board->theBoard[realMove.fromSquare];
  if(Piece::isType(piece, Piece::PAWN)) {
    if(move.size() > 4) {
      //jup, thats promotion
      switch(move[5]) {
        case 'q':
          realMove.setPromoteQueen();
          break;
        case 'r':
          realMove.setPromoteRook();
          break;
        case 'n':
          realMove.setPromoteKnight();
          break;
        case 'b':
          realMove.setPromoteBishop();
          break;
      }
    }
    if(abs(realMove.toSquare/16-realMove.fromSquare/16) == 2) {
      //double pawn push
      realMove.setPawnTwoSquares();
    }
    if(realMove.fromSquare%8 != realMove.toSquare%8 && board->theBoard[realMove.fromSquare] != 0) {
      //en passant
      realMove.setIsEnPassant();
    }
  }
  if(Piece::isType(piece, Piece::KING)) {
    if(realMove.fromSquare-realMove.toSquare == -2) {
      //kingside castle
      realMove.setCastleKingMove();
    } else if(realMove.fromSquare-realMove.toSquare == 2) {
      //queenside castle
      realMove.setCastleQueenMove();
    }
  }
  return realMove;
}


std::vector<Move> extractMoves(std::vector<std::string> words, int placeMoveList, Board* board) {
  std::vector<Move> moves;
  if(words.size() > placeMoveList) {
    //there are moves to parse
    for(int i = placeMoveList+1; i < words.size(); i++) {
      Move move = getRealMove(words[i], board);
      moves.push_back(move);
    }
  }
  return moves;
}


void processPositionCommand(std::string message, Board* board) {
  
  std::istringstream iss(message);
  std::vector<std::string> words;
  std::string word;
  
  while(iss >> word) {
    words.push_back(word);
  }
  int placeMoveList = 2;
  if(words[1] == "startpos") {
    parser.parseFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", board);
  } else if(words[1] == "fen") {
    parser.parseFen(words[2], board);
    placeMoveList = 3;
  }
  std::vector<Move> moves = extractMoves(words, placeMoveList, board);
  for(Move move : moves) {
    //play them
    moveMaker.makeMove(move, board);
  }
}


std::string processGoCommand(std::string message, Board* board) {
  std::string move = "";
  Move theMove = bestMove(board);
  move+= MoveData::intToSquare(theMove.fromSquare);
  move+= MoveData::intToSquare(theMove.toSquare);
  if(theMove.isPromoteQueenMove()) {
    move+='q';
  }
  if(theMove.isPromoteBishopMove()) {
    move+='b';
  }
  if(theMove.isPromoteKnightMove()) {
    move+='n';
  }
  if(theMove.isPromoteBishopMove()) {
    move+='b';
  }
  return move;
}




