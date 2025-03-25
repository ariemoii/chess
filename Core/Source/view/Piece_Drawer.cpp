#include "../../Header/view/Piece_Drawer.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <filesystem>

#define PATH_TO_LICHESS_PIECES "../../../../../Assets/Pieces/pieces-basic-png/"
#define PATH_TO_PIECES(piece) PATH_TO_LICHESS_PIECES#piece

Piece_Drawer::Piece_Drawer() {
  black_bishop.loadFromFile(PATH_TO_PIECES(black-bishop.png));
  black_king.loadFromFile(PATH_TO_PIECES(black_king.png));
  black_knight.loadFromFile(PATH_TO_PIECES(black-knight.png));
  black_pawn.loadFromFile(PATH_TO_PIECES(black-pawn.png));
  black_queen.loadFromFile(PATH_TO_PIECES(black-queen.png));
  black_rook.loadFromFile(PATH_TO_PIECES(black-rook.png));
}

void Piece_Drawer::draw_piece(sf::Texture texture, int xCoord, int yCoord) {
  sf::Sprite sprite(texture);
  sprite.setScale({0.75f,0.75f});
  sprite.setPosition({xCoord, yCoord});
  window->draw(sprite);
}

