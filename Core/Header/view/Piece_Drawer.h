#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

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


  public:
    Piece_Drawer();
    void draw_piece(sf::Texture texture, int xCoord, int yCoord);
};