#include "PseudoLegalMoveGenerator.h"

PseudoLegalMoveGenerator::PseudoLegalMoveGenerator() :
moveData(MoveData())
{ 
};


std::vector<Move> PseudoLegalMoveGenerator::generatePseudolegalMoves(Board* board) {
  //16*8 is the size of the board
  std::vector<Move> pseudoLegalMoves;
  for(int i = 0; i < 16*8; i++) {
    int piece = board->theBoard[i];
    if(!Piece::isTeam(piece, board->sideToMove)) continue;
    if(Piece::isSlidingPiece(piece)) {
      generateSlidingPieceMoves(i, Piece::getType(piece), board, pseudoLegalMoves);
    } else if(Piece::isType(piece, Piece::KNIGHT)) {
      generateKnightMoves(i, board, pseudoLegalMoves);
    } else if(Piece::isType(piece, Piece::KING)) {
      generateKingMoves(i, board, pseudoLegalMoves);
    } else if(Piece::isType(piece, Piece::PAWN)) {
      generatePawnMoves(i, board, pseudoLegalMoves);
    }
  }
  return pseudoLegalMoves;
}

void PseudoLegalMoveGenerator::generateSlidingPieceMoves(int startSquare, Piece::PieceType type, Board* board, std::vector<Move>& moveVector) {
  int piece = board->theBoard[startSquare];
  std::array<int, 64> slidingArray;
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
      if(board->theBoard[move.toSquare]) {
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

bool PseudoLegalMoveGenerator::isLegalCapture(Move move, Board* board) {
  int piece = board->theBoard[move.fromSquare];
  Piece::Team ourTeam = board->sideToMove;
  int capturePiece = board->theBoard[move.toSquare];
  if(Piece::getTeam(capturePiece) == ourTeam) {
    //we cannot capture our own piece
    return false;
  } else {
    //we are capturing an enemy piece
    return true;
  }
}

void PseudoLegalMoveGenerator::generateKnightMoves(int startSquare, Board* board, std::vector<Move>& moveVector) {
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
    if(board->theBoard[move.toSquare]) {
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

void PseudoLegalMoveGenerator::generateKingMoves(int startSquare, Board* board, std::vector<Move>& moveVector) {
  for(auto &i : moveData.kingMoves) {
    if(i == 0) {
      break;
    }
    Move moveNormal;
    moveNormal.fromSquare = startSquare;
    moveNormal.toSquare = startSquare+i;
    if(moveNormal.toSquare & 0x88) {
      //move is outside of the board
      continue;
    }
    if(board->theBoard[moveNormal.toSquare]) {
      //we are trying to capture
      if(isLegalCapture(moveNormal, board)) {
        moveVector.push_back(moveNormal);
      }
      continue;
    }
    moveVector.push_back(moveNormal);

    //castling moves
    int castlingRights = (board->sideToMove == Piece::WHITE) ? GameState::getCastlingRights(board->gameState) : (GameState::getCastlingRights(board->gameState) >> 2);
    if(castlingRights & 0b01 && (!(startSquare-2 & 0x88))) {
      //we have kingside castling rights
      if(!board->theBoard[startSquare-1] && !board->theBoard[startSquare-2]) {
        //there are no pieces in the way
        Move moveCastling = { startSquare, startSquare-2 };
        //moveCastling.isCastleKing = true;
        moveCastling.setCastleKingMove();
        moveVector.push_back(moveCastling);
      }
    }
    if(castlingRights & 0b10 && (!(startSquare+2 & 0x88))) {
      //we have queenside castling rights
      if(!board->theBoard[startSquare+1] && !board->theBoard[startSquare+2]) {
        //there are no pieces in the way
        Move move = { startSquare, startSquare+2 };
        //move.isCastleQueen = true;
        move.setCastleQueenMove();
        moveVector.push_back(move);
      }
    }
  }
  return;
}

void PseudoLegalMoveGenerator::generatePawnMoves(int startSquare, Board* board, std::vector<Move>& moveVector) {
  Piece::Team sideToMove = board->sideToMove;
  int startRank = (sideToMove == Piece::WHITE) ? 1 : 6;
  int promotionRank = (sideToMove == Piece::WHITE) ? 7 : 0;
  int dirOffset = (sideToMove == Piece::WHITE) ? MoveData::N : MoveData::S;
  int currRank = startSquare >> 4;
  

  //forward moves
  Move move1 = {startSquare, startSquare+dirOffset};
  Move move2 = { startSquare, startSquare+dirOffset*2 };
  if((!board->theBoard[move1.toSquare]) && (!(0x88 & (move1.toSquare)))) {
    //there is no piece in the way
    //and move is not out of the board
    if(move1.toSquare/16 == promotionRank) {
      //we can promote
      generatePromotionMoves(moveVector, move1);
    } else {
      moveVector.push_back(move1);
    }
  }
  if(startRank == currRank && (!board->theBoard[move2.toSquare]) && (!board->theBoard[move1.toSquare]) 
    && (!(0x88 & (move2.toSquare)))) {
    //we are on start rank
    //there is no piece in the way
    //move is not out of board
    move2.setPawnTwoSquares();
    moveVector.push_back(move2);
  }

  //capture moves
  Move cap1 = { startSquare, startSquare+dirOffset-1 };
  Move cap2 = { startSquare, startSquare+dirOffset+1 };
  if((!(cap1.toSquare & 0x88)) && board->theBoard[cap1.toSquare]) {
    //we can capture to one side
    if(isLegalCapture(cap1, board)) {
      //we can promote
      if(cap1.toSquare/16 == promotionRank) {
        generatePromotionMoves(moveVector, cap1);
      } else {
        moveVector.push_back(cap1);
      }
    }
  } else if(!(cap1.toSquare & 0x88)) {
    //check for en passant opportunity
    int epTargetSq = (board->sideToMove == Piece::WHITE) ? GameState::getEPSquareWhite(board->gameState) : GameState::getEPSquareBlack(board->gameState);
    if(cap1.toSquare == epTargetSq) {
      cap1.setIsEnPassant();
      moveVector.push_back(cap1);
    }
  }

  if((!(cap2.toSquare & 0x88)) && board->theBoard[cap2.toSquare]) {
    //we can capture to the other side
    if(isLegalCapture(cap2, board)) {
      if(cap2.toSquare == promotionRank) {
        //we can promote
        generatePromotionMoves(moveVector, cap2);
      } else {
        moveVector.push_back(cap2);
      }
    }
  } else if(!(cap1.toSquare & 0x88)) {
    //check for en passant opportunity
    int epTargetSq = (board->sideToMove == Piece::WHITE) ? GameState::getEPSquareWhite(board->gameState) : GameState::getEPSquareBlack(board->gameState);
    if(cap2.toSquare == epTargetSq) {
      cap2.setIsEnPassant();
      moveVector.push_back(cap2);
    }
  }
}

void PseudoLegalMoveGenerator::generatePromotionMoves(std::vector<Move>& moveVector, Move move) {
  std::vector<Move> promMoves(4, move);
  promMoves[0].setPromoteBishop();
  promMoves[1].setPromoteQueen();
  promMoves[2].setPromoteKnight();
  promMoves[3].setPromoteRook();
  moveVector.insert(moveVector.end(), promMoves.begin(), promMoves.end());
}

