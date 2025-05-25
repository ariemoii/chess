#pragma once
#include "model/Move.h"
#include "model/Board.h"

class MoveMaker {


  private:

  public:

  private:
    void handleEP(Move move, Board* board);
    void handleCastling(Move move, Board* board);
    void handlePromotion(Move move, Board* board);
    void updateCastlingRights(Move move, Board* board);

  public: 
    MoveMaker();
    
    void makeMove(Move move, Board* board);
    void unmakeLastMove(Board* board);
};

