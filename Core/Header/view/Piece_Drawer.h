#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "NewPiece.h"

class Piece_Drawer {

  

  private:
    sf::RenderWindow* window;

    sf::Texture black_king;
    sf::Texture black_knight;
    sf::Texture black_bishop;
    sf::Texture black_pawn;
    sf::Texture black_queen;
    sf::Texture black_rook;
    
    sf::Texture white_bishop;
    sf::Texture white_king;
    sf::Texture white_knight;
    sf::Texture white_pawn;
    sf::Texture white_queen;
    sf::Texture white_rook;

    static constexpr int NUM_SQUARES_SIDE = 8;
    const int PIXEL_SQUARE_WIDTH;

  public:
    Piece_Drawer(sf::RenderWindow *window, int pixelSquareWidth);
    void draw_piece(NewPiece::Piece_Type, NewPiece::Team, int file, int rank);

  private:
    sf::Texture& whatTexture(NewPiece::Piece_Type pieceType, NewPiece::Team team);
};