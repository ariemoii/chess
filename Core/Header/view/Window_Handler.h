#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

/**
 * Class that handles the window
 */
class Window_Handler {
  private:
    const int SCREEN_WIDTH;
    static constexpr int NUM_SQUARES_SIDE = 8;
    const int SCREEN_HEIGHT;
    const int PIXEL_SQUARE_WIDTH;
    sf::RenderWindow window;

    /**
     * constructor
     */
  public:
    Window_Handler(int screenHeight, int screenWidth);
  
  private:
    /**
     * display the window
     */
    void display_window();

    /**
     * draw the board on the window
     */
    void draw_board();

    /**
     * draw a square on the board
     */
    void draw_square(bool isLightSquare, int xCoord, int yCoord);

};