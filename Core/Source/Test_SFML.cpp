#include "../Header/Test_SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp> 
#include <optional>


void display_window() {
  sf::RenderWindow window(sf::VideoMode(800, 800), "Chess Application", sf::Style::Close | sf::Style::Titlebar );
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
