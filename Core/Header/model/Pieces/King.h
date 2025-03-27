#pragma once

#include "Piece.h"

class King : public Piece{
  private:
    const static std::vector<Point> moveSet;
  public:
    King(Team team, int file, int rank);

};