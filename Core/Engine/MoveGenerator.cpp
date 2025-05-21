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
    Piece::Team ourSide = board->sideToMove;
    moveMaker.makeMove(moveToCheck, board);
    // std::vector<Move> pseudoLegalMovesOpp = pseudoLegalMoveGenerator.generatePseudolegalMoves(board);
    // bool illegal = false;
    // for(Move oppMove : pseudoLegalMovesOpp) {
    //   if(Piece::isType(board->theBoard[oppMove.toSquare], Piece::KING)) {
    //     //we've captured the king (illegal move)
    //     //do nothign
    //     illegal = true;
    //     break;
    //   }
    // }
    bool illegal = isInCheck(board, ourSide);
    if(!illegal) {
      fullyLegalMoves.push_back(moveToCheck);
    }
    moveMaker.unmakeLastMove(board);
  }
  return fullyLegalMoves;
}

//we are in checkmate if we are in check and are still in check after
//any move we can make
bool MoveGenerator::isCheckMate(Board* board) {
  Piece::Team ourTeam = board->sideToMove;
  bool amInCheck = isInCheck(board, ourTeam);
  if(!amInCheck) {
    return false;
  }
  std::vector<Move> legalMoves = generateLegalMoves(board);
  for(Move legalMove : legalMoves) {
    moveMaker.makeMove(legalMove, board);
    if(!isInCheck(board, ourTeam)) {
      return false;
    }
  }
  return true;
}

bool MoveGenerator::isInCheck(Board* board, Piece::Team team) {
  for(int i = 0; i < board->theBoard.size(); i++) {
    int piece = board->theBoard[i];
    if(piece == 0) {
      //there is no piece
      continue;
    }
    if(Piece::isTeam(piece, team)) {
      //we cannot attack our own king
      continue;
    }
    int kingLoc = (team == Piece::WHITE) ? board->whiteKingLoc : board->blackKingLoc;
    if(moveData.canAttack(piece, i, kingLoc, board)) {
      //they can attack the king, so we are in check.
      return true;
    }
  }
  return false;
}