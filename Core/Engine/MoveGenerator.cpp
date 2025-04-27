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
    if(Piece::isType(piece, Piece::KNIGHT)) {
      generateKnightMoves(i, board, pseudoLegalMoves);
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

  //get the correct piece movement table
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
      if(board->theBoard[move.toSquare] != 0) {
        //we are moving onto a piece
        if(isLegalCapture(move, board)) {
          moveVector.push_back(move);
        }
        break;
      }
      j++;
      moveVector.push_back(move);
    }
  }
  return;
}

bool MoveGenerator::isLegalCapture(Move move, Board* board) {
  /**
  * TODO: implement side to move; replace ourTeam variable
  */
  int piece = board->theBoard[move.fromSquare];
  Piece::Team ourTeam = Piece::getTeam(piece);
  int capturePiece = board->theBoard[move.toSquare];
  if(Piece::getTeam(capturePiece) == ourTeam) {
    //we cannot capture our own piece
    return false;
  } else {
    //we are capturing an enemy piece
    return true;
  }
}

void MoveGenerator::generateKnightMoves(int startSquare, Board* board, std::vector<Move>& moveVector) {
  Piece::Team ourTeam = Piece::getTeam(board->theBoard[startSquare]);
  for(const auto &i : moveData.knightMoves) {
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
    if(board->theBoard[move.toSquare] != 0) {
      //we are trying to capture
      if(isLegalCapture(move, board)) {
        moveVector.push_back(move);
      }
      continue;
    }
    moveVector.push_back(move);
  }
  return;
}