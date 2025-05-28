#pragma once

#include <string>
#include <iostream>
#include "model/Board.h"

std::string getInput();

void respond(std::string);

void processPositionCommand(std::string message, Board* board);

std::string processGoCommand(std::string message, Board* board);
