#include "Chess_Game.h"
#include "Window_Handler.h"
#include "FENparser.h"
#include "Board.h"

#include <iostream>

#define SCREEN_HEIGHT 800
#define SCREEN_WIDTH 800

Chess_Game::Chess_Game(){};

/**
 * main function
 */
void Chess_Game::run_chess() {
  
  FENparser parser;
  std::string fen = parser.requestFEN();
  Board board;
  board.initBoard();
  parser.parseFenOnBoard(fen, &board);
  board.printBoard();
  Window_Handler windowHandler(SCREEN_WIDTH, SCREEN_HEIGHT);
  //main loop
  sf::Event event;
  while(windowHandler.window.isOpen()) {
    while(windowHandler.window.waitEvent(event)) {
      if(event.type == sf::Event::Closed) {
        windowHandler.window.close();
        break;
      }

      if(event.type == sf::Event::KeyPressed) {
        if(event.key.code == sf::Keyboard::A) {
          std::cout << "updating window..\n";
        }
      }

      windowHandler.window.clear();
      windowHandler.draw_board_background();
      windowHandler.draw_board(&board);
      windowHandler.window.display();
    }

    
  }
}