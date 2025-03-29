#pragma once

struct Square {
  int file, rank;
};

struct Move {
  Square fromSquare;
  Square toSquare;
};