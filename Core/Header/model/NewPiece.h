#pragma once


class NewPiece {
  //5 bit integer will tell us the piece: 3 least sig. bits = piece, 2 most sig. bits = team
  public:
    enum Piece_Type { NIKS = 0, PAWN = 1, KNIGHT = 2, KING = 3, QUEEN = 4, ROOK = 5, BISHOP = 6};
    enum Team { NONE = 0, BLACK = 16, WHITE = 8};

  public:
    NewPiece();
    static Piece_Type getType(int piece);
    static Team getTeam(int piece);
    static bool isType(int piece, Piece_Type pieceType);
    static bool isTeam(int piece, Team team);

  private:
    
};