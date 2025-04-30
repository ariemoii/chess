#pragma once
#include "model/Move.h"
#include "model/Board.h"
#include "MoveGenerator.h"

class MoveMaker {


  private:
    MoveGenerator moveGenerator;
  public:

  private:
    bool isLegalMove(Move *move, std::vector<Move> legalMoveList);

  public: 
    MoveMaker();
    
    void makeMove(Move move, Board* board);
    void tryMakeMove(Move move, Board* board); 
     
};

