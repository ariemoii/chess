#include "Perft.h"

Perft::Perft() :
fenParser(FENparser()),
moveGenerator(MoveGenerator()),
board(Board()),
moveMaker(MoveMaker())
{
  testFEN = fenParser.requestFEN();
  fenParser.parseFen(testFEN, &board);
}

int Perft::runPerft(int depth, int maxDepth) {
  if(depth <= 0) {
    return 1;
  }
  std::vector<Move> moves = moveGenerator.generateLegalMoves(&board);
  int numPos = 0;
  for(Move move : moves) {
    moveMaker.makeMove(move, &board);
    int nodes = runPerft(depth-1, maxDepth);
    numPos += nodes;
    moveMaker.unmakeLastMove(&board);
    if(depth==maxDepth) {
      std::cout << MoveData::intToSquare(move.fromSquare) << MoveData::intToSquare(move.toSquare) 
      << " " << nodes << " flag = " << move.flags << "\n";
    }
  }
  
  return numPos;
}