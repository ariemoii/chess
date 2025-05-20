#include "MoveGenerator.h"

MoveGenerator::MoveGenerator() :
pseudoLegalMoveGenerator(PseudoLegalMoveGenerator()),
moveData(MoveData()),
moveMaker(MoveMaker())
{
};

std::vector<Move> MoveGenerator::generateLegalMoves(Board* board) {
  std::vector<Move> pseudoLegalMoves = pseudoLegalMoveGenerator.generatePseudolegalMoves(board);
  std::vector<Move> fullyLegalMoves;
  for(Move moveToCheck : pseudoLegalMoves) {
    moveMaker.makeMove(moveToCheck, board);
    std::vector<Move> pseudoLegalMovesOpp = pseudoLegalMoveGenerator.generatePseudolegalMoves(board);
    bool illegal = false;
    for(Move oppMove : pseudoLegalMovesOpp) {
      if(Piece::isType(board->theBoard[oppMove.toSquare], Piece::KING)) {
        //we've captured the king (illegal move)
        //do nothign
        illegal = true;
        break;
      }
    }
    if(!illegal) {
      fullyLegalMoves.push_back(moveToCheck);
    }
    moveMaker.unmakeLastMove(board);
  }
  return fullyLegalMoves;
}

bool MoveGenerator::isCheckMate(Board* board) {
  
}