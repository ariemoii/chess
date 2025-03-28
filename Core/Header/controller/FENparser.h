#pragma once
#include "NewPiece.h"
#include "NewBoard.h"

#include <string>


/**
 * Class that parser a FEN, and returns a piece list.
 * Source for FEN: https://www.chess.com/terms/fen-chess.
 */
class FENparser {
  public:
    FENparser();
    void parseFenOnBoard(std::string FEN, NewBoard *board);
    std::string requestFEN();

  private:
    NewPiece::Piece_Type pieceTypeFromSymbol(char i);
};