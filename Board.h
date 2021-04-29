#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"

#include <iostream>
#include <string>
#include <vector>

class Board
{
public:
   Board();
   Board(std::string boardInfo);
   void printBoard();
   Tile* getTile(std::string tile);
   int calculateScore(Tile* placedTile);

private:
   std::vector<std::vector<Tile*>> tilesOnBoard;
};

#endif // BOARD_H