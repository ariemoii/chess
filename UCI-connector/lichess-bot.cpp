#include "lichess-bot.h"
#include "controller/MoveMaker.h"
#include "controller/FENparser.h"
#include <sstream>
#include "model/Move.h"
#include "MoveData.h"

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
          realMove.isPromoteQueenMove();
          break;
        case 'r':
          realMove.isPromoteRookMove();
          break;
        case 'n':
          realMove.isPromoteKnightMove();
          break;
        case 'b':
          realMove.isPromoteBishopMove();
          break;
      }
    }
  }
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
  for(Move move : moves) {
    std::cout << MoveData::intToSquare(move.fromSquare) << MoveData::intToSquare(move.toSquare) << "\n";
  }
  return moves;
}


void processPositionCommand(std::string message, Board* board) {
  FENparser parser;
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
  std::vector<Move> moves = extractMoves(words, placeMoveList);
  for(Move move : moves) {
    //play them
  }
}




