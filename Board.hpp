#ifndef BOARD_H
#define BOARD_H

#include "Tile.hpp"

#include <iostream>
#include <string>
#include <vector>

class Board
{
public:
   Board();
   Board(int dimY, int dimX, std::string boardState);
   ~Board();
   void printBoard();
   Tile* getTile(std::string tile);
   int calculateScore(Tile* placedTile);
   void placeTile(Tile* tileToPlace, int x, int y);
   bool isEmptySpot(int x, int y);

private:
   std::vector<std::vector<Tile*>> tilesOnBoard;
   int dimY;
   int dimX;
};

#endif // BOARD_H