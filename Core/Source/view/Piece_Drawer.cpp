#include "Piece_Drawer.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>

#define PATH_TO_LICHESS_PIECES "../../../../../Assets/Pieces/pieces-basic-png/"
#define PATH_TO_PIECES(piece) PATH_TO_LICHESS_PIECES#piece

Piece_Drawer::Piece_Drawer(sf::RenderWindow *window, int pixelSquareWidth) : 
window(window),
PIXEL_SQUARE_WIDTH(pixelSquareWidth) {
  black_bishop.loadFromFile(PATH_TO_PIECES(black-bishop.png));
  black_king.loadFromFile(PATH_TO_PIECES(black_king.png));
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
void Piece_Drawer::draw_piece(Piece_Type pieceType, Team team, int xCoord, int yCoord) {
  sf::Sprite sprite(whatTexture(pieceType, team));
  sprite.setScale({0.75f,0.75f});
  sprite.setPosition({xCoord, yCoord});
  window->draw(sprite);
}

void Piece_Drawer::draw_FEN(std::vector<Piece> pieceVector) {
  sf::Vector2u windowSize = window->getSize();
  for(auto &i : pieceVector) {
    int xCoord, yCoord;
    xCoord = PIXEL_SQUARE_WIDTH*i.getFile();
    yCoord =PIXEL_SQUARE_WIDTH*i.getRank();
    draw_piece(i.getType(), i.getTeam(), xCoord, yCoord);
  }
}


/**
 * Gets the texture of the requested piece
 */
sf::Texture Piece_Drawer::whatTexture(Piece_Type pieceType, Team team) {
  switch(team) {
    case WHITE:
      switch(pieceType) {
        case PAWN:
          return white_pawn;
        case KNIGHT: 
          return white_knight;
        case KING:
          return white_king;
        case ROOK:
          return white_rook;
        case QUEEN:
          return white_queen;
        case BISHOP:
          return white_bishop;
        default:
          std::cout << "piecetype doesnt exist\n";
      }
      break;
    case BLACK:
      switch(pieceType) {
        case PAWN:
          return black_pawn;
        case KNIGHT: 
          return black_knight;
        case KING:
          return black_king;
        case ROOK:
          return black_rook;
        case QUEEN:
          return black_queen;
        case BISHOP:
          return black_bishop;
        default:
          perror("Piece type doesnt exist");
      }
      break;
    default:
      perror("Team doesnt exist");
  }
}

