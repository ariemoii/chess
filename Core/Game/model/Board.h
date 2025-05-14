#pragma once
#include "model/Piece.h"
#include <iostream>

/**
 * I am using the 0x88 board representation. Reference:
 * https://web.archive.org/web/20071027053053/http://www.brucemo.com/compchess/programming/0x88.htm
 */

class Board {
  
  enum TypeGame { HumanVHuman, HumanVAI };

  public:
    static int theBoard[16*8];
    Piece::Team sideToMove;

    //least sig bit for kingside castling, second for queenside castling
    int blackCastleRights, whiteCastleRights;

    //where the respective color can en passant to
    int epSqWhite = -1, epSqBlack = -1;

  private:
    Piece::Team humanTeam;
    Board::TypeGame typeGame;

  public:
  
    Board();  
    void printBoard();
    void askTeam();
    void askTypeGame();

    Piece::Team getHumanTeam() { return humanTeam; };
};