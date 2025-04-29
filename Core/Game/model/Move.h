#pragma once

struct Move {
  int fromSquare;
  int toSquare;

  bool isCastleKing = false;
  bool isCastleQueen = false;
  bool isPromote = false;
  bool isEnPassant = false;

  
  bool operator==(const Move& m)  const {
    return fromSquare == m.fromSquare && toSquare == m.toSquare;
  }
};
