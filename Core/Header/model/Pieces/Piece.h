#include <array>
#include <vector>

enum Piece_Type { NIKS = 0, PAWN, KNIGHT, KING, QUEEN, ROOK, BISHOP};
enum Team { NONE = 0, BLACK, WHITE };

struct Point {
  int x, y;
};

class Piece {
  public:

  protected:
    int file;
    int rank;
    Piece_Type pieceType;
    Team team;

  public:
    Piece(Piece_Type pieceType, Team team);
    void setFile(int file) { this->file = file; };
    void setRank(int rank) {this->rank = rank; };
    int getFile() { return file; };
    int getRank() { return rank; };
    Piece_Type getType() { return pieceType; };
    Team getTeam() { return team; };
    std::vector<Point> calcPossibleMoves();
};