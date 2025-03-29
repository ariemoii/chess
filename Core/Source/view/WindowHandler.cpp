#include "WindowHandler.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

//constructor
WindowHandler::WindowHandler(int screenHeight, int screenWidth) :
SCREEN_WIDTH(screenWidth), 
SCREEN_HEIGHT(screenHeight),
PIXEL_SQUARE_WIDTH(screenWidth/NUM_SQUARES_SIDE),
window(sf::VideoMode({SCREEN_HEIGHT, SCREEN_WIDTH}), "Chess Application", sf::Style::Close | sf::Style::Titlebar),
pieceDrawer(PieceDrawer(&window, PIXEL_SQUARE_WIDTH)) {
  drawBoardBackground();
  //window.display();
}

void WindowHandler::drawSquare(bool isLightSquare, int xCoord, int yCoord) {
  sf::RectangleShape rectangle;
  if(isLightSquare) {
    rectangle.setFillColor(sf::Color(139, 69, 19));
  } else {
    rectangle.setFillColor(sf::Color(250, 240, 230));
  }
  rectangle.setSize(sf::Vector2f(PIXEL_SQUARE_WIDTH, PIXEL_SQUARE_WIDTH));
  rectangle.setPosition({xCoord, yCoord});
  window.draw(rectangle);
}

void WindowHandler::drawBoardBackground() {
  for(int i = 0; i < NUM_SQUARES_SIDE; i++) {
    for(int j = 0; j < NUM_SQUARES_SIDE; j++) {
      int xCoord, yCoord;
      xCoord = PIXEL_SQUARE_WIDTH*j;
      yCoord = PIXEL_SQUARE_WIDTH*i;
      bool isLightSquare;
      if((i+j)%2 == 0) {
        isLightSquare = false;
      } else {
        isLightSquare = true;
      }
      drawSquare(isLightSquare, xCoord, yCoord);
    }
  }
}

void WindowHandler::drawBoard(Board *board, Piece::Team bottomTeam) {
  for(int i = 0; i <8; i++) {
    for(int j = 0; j < 8; j++) {
      if(board->theBoard[i][j] == 0) {
        continue;
      }
      if(bottomTeam == Piece::WHITE) {
        pieceDrawer.drawPiece(Piece::getType(board->theBoard[i][j]), Piece::getTeam(board->theBoard[i][j]), 7-i, 7-j);
      } else {
        pieceDrawer.drawPiece(Piece::getType(board->theBoard[i][j]), Piece::getTeam(board->theBoard[i][j]), i, j);
      }
    }
  }
}

Move WindowHandler::getMove(Square squarePressed) {
  sf::Event event;
  Move move;
  move.fromSquare = squarePressed;
  while(window.waitEvent(event)) {
    if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
      //left mouse button released
      move.toSquare = whatSquare(event.mouseButton.x, event.mouseButton.y);
      break;
    }
  }
  return move;
}

Square WindowHandler::whatSquare(int xCoord, int yCoord) {
  int file, rank;
  file = yCoord/PIXEL_SQUARE_WIDTH;
  rank = xCoord/PIXEL_SQUARE_WIDTH;
  Square sq;
  sq.file = file;
  sq.rank = rank;
  return sq;
}