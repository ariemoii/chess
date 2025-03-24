#include "../Header/Window_Handler.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

//constructor
Window_Handler::Window_Handler(int screenHeight, int screenWidth) :
SCREEN_WIDTH(screenWidth), 
SCREEN_HEIGHT(screenHeight),
window(sf::VideoMode({SCREEN_HEIGHT, SCREEN_WIDTH}), "Chess Application", sf::Style::Close | sf::Style::Titlebar) {
  display_window();
}




void Window_Handler::display_window() {
  sf::Event event;
  while(window.isOpen()) {
    //draw frame
    window.clear(sf::Color::Green);
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


