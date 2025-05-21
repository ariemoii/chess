#include "ChessGame.h"

ChessGame::ChessGame(){};

/**
 * main function
 */
void ChessGame::runChess() {
  
}

void ChessGame::renderAll(WindowHandler* windowHandler, Board* board) {
  windowHandler->window.clear();
  windowHandler->drawBoardBackground();
  windowHandler->drawBoard(board, board->getHumanTeam());
  windowHandler->window.display();
}