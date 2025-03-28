#include "Piece_Drawer.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <filesystem>

#define PATH_TO_LICHESS_PIECES "../../../../Assets/Pieces/pieces-basic-png/"
#define PATH_TO_PIECES(piece) PATH_TO_LICHESS_PIECES#piece

Piece_Drawer::Piece_Drawer(sf::RenderWindow *window, int pixelSquareWidth) : 
window(window),
PIXEL_SQUARE_WIDTH(pixelSquareWidth) {
  black_bishop.loadFromFile(PATH_TO_PIECES(black-bishop.png));
  black_king.loadFromFile(PATH_TO_PIECES(black-king.png));
  black_knight.loadFromFile(PATH_TO_PIECES(black-knight.png));
  black_pawn.loadFromFile(PATH_TO_PIECES(black-pawn.png));
  black_queen.loadFromFile(PATH_TO_PIECES(black-queen.png));
  black_rook.loadFromFile(PATH_TO_PIECES(black-rook.png));

  white_pawn.loadFromFile(PATH_TO_PIECES(white-pawn.png));
  white_knight.loadFromFile(PATH_TO_PIECES(white-knight.png));
  white_bishop.loadFromFile(PATH_TO_PIECES(white-bishop.png));
  white_rook.loadFromFile(PATH_TO_PIECES(white-rook.png));
  white_king.loadFromFile(PATH_TO_PIECES(white-king.png));
  white_queen.loadFromFile(PATH_TO_PIECES(white-queen.png));
}

/**
 * draws the piece on the window
 */
void Piece_Drawer::draw_piece(NewPiece::Piece_Type pieceType, NewPiece::Team team, int file, int rank) {
  sf::Sprite sprite(whatTexture(pieceType, team));
  sprite.setScale({0.75f,0.75f});
  sprite.setPosition({rank*PIXEL_SQUARE_WIDTH, file*PIXEL_SQUARE_WIDTH});
  window->draw(sprite);
}

/**
 * Gets the texture of the requested piece
 */
sf::Texture& Piece_Drawer::whatTexture(NewPiece::Piece_Type pieceType, NewPiece::Team team) {
  switch(team) {
    case NewPiece::WHITE:
      switch(pieceType) {
        case NewPiece::PAWN:
          return white_pawn;
        case NewPiece::KNIGHT: 
          return white_knight;
        case NewPiece::KING:
          return white_king;
        case NewPiece::ROOK:
          return white_rook;
        case NewPiece::QUEEN:
          return white_queen;
        case NewPiece::BISHOP:
          return white_bishop;
        default:
          std::cout << "piecetype doesnt exist\n";
      }
      break;
    case NewPiece::BLACK:
      switch(pieceType) {
        case NewPiece::PAWN:
          return black_pawn;
        case NewPiece::KNIGHT: 
          return black_knight;
        case NewPiece::KING:
          return black_king;
        case NewPiece::ROOK:
          return black_rook;
        case NewPiece::QUEEN:
          return black_queen;
        case NewPiece::BISHOP:
          return black_bishop;
        default:
          perror("Piece type doesnt exist");
      }
      break;
    default:
      perror("Team doesnt exist");
  }
}

