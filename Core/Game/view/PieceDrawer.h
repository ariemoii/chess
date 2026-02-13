#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "model/Piece.h"

class PieceDrawer {

  private:
    sf::RenderWindow* window;

    //textures
    sf::Texture blackKing;
    sf::Texture blackKnight;
    sf::Texture blackBishop;
    sf::Texture blackPawn;
    sf::Texture blackQueen;
    sf::Texture blackRook;
    
    sf::Texture whiteBishop;
    sf::Texture whiteKing;
    sf::Texture whiteKnight;
    sf::Texture whitePawn;
    sf::Texture whiteQueen;
    sf::Texture whiteRook;

    static constexpr int NUM_SQUARES_SIDE = 8;
    const int PIXEL_SQUARE_WIDTH;

  public:
    PieceDrawer(sf::RenderWindow *window, int pixelSquareWidth);
    void drawPiece(Piece::PieceType, Piece::Team, int file, int rank);

  private:
    sf::Texture& whatTexture(Piece::PieceType pieceType, Piece::Team team);
};