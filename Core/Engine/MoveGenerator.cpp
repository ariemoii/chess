#include "MoveGenerator.h"

MoveGenerator::MoveGenerator() :
pseudoLegalMoveGenerator(PseudoLegalMoveGenerator()),
moveData(MoveData()),
moveMaker(MoveMaker())
{
};

void MoveGenerator::generateLegalMoves(Board* board, std::vector<Move>& legalMoves) {
  std::vector<Move> pseudoLegalMoves;
  pseudoLegalMoveGenerator.generatePseudolegalMoves(board, pseudoLegalMoves);
  Piece::Team ourSide = board->sideToMove;
  std::unordered_set<int> kingDangerSquares;
  generateKingDangerSquares(ourSide, board, kingDangerSquares);
  int kingPosition = (ourSide == Piece::WHITE) ? board->whiteKingLoc : board->blackKingLoc;
  bool areInCheckCurrently = kingDangerSquares.count(kingPosition);
  for(Move moveToCheck : pseudoLegalMoves) {
    if(areInCheckCurrently && (moveToCheck.isCastleKingMove() || moveToCheck.isCastleQueenMove())) {
      //cant castle out of check
      continue;
    }
    if(moveToCheck.isCastleKingMove()) {
      if(kingDangerSquares.count(moveToCheck.fromSquare+1)) {
        //cant castle through check kingside
        continue;
      }
    } 
    if(moveToCheck.isCastleQueenMove()) {
      if(kingDangerSquares.count(moveToCheck.fromSquare-1)) {
        //cant castle through check queenside either
        continue;
      }
    }

    if(moveToCheck.isEnPassantMove()) {
      moveMaker.makeMove(moveToCheck, board);
      if(isInCheck(board, ourSide)) {
        continue;
      }
      moveMaker.unmakeLastMove(board);
    }

    if(kingPosition == moveToCheck.fromSquare) {
      //if we move the king, see if we are moving to an attacked square
      if(kingDangerSquares.count(moveToCheck.toSquare)) {
        continue;
      }
    }


    moveMaker.makeMove(moveToCheck, board);
    bool illegal = isInCheck(board, ourSide); 
    if(!illegal) {
      legalMoves.push_back(moveToCheck);
    }
    moveMaker.unmakeLastMove(board);

    legalMoves.push_back(moveToCheck);
  }
  return;
}

//we are in checkmate if we are in check and are still in check after
//any move we can make
bool MoveGenerator::isCheckMate(Board* board) {
  Piece::Team ourTeam = board->sideToMove;
  bool amInCheck = isInCheck(board, ourTeam);
  if(!amInCheck) {
    return false;
  }
  std::vector<Move> legalMoves;
  generateLegalMoves(board, legalMoves);
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

bool MoveGenerator::isLeftInCheck(Move move, Piece::Team ourTeam, Board* board) {

}

void MoveGenerator::generateKingDangerSquares(Piece::Team ourTeam, Board* board, std::unordered_set<int>& kingDangerSquares) {
  for(int i = 0; i < board->theBoard.size(); i++) {
    int piece = board->theBoard[i];
    if(piece == 0) continue;
    if(Piece::isTeam(piece, ourTeam)) continue;

    //knight attacks
    if(Piece::isType(piece, Piece::KNIGHT)) {
      for(const int &dir : moveData.knightMoves) {
        if(dir == 0) break;
        if((i+dir) & 0x88) continue;
        kingDangerSquares.insert(i+dir);
      }
    } else if(Piece::isType(piece, Piece::ROOK)) {
      //rook attacks
      kingDangerSquaresSlidingPieces(moveData.rookMoves, kingDangerSquares, board, i, ourTeam);
    } else if(Piece::isType(piece, Piece::BISHOP)) {
      kingDangerSquaresSlidingPieces(moveData.bishopMoves, kingDangerSquares, board, i, ourTeam);
    } else if(Piece::isType(piece, Piece::QUEEN)) {
      kingDangerSquaresSlidingPieces(moveData.queenMoves, kingDangerSquares, board, i, ourTeam);
    } else if(Piece::isType(piece, Piece::KING)) {
      for(const int &dir : moveData.kingMoves) {
        if(dir == 0) break;
        if((i+dir) & 0x88) continue;
        kingDangerSquares.insert(i+dir);
      }
    } else if(Piece::isType(piece, Piece::PAWN)) {
      int dir1, dir2;
      //if we are white, black pawns attack us
      dir1 = (ourTeam == Piece::WHITE) ? MoveData::SE : MoveData::NE;
      if(!((i+dir1) & 0x88)) {
        kingDangerSquares.insert(i+dir1);
      }
      dir2 = (ourTeam == Piece::WHITE) ? MoveData::SW : MoveData::NW;
      if(!((i+dir2) & 0x88)) {
        kingDangerSquares.insert(i+dir2);
      }
    }
  }
}

void MoveGenerator::kingDangerSquaresSlidingPieces(const std::array<int, 64>& slidingPieceArray, std::unordered_set<int>& kingDangerSquares, Board* board,int fromSquare, Piece::Team ourTeam) {
  int enemyKingLoc=  (ourTeam == Piece::WHITE) ? board->blackKingLoc : board->whiteKingLoc;
  for(const int &dir : slidingPieceArray) {
    if(dir == 0) break;
    for(int i = 1; i <= 8; i++) {
      if((fromSquare+dir*i) & 0x88) break;
      if(board->theBoard[fromSquare+dir*i] != 0) {
        //if we see a piece, add it to the attacked squares and break
        //we dont care that we add our own piece since we cannot move on there anyway
        kingDangerSquares.insert(fromSquare+dir*i);
        if(!(fromSquare+dir*i == enemyKingLoc)) {
          break;
        }
      }
      kingDangerSquares.insert(fromSquare+dir*i);
    }
  }
  return;
}