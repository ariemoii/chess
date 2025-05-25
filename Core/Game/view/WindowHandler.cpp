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
    rectangle.setFillColor(sf::Color(255, 225, 190));
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
  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {
      if(board->theBoard[i*16+j] == 0) {
        continue;
      }
      if(bottomTeam == Piece::WHITE) {
        pieceDrawer.drawPiece(Piece::getType(board->theBoard[i*16+j]), Piece::getTeam(board->theBoard[i*16+j]), j, 7-i);
      } else {
        pieceDrawer.drawPiece(Piece::getType(board->theBoard[i*16+j]), Piece::getTeam(board->theBoard[i*16+j]), 7-j, i);
      }
    }
  }
}

Move WindowHandler::getMove(int squarePressed, Piece::Team humanTeam, Board* board) {
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
  if(humanTeam == Piece::WHITE) {
    //((7*16)+7) is needed because the board is flipped
    //when looking at it from whites perspective
    move.fromSquare = ((7*16)+7)-move.fromSquare;
    move.toSquare = ((7*16)+7)-move.toSquare;
  }
  int promotionRank = (board->sideToMove == Piece::WHITE) ? 7 : 0;
  if(Piece::isType(board->theBoard[move.fromSquare], Piece::PAWN)) {
    //we are moving a pawn
    if(move.toSquare/16 == promotionRank) {
      //we are promoting a pawn
      Piece::PieceType type = getPromotionPiece();
      switch(type) {
        case Piece::ROOK:
          move.setPromoteRook();
          break;
        case Piece::QUEEN:
          move.setPromoteQueen();
          break;
        case Piece::KNIGHT:
          move.setPromoteKnight();
          break;
        case Piece::BISHOP:
          move.setPromoteBishop();
          break;
        default:
          //shouldnt ever reach here
          std::cout << "did not get correct promotion type" << std::endl;
      }
    }
  }
  return move;
}

Piece::PieceType WindowHandler::getPromotionPiece() {
  std::cout << "Please type 'q' for queen, 'n' for knight, 'b' for bisschop, 'r' for rook" << std::endl;
  std::string piece;
  getline(std::cin, piece);
  if(piece[0] == 'q') {
    return Piece::QUEEN;
  }
  if(piece[0] == 'r') {
    return Piece::ROOK;
  }
  if(piece[0] == 'n') {
    return Piece::KNIGHT;
  }
  if(piece[0] == 'b') {
    return Piece::BISHOP;
  }
  std::cout << "invalid choice lil bro" << std::endl;
  return getPromotionPiece();
}

int WindowHandler::whatSquare(int xCoord, int yCoord) {
  int file, rank;
  file = xCoord/PIXEL_SQUARE_WIDTH;
  rank = yCoord/PIXEL_SQUARE_WIDTH;
  int sq = rank*16 + 7-file;
  return sq;
}