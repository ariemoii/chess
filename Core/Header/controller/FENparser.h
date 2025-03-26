#include "../model/Pieces/Piece.h"
#include <string>


/**
 * Class that parser a FEN, and returns a piece list.
 * Source for FEN: https://www.chess.com/terms/fen-chess.
 */
class FENparser {
  public:
    FENparser();
    std::vector<Piece> parseFEN(std::string FEN);
    std::string requestFEN();

  private:
    Piece_Type pieceTypeFromSymbol(char i);
};