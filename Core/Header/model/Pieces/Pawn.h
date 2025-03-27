#pragma once

#include "Piece.h"

class Pawn : public Piece{
  private:
    const static std::vector<Point> moveSet;
  public:
    Pawn(Team team, int file, int rank);

};