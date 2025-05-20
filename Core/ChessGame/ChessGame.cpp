#include "ChessGame.h"

#define SCREEN_HEIGHT 800
#define SCREEN_WIDTH 800

ChessGame::ChessGame(){};

/**
 * main function
 */
void ChessGame::runChess() {
  
  FENparser parser;
  std::string fen = parser.requestFEN();
  Board board;
  board.askTeam();
  parser.parseFen(fen, &board);
  board.printBoard();
  WindowHandler windowHandler(SCREEN_WIDTH, SCREEN_HEIGHT);
  MoveMaker moveMaker;
  sf::Event event;
  MoveGenerator moveGenerator;

  //main loop for human v human game
  while(windowHandler.window.isOpen()) {
    while(windowHandler.window.waitEvent(event)) {
      if(event.type == sf::Event::Closed) {
        windowHandler.window.close();
        break;
      }

      if(event.type == sf::Event::MouseButtonPressed) {
        if(event.mouseButton.button == sf::Mouse::Left) {
          //left mouse button has been pressed
          int pressedSquare = windowHandler.whatSquare(event.mouseButton.x, event.mouseButton.y);
          Move move = windowHandler.getMove(pressedSquare, board.getHumanTeam(), &board);
          std::vector<Move> moveList = moveGenerator.generateLegalMoves(&board);
          for(auto i : moveList) {
            if(i == move) {
              //move is legal
              i.setPromotionFlags(move.getPromotionFlags());
              move = i;
              moveMaker.makeMove(move, &board);
              break;
            }
          }
        }
      }
      if(event.type == sf::Event::KeyPressed) {
        if(event.key.code == sf::Keyboard::U) {
          moveMaker.unmakeLastMove(&board);
        }
      }

      renderAll(&windowHandler, &board);
    }
  }
}

void ChessGame::renderAll(WindowHandler* windowHandler, Board* board) {
  windowHandler->window.clear();
  windowHandler->drawBoardBackground();
  windowHandler->drawBoard(board, board->getHumanTeam());
  windowHandler->window.display();
}