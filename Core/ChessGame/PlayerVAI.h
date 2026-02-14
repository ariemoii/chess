#pragma once

#include "ChessGame.h"

#include "controller/MoveMaker.h"

class PlayerVAI : public ChessGame {
  public:

    PlayerVAI();
    void runChess() override;

  private:
    void moveBot(MoveMaker &moveMaker);
};