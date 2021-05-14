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
   bool placeTile(Tile* tileToPlace, int x, int y);
   bool isFirstTile();
   int calculateScoreHorizontal(int coordX, int coordY);
   int calculateScoreVertical(int coordX, int coordY);
   int getDimCols();
   int getDimRows();
   std::string saveBoard();

private:
   std::vector<std::vector<Tile*>> tilesOnBoard;
   int dimCols;
   int dimRows;
   bool canPlaceHorizontal(Tile* tileToPlace, int x, int y);
   bool canPlaceVertical(Tile* tileToPlace, int x, int y);
   bool hasAdjacent(int x, int y);
   bool loadingFromSave;
};

#endif // BOARD_H