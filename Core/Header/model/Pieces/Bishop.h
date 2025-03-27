#pragma once

#include "Piece.h"

class Bishop : public Piece{
  private:
    const static std::vector<Point> moveSet;
  public:
    Bishop(Team team, int file, int rank);

};