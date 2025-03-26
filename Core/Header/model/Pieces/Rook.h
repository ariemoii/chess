#include "Piece.h"

class Rook : public Piece{
  private:
    const static std::vector<Point> moveSet;
  public:
    Rook(Team team);

};