#include "Perft/Perft.h"
#include <string>
#include <iostream>
#include <chrono>

int readDepth(int argc, char*  argv[]) {
  for(int i = 1; i < argc; i++) {
    std::string arg = argv[i];
    if(arg.rfind("--depth=", 0) == 0) {
      std::string value = arg.substr(8);
      try {
        return std::stoi(value);
      } catch (...) {
        
      }
    }
  }
  return 0;
}

int main(int argc, char* argv[]) {
  Perft perft;
  auto start = std::chrono::high_resolution_clock::now();
  int depth = readDepth(argc, argv);
  int numPos = perft.runPerft(depth, depth);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = end - start;
  std::cout << "numpos = " << numPos << "\n";
  std::cout << "Took: " << duration.count() << " seconds\n"; 
  return 0;
}