#include "MoveGenerator.h"

MoveGenerator::MoveGenerator() :
moveData(MoveData())
{ 
};


std::vector<Move> MoveGenerator::generatePseudolegalMoves(Board* board, int startSquare) {
  return generateSlidingPieceMoves(startSquare, Piece::getType(board->theBoard[startSquare]), board);
}

std::vector<Move> MoveGenerator::generateSlidingPieceMoves(int startSquare, Piece::PieceType type, Board* board) {
  int piece = board->theBoard[startSquare];
  std::array<int, 64> slidingArray;
  std::cout << "piecetype = " << Piece::getType(piece) << std::endl;
  if(!(Piece::isSlidingPiece(piece))) {
    //perror("is not a sliding piece\n");
    //return no legal moves
    std::cout << "is not a sliding piece " << std::endl;
    return std::vector<Move>();
  }

  std::vector<Move> pseudoLegalSlidingMoves;
  switch(type) {
    case Piece::BISHOP:
      slidingArray = moveData.bishopMoves;
      break;
    case Piece::ROOK:
      slidingArray = moveData.rookMoves;
      break;
    case Piece::QUEEN:
      slidingArray = moveData.queenMoves;
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