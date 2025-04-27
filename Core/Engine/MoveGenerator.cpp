#include "MoveGenerator.h"

MoveGenerator::MoveGenerator() :
moveData(MoveData())
{ 
};


std::vector<Move> MoveGenerator::generatePseudolegalMoves(Board* board) {
  //16*8 is the size of the board
  std::vector<Move> pseudoLegalMoves;
  for(int i = 0; i < 16*8; i++) {
    int piece = board->theBoard[i];
    if(Piece::isSlidingPiece(piece)) {
      generateSlidingPieceMoves(i, Piece::getType(piece), board, pseudoLegalMoves);
    }
  }
  return pseudoLegalMoves;
}

void MoveGenerator::generateSlidingPieceMoves(int startSquare, Piece::PieceType type, Board* board, std::vector<Move>& moveVector) {
  int piece = board->theBoard[startSquare];
  std::array<int, 64> slidingArray;
  if(!(Piece::isSlidingPiece(piece))) {
    //perror("is not a sliding piece\n");
    //return no legal moves
    std::cout << "is not a sliding piece " << std::endl;
    return;
  }
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
    int j = 1;
    while(1) {
      Move move;
      move.fromSquare = startSquare;
      move.toSquare = startSquare+(i*j);
      if(move.toSquare & 0x88) {
        //move is outside of the board
        break;
        }
      j++;
      moveVector.push_back(move);
    }
  }
  return;
}