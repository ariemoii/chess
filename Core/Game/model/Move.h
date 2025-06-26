#pragma once

struct Move {
  int fromSquare;
  int toSquare;

  //kingCastleMove: bit 1
  //queenCastleMove: bit 2
  //promote Q: bit 3
  //promote B: bit 4
  //promote R: bit 5
  //promote N: bit 6
  //is en passant: bit 7
  //is pawn two square move: bit 8
  unsigned int flags = 0;

  //bit masks
  static constexpr unsigned int CASTLE_KING = 0b1;
  static constexpr unsigned int CASTLE_QUEEN = 0b10;
  static constexpr unsigned int PROMOTE_QUEEN = 0b100;
  static constexpr unsigned int PROMOTE_BISHOP = 0b1000;
  static constexpr unsigned int PROMOTE_ROOK = 0b10000;
  static constexpr unsigned int PROMOTE_KNIGHT = 0b100000;
  static constexpr unsigned int EN_PASSANT = 0b1000000; 
  static constexpr unsigned int PAWN_TWO_SQUARES = 0b10000000;
  static constexpr unsigned int PROMOTION_FLAGS = 0b111100;

  //setters
  void setCastleKingMove() { flags |= CASTLE_KING; }
  void setCastleQueenMove() { flags |= CASTLE_QUEEN; }
  void setPromoteQueen() { flags |= PROMOTE_QUEEN; }
  void setPromoteBishop() { flags |= PROMOTE_BISHOP; }
  void setPromoteRook() { flags |= PROMOTE_ROOK; }
  void setPromoteKnight() { flags |= PROMOTE_KNIGHT; }
  void setIsEnPassant() { flags |= EN_PASSANT; }
  void setPawnTwoSquares() { flags |= PAWN_TWO_SQUARES; }
  void setPromotionFlags(int promFlags) { flags &= ~PROMOTION_FLAGS; flags |= promFlags; }

  //getters
  bool isCastleKingMove() const { return flags & CASTLE_KING; }
  bool isCastleQueenMove() const { return flags & CASTLE_QUEEN; }
  bool isPromoteQueenMove() const { return flags & PROMOTE_QUEEN; }
  bool isPromoteBishopMove() const { return flags & PROMOTE_BISHOP; }
  bool isPromoteRookMove() const { return flags & PROMOTE_ROOK; }
  bool isPromoteKnightMove() const { return flags & PROMOTE_KNIGHT; }
  bool isEnPassantMove() const { return flags & EN_PASSANT; }
  bool isPawnTwoSquaresForwardMove() const { return flags & PAWN_TWO_SQUARES; }
  int getPromotionFlags() const { return flags & PROMOTION_FLAGS; }

  
  bool operator==(const Move& m)  const {
    return fromSquare == m.fromSquare && toSquare == m.toSquare;
  }
};

struct MoveList {
  Move moves[256];
  int count = 0;
  void add(Move move) {
    moves[count] = move;
    count++;
  }

  inline Move operator[](int i) const {
    return moves[i];
  }
  
};