#include "MoveMaker.h"
#include <iostream>

MoveMaker::MoveMaker() 
{
  
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
  
  //store the current board state and move
  board->boardStates[board->currentPly].gameState = board->gameState;
  board->boardStates[board->currentPly].playedMove = move;

  //update king locations
  if(piece == (Piece::KING | Piece::WHITE)) {
    board->whiteKingLoc = move.toSquare;
  }
  if(piece == (Piece::KING | Piece::BLACK)) {
    board->blackKingLoc = move.toSquare;
  }

  handleCastling(move, board);

  updateCastlingRights(move, board);

  handlePromotion(move, board);

  handleEP(move, board);

  

  //we need to change the side to move
  board->switchSideToMove();

  //update half-move clock
  board->currentPly++;

  return;
}

void MoveMaker::updateCastlingRights(Move move, Board* board) {
  int rights = GameState::getCastlingRights(board->gameState);
  int kingStartSq = (board->sideToMove == Piece::WHITE) ? 4 : 116;
  int kingSideRookSq = (board->sideToMove == Piece::WHITE) ? 7 : 119;
  int queenSideRookSq = (board->sideToMove == Piece::WHITE) ? 0 : 112;

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

  kingSideRookSq = (board->sideToMove == Piece::WHITE) ? 7 : 119;
  queenSideRookSq = (board->sideToMove == Piece::WHITE) ? 0 : 112;

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
  if(move.isPromoteBishopMove()) {
    board->theBoard[move.toSquare] = board->sideToMove | Piece::BISHOP;
  } else if(move.isPromoteKnightMove()) {
    board->theBoard[move.toSquare] = board->sideToMove | Piece::KNIGHT;
  } else if(move.isPromoteQueenMove()) {
    board->theBoard[move.toSquare] = board->sideToMove | Piece::QUEEN;
  } else if(move.isPromoteRookMove()) {
    board->theBoard[move.toSquare] = board->sideToMove | Piece::ROOK;
  }
}

void MoveMaker::handleCastling(Move move, Board* board) {
  //handle castling moves
  if(move.isCastleKingMove()) {
    board->theBoard[move.fromSquare+3] = 0;
    board->theBoard[move.fromSquare+1] = board->sideToMove | Piece::ROOK;
  }
  if(move.isCastleQueenMove()) {
    board->theBoard[move.fromSquare-4] = 0;
    board->theBoard[move.fromSquare-1] = board->sideToMove | Piece::ROOK;
  }
}

void MoveMaker::handleEP(Move move, Board* board) {
  if(move.isPawnTwoSquaresForwardMove()) {
    //we created en passant opportunity
    int squareBehindPawn = (board->sideToMove == Piece::WHITE) ? move.toSquare-16 : move.toSquare+16;
    if(board->sideToMove == Piece::WHITE) {
      GameState::setEPSquareBlack(squareBehindPawn, board->gameState);
    } else {
      GameState::setEPSquareWhite(squareBehindPawn, board->gameState);
    }
  } else {
    //if we've played en passant
    if(move.isEnPassantMove()) {
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

void MoveMaker::unmakeLastMove(Board* board) {
  if(!board->currentPly) {
    //we cannot unmake move
    std::cout << "tried to unmake move when none have been played\n";
    return;
  }

  //decrement ply count
  (board->currentPly)--;

  //reset move turn
  board->switchSideToMove();

  //restore game state
  board->gameState = board->boardStates[board->currentPly].gameState;

  Move lastMove = board->boardStates[board->currentPly].playedMove;
  int gameStateThen = board->boardStates[board->currentPly].gameState;
  //unplay last move
  board->theBoard[lastMove.fromSquare] = board->theBoard[lastMove.toSquare];
  board->theBoard[lastMove.toSquare] = GameState::getCapturedPiece(gameStateThen);

  //if we promoted, place pawn back
  if(lastMove.getPromotionFlags()) {
    board->theBoard[lastMove.fromSquare] = Piece::PAWN | board->sideToMove;
  }

  //if we played en passant, place pawn back
  if(lastMove.isEnPassantMove()) {
    int squarePawnBack = (board->sideToMove == Piece::WHITE) 
    ? GameState::getEPSquareWhite(gameStateThen)-16 : GameState::getEPSquareBlack(gameStateThen)+16;
    int pawn = (board->sideToMove == Piece::WHITE) ? Piece::PAWN | Piece::BLACK : Piece::PAWN | Piece::WHITE;
    board->theBoard[squarePawnBack] = pawn;
  }

  if(lastMove.isCastleKingMove()) {
    board->theBoard[lastMove.fromSquare+3] = board->sideToMove | Piece::ROOK;
    board->theBoard[lastMove.fromSquare+1] = 0;
  }

  if(lastMove.isCastleQueenMove()) {
    board->theBoard[lastMove.fromSquare-4] = board->sideToMove | Piece::ROOK;
    board->theBoard[lastMove.fromSquare-1] = 0;
  }

  int piece = board->theBoard[lastMove.fromSquare];
  if(piece == (Piece::KING | Piece::WHITE)) {
    board->whiteKingLoc = lastMove.fromSquare;
  }
  if(piece == (Piece::KING | Piece::BLACK)) {
    board->blackKingLoc = lastMove.fromSquare;
  }
} 
