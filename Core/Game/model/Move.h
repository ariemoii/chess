#pragma once

struct Move {
  int fromSquare;
  int toSquare;
  bool isEnPassant = false;
  bool pawnTwoSquares = false;

  //kingCastleMove: bit 1
  //queenCastleMove: bit 2
  //promote Q: bit 3
  //promote B: bit 4
  //promote R: bit 5
  //promote N: bit 6
  //is en passant: bit 7
  //is pawn two square move: bit 8
  unsigned int flags = 0;

  //setters
  void setCastleKingMove() { flags |= 0b1; }
  void setCastleQueenMove() { flags |= 0b10; }
  void setPromoteQueen() { flags |= 0b100; }
  void setPromoteBishop() { flags |= 0b1000; }
  void setPromoteRook() { flags |= 0b10000; }
  void setPromoteKnight() { flags |= 0b100000; }
  void setIsEnPassant() { flags |= 0b1000000; }
  void setPawnTwoSquares() { flags |= 0b10000000; }

  //getters
  bool isCastleKingMove() const { return flags & 0b1; }
  bool isCastleQueenMove() const { return flags & 0b10; }
  bool isPromoteQueenMove() const { return flags & 0b100; }
  bool isPromoteBishopMove() const { return flags & 0b1000; }
  bool isPromoteRookMove() const { return flags & 0b10000; }
  bool isPromoteKnightMove() const { return flags & 0b100000; }
  bool isEnPassantMove() const { return flags & 0b1000000; }
  bool isPawnTwoSquaresForwardMove() const { return flags & 0b10000000; }
  int getPromotionFlags() const { return flags & 0b111100; }

  
  bool operator==(const Move& m)  const {
    return fromSquare == m.fromSquare && toSquare == m.toSquare;
  }
};