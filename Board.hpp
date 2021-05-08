#ifndef BOARD_H
#define BOARD_H

#include "Tile.hpp"
#include "TileCodes.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Board
{
public:
   Board();
   Board(int dimX, int dimY, std::string boardState);
   ~Board();
   void printBoard();
   Tile* getTile(std::string tile);
   int calculateScore(Tile* placedTile);
   void placeTile(Tile* tileToPlace, int x, int y);
   bool isEmptySpot(int x, int y);
   std::string saveBoard();
   int getDimCols();
   int getDimRows();

private:
   std::vector<std::vector<Tile*>> tilesOnBoard;
   int dimCols;
   int dimRows;
};

#endif // BOARD_H