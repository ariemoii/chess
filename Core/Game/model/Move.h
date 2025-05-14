#pragma once

struct Move {
  int fromSquare;
  int toSquare;

  bool isCastleKing = false;
  bool isCastleQueen = false;
  bool isPromoteQ = false;
  bool isPromoteB = false;
  bool isPromoteN = false;
  bool isPromoteR = false;
  bool isEnPassant = false;
  bool isKingMove = false;
  bool pawnTwoSquares = false;
  
  bool operator==(const Move& m)  const {
    return fromSquare == m.fromSquare && toSquare == m.toSquare;
  }
};
