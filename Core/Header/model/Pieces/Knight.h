#pragma once

#include "Piece.h"

class Knight : public Piece{
  private:
    const static std::vector<Point> moveSet;
  public:
    Knight(Team team, int file, int rank);

};