#include "AI/Search.h"
#include "model/Piece.h"
#include "MoveGenerator.h"
#include "controller/MoveMaker.h"
#include "MoveData.h"
#include "model/Board.h"

#include <vector>

constexpr int PAWN_VALUE = 100;
constexpr int KNIGHT_VALUE = 300;
constexpr int ROOK_VALUE = 500;
constexpr int QUEEN_VALUE = 900;
constexpr int BISHOP_VALUE = 320;

static MoveGenerator moveGenerator;
static MoveMaker moveMaker;
static MoveData moveData;

static int countMaterial(Board* board, Piece::Team team) {
  int material = 0;
  for(int piece : board->theBoard) {
    if(!Piece::isTeam(piece, team)) continue;
    if(Piece::isType(piece, Piece::PAWN)) {
      material += PAWN_VALUE; 
    } else if(Piece::isType(piece, Piece::ROOK)) {
      material += ROOK_VALUE;
    } else if(Piece::isType(piece, Piece::QUEEN)) {
      material += QUEEN_VALUE;
    } else if(Piece::isType(piece, Piece::KNIGHT)) {
      material += KNIGHT_VALUE;
    } else if(Piece::isType(piece, Piece::BISHOP)) {
      material += BISHOP_VALUE;
    }
  }
  return material;
}

static int evaluate(Board* board) {
  int whiteEval = countMaterial(board, Piece::WHITE);
  int blackEval = countMaterial(board, Piece::BLACK);

  int evaluation = whiteEval-blackEval; 
  int perspective = (board->sideToMove == Piece::WHITE) ? 1 : -1;
  return evaluation*perspective;
}

static int search(int depth, Board* board) {
  if(depth == 0) {
    return evaluate(board);
  }

  std::vector<Move> moves;
  moveGenerator.generateLegalMoves(board, moves);

  if(moves.size() == 0) {
    if(moveGenerator.isInCheck(board, board->sideToMove)) {
      //what is worse than checkmate?
      return -999999999;
    }
    //it is stalemate
    return 0;
  }

  int bestEval = -999999999;

  for(Move move : moves) {
    moveMaker.makeMove(move, board);
    int evaluation = -search(depth-1, board);
    bestEval = std::max(bestEval, evaluation);
    moveMaker.unmakeLastMove(board);
  }
  return bestEval;
}




Move bestMove(Board* board) {
  std::vector<Move> moves;
  moveGenerator.generateLegalMoves(board, moves);
  Move theBest;
  int bestEval = -999999999;
  for(Move move : moves) {
    moveMaker.makeMove(move, board);
    int eval = -search(2, board);
    moveMaker.unmakeLastMove(board);
    if(eval >= bestEval) {
      bestEval = eval;
      theBest = move;
    }
    // std::cout << "eval for move " << MoveData::intToSquare(move.fromSquare) << MoveData::intToSquare(move.toSquare);
    // std::cout << " = " << eval << "\n";
  }
  return theBest;
}

