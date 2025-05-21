#include "Piece.h"

bool Piece::isType(int piece, Piece::PieceType type) {
  int pieceType = piece & 0b111;
  return pieceType == type;
}

bool Piece::isTeam(int piece, Piece::Team team) {
  int pieceTeam = piece & 0b11000;
  return pieceTeam == team;
}

Piece::Team Piece::getTeam(int piece) {
  if(isTeam(piece, Piece::WHITE)) {
    return Piece::WHITE;
  }
  if(isTeam(piece, Piece::BLACK)) {
    return Piece::BLACK;
  }
  return Piece::NONE;
}

Piece::PieceType Piece::getType(int piece) {
  if(isType(piece, Piece::PAWN)) {
    return Piece::PAWN;
  }
  if(isType(piece, Piece::KING)) {
    return Piece::KING;
  }
  if(isType(piece, Piece::KNIGHT)) {
    return Piece::KNIGHT;
  }
  if(isType(piece, Piece::BISHOP)) {
    return Piece::BISHOP;
  }
  if(isType(piece, Piece::ROOK)) {
    return Piece::ROOK;
  }
  if(isType(piece, Piece::QUEEN)) {
    return Piece::QUEEN;
  }
  return Piece::NIKS;
}

bool Piece::isSlidingPiece(int piece) {
  return isType(piece, Piece::BISHOP) || isType(piece, Piece::ROOK) || isType(piece, Piece::QUEEN);
}
