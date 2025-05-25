#include "ChessGame.h"
#include "PlayerVPlayer.h"
#include <memory>

int main() {
  std::unique_ptr<ChessGame> chess;
  std::cout << "press 1 for Player v Player, 2 for Player v AI\n";
  char ans;
  std::cin >> ans;
  while(ans != '1' /*&& ans != 2*/) {
    std::cout << "wrong choice, try again.\n";
    std::cin >> ans;
  }
  getchar();
  if(ans == '1') {
    chess = std::make_unique<PlayerVPlayer>();
  } else if (ans == '2') {
    //chess = std::make_unique<PlayerVAI>();
  }
  chess->runChess();
}