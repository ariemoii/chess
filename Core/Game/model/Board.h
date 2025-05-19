#pragma once
#include "model/Piece.h"
#include "model/GameState.h"
#include <iostream>
#include <array>

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
    //where the respective color can en passant to
    //half-move clock
    int currentPly = 0;

    //array for holding immutable game-states
    //(castling, EPsquares, promotions etc.)
    //for the bit layout, see GameState.h and GameState.cpp
    std::array<unsigned int, 1024> boardStates;

    unsigned int gameState = 0;


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