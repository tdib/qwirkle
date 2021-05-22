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

   // ORIGINALLY IN PRIVATE - MOVED HERE FOR INDIVIDUAL
   bool canPlaceHorizontal(Tile* tileToPlace, int x, int y);
   bool canPlaceVertical(Tile* tileToPlace, int x, int y);
   bool hasAdjacent(int x, int y);
   std::vector<std::vector<Tile*>> getTilesOnBoard();

   // INDIVIDUAL
   int calculateScore(int col, int row);

private:
   std::vector<std::vector<Tile*>> tilesOnBoard;
   int dimCols;
   int dimRows;
   bool loadingFromSave;
};

#endif // BOARD_H