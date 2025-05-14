#include "MoveMaker.h"

//delete iostream at some point
#include <iostream>

MoveMaker::MoveMaker() : 
moveGenerator(MoveGenerator()){
  
};


void MoveMaker::makeMove(Move move, Board* board) {
  int piece = board->theBoard[move.fromSquare];
  if(piece == 0) {
    //no piece here
    return;
  }
  board->theBoard[move.fromSquare] = 0;
  board->theBoard[move.toSquare] = piece;

  //handle castling moves
  if(move.isCastleKing) {
    board->theBoard[move.fromSquare-3] = 0;
    board->theBoard[move.fromSquare-1] = board->sideToMove | Piece::ROOK;
  }
  if(move.isCastleQueen) {
    board->theBoard[move.fromSquare+4] = 0;
    board->theBoard[move.fromSquare+1] = board->sideToMove | Piece::ROOK;
  }
  if(move.isCastleKing || move.isCastleQueen || move.isKingMove) {
    //revoke this colors castling rights
    if(board->sideToMove == Piece::WHITE) {
      board->whiteCastleRights = 0;
    } else {
      board->blackCastleRights = 0;
    }
  }

  //handle promotion
  if(move.isPromoteB) {
    board->theBoard[move.toSquare] = board->sideToMove | Piece::BISHOP;
  } else if(move.isPromoteN) {
    board->theBoard[move.toSquare] = board->sideToMove | Piece::KNIGHT;
  } else if(move.isPromoteQ) {
    board->theBoard[move.toSquare] = board->sideToMove | Piece::QUEEN;
  } else if(move.isPromoteR) {
    board->theBoard[move.toSquare] = board->sideToMove | Piece::ROOK;
  }

  handleEP(move, board);


  //we need to change the side to move
  if(board->sideToMove == Piece::WHITE) {
    board->sideToMove = Piece::BLACK;
  } else {
    board->sideToMove = Piece::WHITE;
  }

  return;
}

void MoveMaker::handleEP(Move move, Board* board) {
  if(move.pawnTwoSquares) {
    //we created en passant opportunity
    int squareBehindPawn = (board->sideToMove == Piece::WHITE) ? move.toSquare-16 : move.toSquare+16;
    if(board->sideToMove == Piece::WHITE) {
      board->epSqBlack = squareBehindPawn;
    } else {
      board->epSqWhite = squareBehindPawn;
    }
  } else {
    //if we've played en passant
    if(move.isEnPassant) {
      int sqBehindTarget = (board->sideToMove == Piece::WHITE) ? board->epSqWhite-16 : board->epSqBlack+16;
      //take the pawn behind
      board->theBoard[sqBehindTarget] = 0;
    }

    //remove target en passant square
    if(board->sideToMove == Piece::WHITE) {
      board->epSqWhite = -1;
    } else {
      board->epSqBlack = -1;
    }
  }
}

void MoveMaker::tryMakeMove(Move move, Board* board) {
  int piece = board->theBoard[move.fromSquare];
  std::vector<Move> pseudoLegalMoves = moveGenerator.generatePseudolegalMoves(board);
  if(isLegalMove(&move, pseudoLegalMoves)) {
    std::cout << "move is legal " << std::endl;
    makeMove(move, board);
  } else {
    std::cout << "move is NOT legal " << std::endl;
  }
  std::cout << "square " << move.fromSquare << std::endl;
}

bool MoveMaker::isLegalMove(Move *move, std::vector<Move> moveList) {
  for(auto i : moveList) {
    if(i == *move) {
      i.isPromoteB = (*move).isPromoteB;
      i.isPromoteN = (*move).isPromoteN;
      i.isPromoteQ = (*move).isPromoteQ;
      i.isPromoteR = (*move).isPromoteR;
      *move = i;
      return true;
    }
  }
  return false;
}

