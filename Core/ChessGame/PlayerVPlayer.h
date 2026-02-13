#pragma once

#include "ChessGame.h"

#include "model/Board.h"

class PlayerVPlayer : public ChessGame {
  private:
    Board board;


  public:

    PlayerVPlayer();
    void runChess() override;



  private:

  public:




};