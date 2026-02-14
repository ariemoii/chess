#include "ChessGame.h"

#include "view/WindowHandler.h"
#include "model/Board.h"
#include "controller/FENparser.h"

#include <iostream>
#include <string>
#include <unistd.h>  

ChessGame::ChessGame()
  :
    board(initBoard()),
    windowHandler(WindowHandler(SCREEN_WIDTH, SCREEN_HEIGHT)),
    moveGenerator(MoveGenerator())
{};

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

Board ChessGame::initBoard() {
  FENparser parser;
  std::string fen = parser.requestFEN();
  Board board;
  board.askTeam();
  parser.parseFen(fen, &board);
  board.printBoard();
  return board;
}

void ChessGame::printCheckMate(Board &theBoard) {
  if(board.sideToMove == Piece::WHITE) {
    std::cout << "Checkmate! Black wins!\n";
  } else {
    std::cout << "Checkmate! White wins!\n";
  }
  sleep(5);
  windowHandler.window.close();
}