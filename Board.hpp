#ifndef BOARD_H
#define BOARD_H

#include "Tile.hpp"
#include "TileCodes.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define MAX_COLS         26
#define MAX_ROWS         26
#define FIRST_BOARD_CHAR 'A'
#define LAST_BOARD_CHAR  'Z'
#define TOP_BOTTOM_EDGE  '-'
#define LEFT_RIGHT_EDGE  '|'

class Board
{
public:
   Board();
   ~Board();
   // load constructor - loads the dimensions of the board and tiles on board
   Board(int dimX, int dimY, std::string boardState);
   // prints the board with all tiles, boolean parameter determines if they will
   // be coloured tiles or not
   void printBoard(bool colourPrinting);
   // attempts to place a given tile at location x, y
   bool placeTile(Tile* tileToPlace, int x, int y);
   // returns true if no tiles are on the board
   bool isFirstTile();
   // calculate score on the x axis
   int calculateScoreHorizontal(int coordX, int coordY);
   // calculate score on the y axis
   int calculateScoreVertical(int coordX, int coordY);
   // returns number of columns of the board
   int getDimCols();
   // returns number of rows of the board
   int getDimRows();
   // used for saving the board - returns a string containing the tiles on board
   std::string saveBoard();

   // ORIGINALLY IN PRIVATE - MOVED HERE FOR INDIVIDUAL

   // checks if the left or right tile matches the given tile
   bool canPlaceHorizontal(Tile* tileToPlace, int x, int y);
   // checks if the up or down tile matches the given tile
   bool canPlaceVertical(Tile* tileToPlace, int x, int y);
   // checks if there is a tile directly next to the given coordinates
   bool hasAdjacent(int x, int y);
   // returns a vector containing all tiles on the board
   std::vector<std::vector<Tile*>> getTilesOnBoard();

private:
   std::vector<std::vector<Tile*>> tilesOnBoard;
   int dimCols;
   int dimRows;
   bool loadingFromSave;
};

#endif // BOARD_H