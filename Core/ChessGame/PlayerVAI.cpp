#include "PlayerVAI.h"
#include "AI/Search.h"
#include <unistd.h>  

PlayerVAI::PlayerVAI()
{

}

void PlayerVAI::runChess() {
  FENparser parser;
  std::string fen = parser.requestFEN();
  Board board;
  board.askTeam();
  parser.parseFen(fen, &board);
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

      if(board.sideToMove != board.getHumanTeam()) {
        //time for the bot to move!
        std::cout << "finding best move" << std::endl;
        Move move = bestMove(&board);
        std::cout << "best move = " << (MoveData::intToSquare(move.fromSquare)) << (MoveData::intToSquare(move.toSquare)) << '\n';
        moveMaker.makeMove(move, &board);
        renderAll(&windowHandler, &board);
        if(moveGenerator.isCheckMate(&board)) {
          if(board.sideToMove == Piece::WHITE) {
            std::cout << "Checkmate! Black wins!\n";
          } else {
            std::cout << "Checkmate! White wins!\n";
          }
          sleep(5);
          windowHandler.window.close();
        }
      }

      if(event.type == sf::Event::MouseButtonPressed) {
        if(event.mouseButton.button == sf::Mouse::Left) {
          //left mouse button has been pressed
          if(board.sideToMove != board.getHumanTeam()) {
            continue;
          }
          int pressedSquare = windowHandler.whatSquare(event.mouseButton.x, event.mouseButton.y);
          Move move = windowHandler.getMove(pressedSquare, board.getHumanTeam(), &board);
          std::cout << "Square = " << move.fromSquare;
          std::cout << " = " << MoveData::intToSquare(move.fromSquare) << "\n";
          std::vector<Move> moveList;
          moveGenerator.generateLegalMoves(&board, moveList);
          bool legal = false;
          for(auto i : moveList) {
            if(i == move) {
              legal = true;
              //move is legal
              i.setPromotionFlags(move.getPromotionFlags());
              move = i;
              Piece::Team ourTeam = board.sideToMove;
              moveMaker.makeMove(move, &board);
              if(moveGenerator.isCheckMate(&board)) {
                if(board.sideToMove == Piece::WHITE) {
                  std::cout << "Checkmate! Black wins!\n";
                } else {
                  std::cout << "Checkmate! White wins!\n";
                }
                windowHandler.window.close();
              }
              break;
            }
          }
        }
      }
      if(event.type == sf::Event::KeyPressed) {
        if(event.key.code == sf::Keyboard::U) {
          moveMaker.unmakeLastMove(&board);
          moveMaker.unmakeLastMove(&board);
        }
      }

      renderAll(&windowHandler, &board);
    }
  }
}