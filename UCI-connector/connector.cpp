#include "lichess-bot.h"
#include <iostream>
#include "model/Board.h"

int main() {
  std::string message;
  getline(std::cin, message);
  Board board;
  
  while(message != "quit") {
    if(message == "uci") {
      respond("uciok");
    } else if(message == "isready") {
      respond("readyok");
    } else if(message == "ucinewgame") ;
    if(message.find("position") != std::string::npos) {
      processPositionCommand(message, &board);
    } else if(message.find("go") != std::string::npos) {
      std::cout << "bestmove " << processGoCommand(message, &board) << "\n";
    }
    getline(std::cin, message);

  }

  return 0;
}
