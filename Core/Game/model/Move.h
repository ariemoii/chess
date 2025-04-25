#pragma once

struct Move {
  int fromSquare;
  int toSquare;
  
  bool operator==(const Move& m)  const {
    return fromSquare == m.fromSquare && toSquare == m.toSquare;
  }
};
