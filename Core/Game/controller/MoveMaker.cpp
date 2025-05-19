#include "MoveMaker.h"

//delete iostream at some point
#include <iostream>

MoveMaker::MoveMaker() : 
moveGenerator(MoveGenerator()){
  
};


void MoveMaker::makeMove(Move move, Board* board) {
  int piece = board->theBoard[move.fromSquare];
  int capturedPiece = board->theBoard[move.toSquare];
  if(piece == 0) {
    //no piece here
    return;
  }
  board->theBoard[move.fromSquare] = 0;
  board->theBoard[move.toSquare] = piece;

  //remember captured piece for unmake move
  GameState::setCapturedPiece(capturedPiece, board->gameState);

  handleCastling(move, board);

  updateCastlingRights(move, board);

  handlePromotion(move, board);

  handleEP(move, board);


  //we need to change the side to move
  if(board->sideToMove == Piece::WHITE) {
    board->sideToMove = Piece::BLACK;
  } else {
    board->sideToMove = Piece::WHITE;
  }

  //update half-move clock
  board->currentPly++;

  return;
}

void MoveMaker::updateCastlingRights(Move move, Board* board) {
  int rights = GameState::getCastlingRights(board->gameState);
  int kingStartSq = (board->sideToMove == Piece::WHITE) ? 3 : 115;
  int kingSideRookSq = (board->sideToMove == Piece::WHITE) ? 0 : 112;
  int queenSideRookSq = (board->sideToMove == Piece::WHITE) ? 7 : 119;

  //we moved the king
  if(move.fromSquare == kingStartSq) {
    if(board->sideToMove == Piece::WHITE) {
      rights &= 0b1100;
      GameState::setCastlingRights(rights, board->gameState);
    } else {
      rights &= 0b0011;
      GameState::setCastlingRights(rights, board->gameState);
    }
  }

  //we moved kingside rook
  if(move.fromSquare == kingSideRookSq) {
    if(board->sideToMove == Piece::WHITE) {
      rights &= 0b1110;
      GameState::setCastlingRights(rights, board->gameState);
    } else {
      rights &= 0b1011;
      GameState::setCastlingRights(rights, board->gameState);
    }
  }

  //we moved queenside rook
  if(move.fromSquare == queenSideRookSq) {
    if(board->sideToMove == Piece::WHITE) {
      rights &= 0b1101;
      GameState::setCastlingRights(rights, board->gameState);
    } else {
      rights &= 0b0111;
      GameState::setCastlingRights(rights, board->gameState);
    }
  }

  kingSideRookSq = (board->sideToMove == Piece::WHITE) ? 112 : 0;
  queenSideRookSq = (board->sideToMove == Piece::WHITE) ? 119 : 7;

  //we've taken kingside rook: update rights accordingly
  if(move.toSquare == kingSideRookSq) {
    if(board->sideToMove == Piece::WHITE) {
      rights &= 0b1011;
      GameState::setCastlingRights(rights, board->gameState);
    } else {
      rights &= 0b1110;
      GameState::setCastlingRights(rights, board->gameState);
    }
  }

  //we've taken queenside rook: update rights accordingly
  if(move.toSquare == queenSideRookSq) {
    if(board->sideToMove == Piece::WHITE) {
      rights &= 0b0111;
      GameState::setCastlingRights(rights, board->gameState);
    } else {
      rights &= 0b1101;
      GameState::setCastlingRights(rights, board->gameState);
    }
  }
}

void MoveMaker::handlePromotion(Move move, Board* board) {
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
}

void MoveMaker::handleCastling(Move move, Board* board) {
  //handle castling moves
  if(move.isCastleKingMove()) {
    board->theBoard[move.fromSquare-3] = 0;
    board->theBoard[move.fromSquare-1] = board->sideToMove | Piece::ROOK;
  }
  if(move.isCastleQueenMove()) {
    board->theBoard[move.fromSquare+4] = 0;
    board->theBoard[move.fromSquare+1] = board->sideToMove | Piece::ROOK;
  }
}

void MoveMaker::handleEP(Move move, Board* board) {
  if(move.pawnTwoSquares) {
    //we created en passant opportunity
    int squareBehindPawn = (board->sideToMove == Piece::WHITE) ? move.toSquare-16 : move.toSquare+16;
    if(board->sideToMove == Piece::WHITE) {
      GameState::setEPSquareBlack(squareBehindPawn, board->gameState);
    } else {
      GameState::setEPSquareWhite(squareBehindPawn, board->gameState);
    }
  } else {
    //if we've played en passant
    if(move.isEnPassant) {
      int sqBehindTarget = (board->sideToMove == Piece::WHITE) ? GameState::getEPSquareWhite(board->gameState)-16 : GameState::getEPSquareBlack(board->gameState)+16;
      //take the pawn behind
      board->theBoard[sqBehindTarget] = 0;
    }

    //remove target en passant square
    if(board->sideToMove == Piece::WHITE) {
      GameState::setEPSquareWhite(0b100000000, board->gameState);
    } else {
      GameState::setEPSquareBlack(0b100000000, board->gameState);
    }
  }
}

void MoveMaker::tryMakeMove(Move move, Board* board) {
  int piece = board->theBoard[move.fromSquare];
  std::vector<Move> pseudoLegalMoves = moveGenerator.generateLegalMoves(board);
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

void MoveMaker::unmakeMove(Move move, Board* board) {

} 
