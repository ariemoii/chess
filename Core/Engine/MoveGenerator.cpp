#include "MoveGenerator.h"

MoveGenerator::MoveGenerator() { 

};


std::vector<Move> MoveGenerator::generatePeudolegalMoves(Board* board, int startSquare) {
  return generateSlidingPieceMoves(startSquare, Piece::getType(board->theBoard[startSquare]), board);
}

std::vector<Move> MoveGenerator::generateSlidingPieceMoves(int startSquare, Piece::PieceType type, Board* board) {
  int piece = board->theBoard[startSquare];
  std::array<int, 64> slidingArray;
  if(!Piece::isSlidingPiece(piece)) {
    perror("is not a sliding piece\n");
  }

  std::vector<Move> pseudoLegalSlidingMoves;
  switch(type) {
    case Piece::BISHOP:
      slidingArray = MoveData::bishopMoves;
      break;
    case Piece::ROOK:
      slidingArray = MoveData::rookMoves;
      break;
    case Piece::QUEEN:
      slidingArray = MoveData::queenMoves;
      break;
  }

  for(const auto &i : slidingArray) {
    if(i == 0) {
      break;
    }
    Move move;
    move.fromSquare = startSquare;
    move.toSquare = startSquare+i;
    if(move.toSquare & 0x88) {
      //move is outside of the board
      continue;
    }
    pseudoLegalSlidingMoves.push_back(move);
  }
  return pseudoLegalSlidingMoves;
}