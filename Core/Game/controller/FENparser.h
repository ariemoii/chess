#pragma once
#include "model/Piece.h"
#include "model/Board.h"
#include "model/GameState.h"
#include <vector>
#include <string>


/**
 * Class that parser a FEN, and returns a piece list.
 * Source for FEN: https://www.chess.com/terms/fen-chess.
 */
class FENparser {
  public:
    FENparser();
    void parseFen(std::string FEN, Board *board);
    std::string requestFEN();

  private:
    Piece::PieceType pieceTypeFromSymbol(char i);
    void extractBoardState(std::vector<std::string> words, Board* board);
};