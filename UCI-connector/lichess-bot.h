#pragma once

#include <string>
#include <iostream>
#include "model/Board.h"

std::string getInput();

void respond(std::string);

void processPositionCommand(std::string message, Board* board);

//return the best move as a string
std::string processGoCommand(std::string message, Board* board);
