#pragma once
#include "Piece.h"
#include "Board.h"

#include <string>


/**
 * Class that parser a FEN, and returns a piece list.
 * Source for FEN: https://www.chess.com/terms/fen-chess.
 */
class FENparser {
  public:
    FENparser();
    void parseFenOnBoard(std::string FEN, Board *board);
    std::string requestFEN();

  private:
    Piece_Type pieceTypeFromSymbol(char i);
};