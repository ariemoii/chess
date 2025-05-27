#pragma once
#include "model/Piece.h"
#include "model/GameState.h"
#include "model/Move.h"
#include <iostream>
#include <array>

/**
 * I am using the 0x88 board representation. Reference:
 * https://web.archive.org/web/20071027053053/http://www.brucemo.com/compchess/programming/0x88.htm
 */

struct boardState {
  unsigned int gameState;
  Move playedMove;
};

class Board {
  
  enum TypeGame { HumanVHuman, HumanVAI };

  public:
    std::array<int, 16*8> theBoard = {};
    Piece::Team sideToMove;

    //half-move clock
    int currentPly = 0;

    //array for holding immutable game-states
    //(castling, EPsquares, promotions etc.)
    //for the bit layout, see GameState.h and GameState.cpp
    std::array<boardState, 1024> boardStates;

    unsigned int gameState = 0;
    int blackKingLoc = -1, whiteKingLoc = -1;

  private:
    Piece::Team humanTeam;
    Board::TypeGame typeGame;

  public:
  
    Board();  
    void printBoard();
    void askTeam();
    void askTypeGame();
    void switchSideToMove();
    void switchHumanTeam();
    

    Piece::Team getHumanTeam() { return humanTeam; };

  private:
    
};