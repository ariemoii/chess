#include "../../Header/view/Window_Handler.h"
#include "../../Header/view/Piece_Drawer.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

//constructor
Window_Handler::Window_Handler(int screenHeight, int screenWidth) :
SCREEN_WIDTH(screenWidth), 
SCREEN_HEIGHT(screenHeight),
PIXEL_SQUARE_WIDTH(screenWidth/NUM_SQUARES_SIDE),
window(sf::VideoMode({SCREEN_HEIGHT, SCREEN_WIDTH}), "Chess Application", sf::Style::Close | sf::Style::Titlebar) {
  display_window();
}

void Window_Handler::display_window() {
  sf::Event event;
  while(window.isOpen()) {
    //draw frame
    window.clear(sf::Color::Green);
    draw_board();
    window.display();

    //frame logic
    while(window.waitEvent(event)) {

      //check if window closed
      switch(event.type) {
        case sf::Event::Closed:
          window.close();
          return;
      }
    }
    
    //clear frame
    window.clear(sf::Color::Green);
  }
}

void Window_Handler::draw_square(bool isLightSquare, int xCoord, int yCoord) {
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

void Window_Handler::draw_board() {
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
      draw_square(isLightSquare, xCoord, yCoord);
    }
  }
}

