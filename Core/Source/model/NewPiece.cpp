#include "NewPiece.h"

NewPiece::NewPiece(){};

bool NewPiece::isType(int piece, NewPiece::Piece_Type type) {
  int pieceType = piece & 0b111;
  return pieceType == type;
}

bool NewPiece::isTeam(int piece, NewPiece::Team team) {
  int pieceTeam = piece & 0b11000;
  return pieceTeam == team;
}

NewPiece::Team NewPiece::getTeam(int piece) {
  if(isTeam(piece, NewPiece::WHITE)) {
    return NewPiece::WHITE;
  }
  if(isTeam(piece, NewPiece::BLACK)) {
    return NewPiece::BLACK;
  }
  return NewPiece::NONE;
}

NewPiece::Piece_Type NewPiece::getType(int piece) {
  if(isType(piece, NewPiece::PAWN)) {
    return NewPiece::PAWN;
  }
  if(isType(piece, NewPiece::KING)) {
    return NewPiece::KING;
  }
  if(isType(piece, NewPiece::KNIGHT)) {
    return NewPiece::KNIGHT;
  }
  if(isType(piece, NewPiece::BISHOP)) {
    return NewPiece::BISHOP;
  }
  if(isType(piece, NewPiece::ROOK)) {
    return NewPiece::ROOK;
  }
  if(isType(piece, NewPiece::QUEEN)) {
    return NewPiece::QUEEN;
  }
  return NewPiece::NIKS;
}