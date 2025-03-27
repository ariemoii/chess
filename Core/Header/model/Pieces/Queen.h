#pragma once

#include "Piece.h"

class Queen : public Piece{
  private:
    const static std::vector<Point> moveSet;
  public:
    Queen(Team team, int file, int rank);

};