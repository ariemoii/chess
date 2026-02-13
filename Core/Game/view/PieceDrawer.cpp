#include "PieceDrawer.h"

//#include <SFML/Graphics.hpp>
//#include <SFML/Window.hpp>

#include <iostream>
#include <filesystem>

#include "model/Piece.h"

#define PATH_TO_LICHESS_PIECES "../../../../Assets/Pieces/pieces-basic-png/"
#define PATH_TO_PIECES(piece) PATH_TO_LICHESS_PIECES#piece

PieceDrawer::PieceDrawer(sf::RenderWindow *window, int pixelSquareWidth) : 
window(window),
PIXEL_SQUARE_WIDTH(pixelSquareWidth) {
  blackBishop.loadFromFile(PATH_TO_PIECES(black-bishop.png));
  blackKing.loadFromFile(PATH_TO_PIECES(black-king.png));
  blackKnight.loadFromFile(PATH_TO_PIECES(black-knight.png));
  blackPawn.loadFromFile(PATH_TO_PIECES(black-pawn.png));
  blackQueen.loadFromFile(PATH_TO_PIECES(black-queen.png));
  blackRook.loadFromFile(PATH_TO_PIECES(black-rook.png));

  whitePawn.loadFromFile(PATH_TO_PIECES(white-pawn.png));
  whiteKnight.loadFromFile(PATH_TO_PIECES(white-knight.png));
  whiteBishop.loadFromFile(PATH_TO_PIECES(white-bishop.png));
  whiteRook.loadFromFile(PATH_TO_PIECES(white-rook.png));
  whiteKing.loadFromFile(PATH_TO_PIECES(white-king.png));
  whiteQueen.loadFromFile(PATH_TO_PIECES(white-queen.png));
}

/**
 * draws the piece on the window
 */
void PieceDrawer::drawPiece(Piece::PieceType pieceType, Piece::Team team, int file, int rank) {
  sf::Sprite sprite(whatTexture(pieceType, team));
  sprite.setScale({0.75f,0.75f});
  sprite.setPosition({file*PIXEL_SQUARE_WIDTH, rank*PIXEL_SQUARE_WIDTH});
  window->draw(sprite);
}

/**
 * Gets the texture of the requested piece
 */
sf::Texture& PieceDrawer::whatTexture(Piece::PieceType pieceType, Piece::Team team) {
  switch(team) {
    case Piece::WHITE:
      switch(pieceType) {
        case Piece::PAWN:
          return whitePawn;
        case Piece::KNIGHT: 
          return whiteKnight;
        case Piece::KING:
          return whiteKing;
        case Piece::ROOK:
          return whiteRook;
        case Piece::QUEEN:
          return whiteQueen;
        case Piece::BISHOP:
          return whiteBishop;
        default:
          std::cout << "piecetype doesnt exist\n";
      }
      break;
    case Piece::BLACK:
      switch(pieceType) {
        case Piece::PAWN:
          return blackPawn;
        case Piece::KNIGHT: 
          return blackKnight;
        case Piece::KING:
          return blackKing;
        case Piece::ROOK:
          return blackRook;
        case Piece::QUEEN:
          return blackQueen;
        case Piece::BISHOP:
          return blackBishop;
        default:
          std::cerr << "Piece type doesnt exis\n";
      }
      break;
    default:
      std::cerr << "Team doesnt exist\n";
  }
}

