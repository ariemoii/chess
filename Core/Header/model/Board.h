#pragma once
#include "Piece.h"
#include <iostream>



class Board {
  
  enum TypeGame { HumanVHuman, HumanVAI };

  public:
    static int theBoard[8][8];

  private:
    Piece::Team humanTeam;
    Board::TypeGame typeGame;

  public:
  
    Board();  
    void printBoard();
    void askTeam();
    void askTypeGame();

    Piece::Team getHumanTeam() { return humanTeam; };

    //make a 'flip board' function: if human v human,
    //white make move, flip board so black can make move.
};