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
  Piece::Team ourSide = board->sideToMove;
  bool areInCheckCurrently = isInCheck(board, ourSide);
  for(Move moveToCheck : pseudoLegalMoves) {
    if(areInCheckCurrently && (moveToCheck.isCastleKingMove() || moveToCheck.isCastleQueenMove())) {
      //cant castle out of check
      continue;
    }
    if(moveToCheck.isCastleKingMove()) {
      if(isInCheck(board, ourSide, moveToCheck.fromSquare+1)) {
        //cant castle through check kingside
        continue;
      }
    } 
    if(moveToCheck.isCastleQueenMove()) {
      if(isInCheck(board, ourSide, moveToCheck.fromSquare-1)) {
        //cant castle through check queenside either
        continue;
      }
    }
    moveMaker.makeMove(moveToCheck, board);
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
  return(legalMoves.size() == 0);
}

bool MoveGenerator::isInCheck(Board* board, Piece::Team team, int square) {
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
    if(square != -1) {
      kingLoc = square;
    }
    if(moveData.canAttack(piece, i, kingLoc, board)) {
      //they can attack the king, so we are in check.
      return true;
    }
  }
  return false;
}