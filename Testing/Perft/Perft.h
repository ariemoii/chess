#pragma once

#include "model/Board.h"
#include "MoveGenerator.h"
#include "controller/FENparser.h"
#include "model/Move.h"
#include "controller/MoveMaker.h"
#include "MoveData.h"

#include <iostream>
#include <string>
#include <vector>

class Perft {
  public:
    Perft();
    int runPerft(int depth, int maxDepth);

  private:
    MoveGenerator moveGenerator;
    FENparser fenParser;
    std::string testFEN;
    Board board;
    MoveMaker moveMaker;


  public:


  private:

  
};