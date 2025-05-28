#include "lichess-bot.h"
#include <iostream>
#include "Engine/AI/Search.h"
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
    } else if(message == "go") {

    }


    getline(std::cin, message);

  }

  return 0;
}
