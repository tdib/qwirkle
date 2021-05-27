#include "Board.hpp"

Board::Board()
{
   this->loadingFromSave = false;
   this->dimCols         = MAX_COLS;
   this->dimRows         = MAX_ROWS;
   this->tilesOnBoard.resize(dimRows, std::vector<Tile*>(dimCols, 0));

   // initialise entire board to nullptrs
   int rowSize = tilesOnBoard.size();
   for (int row = 0; row < rowSize; row++)
   {
      int colSize = tilesOnBoard[row].size();
      for (int col = 0; col < colSize; col++)
      {
         tilesOnBoard[row][col] = nullptr;
      }
   }
}

Board::Board(int dimCols, int dimRows, std::string boardState)
{
   this->loadingFromSave = true;
   this->dimCols         = dimCols;
   this->dimRows         = dimRows;
   this->tilesOnBoard.resize(dimRows, std::vector<Tile*>(dimCols, 0));
   std::stringstream boardTiles(boardState);

   // iterate through boardstate
   while (boardTiles.good())
   {
      // parse board information (e.g. B1@A0) to tile and location
      Tile* tileToPlace          = nullptr;
      std::string tileToPlaceStr = "";
      std::getline(boardTiles, tileToPlaceStr, '@');
      Colour tileColour     = tileToPlaceStr[0];
      std::string toConvert = "";
      toConvert.push_back(tileToPlaceStr[1]);
      Shape tileShape = atoi(toConvert.c_str());

      // check if tile is valid and create a tile object for it
      Colour colours[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
      Shape shapes[]   = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};
      for (Colour colour : colours)
      {
         for (Shape shape : shapes)
         {
            if (tileShape == shape && tileColour == colour)
            {
               tileToPlace = new Tile(tileShape, tileColour);
            }
         }
      }

      std::string coordToPlace = "";
      std::getline(boardTiles, coordToPlace, ',');

      // Determine the x and y coordinate of the tile to place
      int x = 0;
      if (coordToPlace.size() == 2)
      {
         std::string str = "";
         str.push_back(coordToPlace[1]);
         x = atoi(str.c_str());
      }
      else if (coordToPlace.size() == 3)
      {
         std::string str = "";
         str.push_back(coordToPlace[1]);
         str.push_back(coordToPlace[2]);
         x = atoi(str.c_str());
      }

      int y   = 0;
      int row = 0;
      for (char A = 'A'; A <= 'Z'; A++)
      {
         if (coordToPlace[0] == A)
         {
            y = row;
         }
         row++;
      }

      // place tileToPlace there
      placeTile(tileToPlace, x, y);
   }

   loadingFromSave = false;
}

Board::~Board()
{
   int rowSize = tilesOnBoard.size();
   for (int row = 0; row < rowSize; row++)
   {
      int colSize = tilesOnBoard[row].size();
      for (int col = 0; col < colSize; col++)
      {
         if (tilesOnBoard[row][col] != nullptr)
         {
            delete tilesOnBoard[row][col];
         }
      }
   }
}

void Board::printBoard(bool colourPrinting)
{
   // print initial padding
   std::cout << "   ";

   // print column numbers
   for (int i = 0; i < dimCols; i++)
   {
      if (i >= 10)
      {
         std::cout << i << " ";
      }
      else
      {
         std::cout << i << "  ";
      }
   }

   // padding for second line
   std::cout << std::endl;
   std::cout << "  ";

   // print top edge of board
   for (int i = 0; i <= dimCols * 3; i++)
   {
      std::cout << TOP_BOTTOM_EDGE;
   }
   std::cout << std::endl;

   // used to output the respective row character on the board
   char rowChar = FIRST_BOARD_CHAR;
   int rowSize  = tilesOnBoard.size();
   for (int row = 0; row < rowSize; row++)
   {
      std::cout << rowChar << " " << LEFT_RIGHT_EDGE;
      int colSize = tilesOnBoard[row].size();
      for (int col = 0; col < colSize; col++)
      {
         if (tilesOnBoard[row][col] == nullptr)
         {
            std::cout << "  ";
         }
         else
         {
            // print each tile on the board (in colour or white)
            if (colourPrinting)
            {
               tilesOnBoard[row][col]->printTileColour();
            }
            else
            {
               tilesOnBoard[row][col]->printTile();
            }
         }
         std::cout << LEFT_RIGHT_EDGE;
      }

      std::cout << std::endl;

      // increment the row character
      rowChar++;
   }

   // print padding for last line (bottom edge)
   std::cout << "  ";

   // print bottom edge
   for (int i = 0; i <= dimCols * 3; i++)
   {
      std::cout << TOP_BOTTOM_EDGE;
   }
   std::cout << std::endl;
}

int Board::calculateScoreHorizontal(int coordX, int coordY)
{
   int score = 0;

   // check left
   int leftX = coordX - 1;
   while (leftX >= 0 && tilesOnBoard[coordY][leftX] != nullptr)
   {
      leftX--;
   }
   leftX++;

   // check right
   int rightX = coordX + 1;
   while (rightX < dimCols && tilesOnBoard[coordY][rightX] != nullptr)
   {
      rightX++;
   }
   rightX--;

   score = (rightX - leftX) + 1;

   if (score == 6)
   {
      score += 6;
   }

   if (score == 1)
   {
      score = 0;
   }

   return score;
}

int Board::calculateScoreVertical(int coordX, int coordY)
{
   int score = 0;

   // check up
   int upY = coordY - 1;
   while (upY >= 0 && tilesOnBoard[upY][coordX] != nullptr)
   {
      upY--;
   }
   upY++;

   // check down
   int downY = coordY + 1;
   while (downY < dimRows && tilesOnBoard[downY][coordX] != nullptr)
   {
      downY++;
   }
   downY--;

   score = (downY - upY) + 1;

   if (score == 6)
   {
      score += 6;
   }

   if (score == 1)
   {
      score = 0;
   }

   return score;
}

bool Board::canPlaceHorizontal(Tile* tileToPlace, int x, int y)
{
   bool valid          = true;
   Colour targetColour = tileToPlace->toString().at(0);
   char targetShape    = tileToPlace->toString().at(1);

   // check left
   int leftX = x - 1;
   while (leftX >= 0 && tilesOnBoard[y][leftX] != nullptr)
   {
      leftX--;
   }
   leftX++;
   // check right
   int rightX = x + 1;
   while (rightX < dimCols && tilesOnBoard[y][rightX] != nullptr)
   {
      rightX++;
   }
   rightX--;

   // check tiles in range
   for (int currX = leftX; (currX <= rightX) && valid; currX++)
   {
      // don't check target coordinate
      if (currX != x)
      {
         Tile* currentTile      = tilesOnBoard[y][currX];
         Colour currentColour   = currentTile->toString().at(0);
         char currentShape      = currentTile->toString().at(1);
         bool isMatchingColours = currentColour == targetColour;
         bool isMatchingShapes  = currentShape == targetShape;
         if (isMatchingColours && isMatchingShapes)
         {
            // can't repeat the same tile
            valid = false;
         }
         else if (!isMatchingColours && !isMatchingShapes)
         {
            // can't place the tile next to a tile with no matches
            valid = false;
         }
         // check other tiles
         for (int otherX = leftX; (otherX <= rightX) && valid; otherX++)
         {
            Tile* otherTile = tilesOnBoard[y][otherX];
            if (currX != otherX && otherX != x)
            {
               Colour otherColour     = otherTile->toString().at(0);
               char otherShape        = otherTile->toString().at(1);
               bool isMatchingColours = currentColour == otherColour;
               bool isMatchingShapes  = currentShape == otherShape;
               if (isMatchingColours && isMatchingShapes)
               {
                  // can't repeat the same tile
                  valid = false;
               }
               else if (!isMatchingColours && !isMatchingShapes)
               {
                  // can't bridge with no matches
                  valid = false;
               }
            }
         }
      }
   }

   return valid;
}

bool Board::canPlaceVertical(Tile* tileToPlace, int x, int y)
{
   bool valid          = true;
   Colour targetColour = tileToPlace->toString().at(0);
   char targetShape    = tileToPlace->toString().at(1);

   // check up
   int upY = y - 1;
   while (upY >= 0 && tilesOnBoard[upY][x] != nullptr)
   {
      upY--;
   }
   upY++;
   // check down
   int downY = y + 1;
   while (downY < dimRows && tilesOnBoard[downY][x] != nullptr)
   {
      downY++;
   }
   downY--;

   // check tiles in range
   for (int currY = upY; (currY <= downY) && valid; currY++)
   {
      // don't check target coordinate
      if (currY != y)
      {
         Tile* currentTile      = tilesOnBoard[currY][x];
         Colour currentColour   = currentTile->toString().at(0);
         char currentShape      = currentTile->toString().at(1);
         bool isMatchingColours = currentColour == targetColour;
         bool isMatchingShapes  = currentShape == targetShape;
         if (isMatchingColours && isMatchingShapes)
         {
            // can't repeat the same tile
            valid = false;
         }
         else if (!isMatchingColours && !isMatchingShapes)
         {
            // can't place the tile next to a tile with no matches
            valid = false;
         }
         // check other tiles
         for (int otherY = upY; (otherY <= downY) && valid; otherY++)
         {
            Tile* otherTile = tilesOnBoard[otherY][x];
            if (currY != otherY && otherY != y)
            {
               Colour otherColour     = otherTile->toString().at(0);
               char otherShape        = otherTile->toString().at(1);
               bool isMatchingColours = currentColour == otherColour;
               bool isMatchingShapes  = currentShape == otherShape;
               if (isMatchingColours && isMatchingShapes)
               {
                  // can't repeat the same tile
                  valid = false;
               }
               else if (!isMatchingColours && !isMatchingShapes)
               {
                  // can't bridge with no matches
                  valid = false;
               }
            }
         }
      }
   }

   return valid;
}

bool Board::hasAdjacent(int x, int y)
{
   bool success = false;

   // left
   if (x > 0 && tilesOnBoard[y][x - 1] != nullptr)
   {
      success = true;
   }
   // right
   else if (x < dimCols - 1 && tilesOnBoard[y][x + 1] != nullptr)
   {
      success = true;
   }
   // up
   else if (y > 0 && tilesOnBoard[y - 1][x] != nullptr)
   {
      success = true;
   }
   // down
   else if (y < dimRows - 1 && tilesOnBoard[y + 1][x] != nullptr)
   {
      success = true;
   }

   return success;
}

bool Board::isFirstTile()
{
   // check every tile for a non nullptr (meaning something has been placed)
   bool firstTile = true;
   for (int y = 0; y < dimRows && firstTile; y++)
   {
      for (int x = 0; x < dimCols && firstTile; x++)
      {
         if (tilesOnBoard[y][x] != nullptr)
         {
            firstTile = false;
         }
      }
   }
   return firstTile;
}

bool Board::placeTile(Tile* tileToPlace, int x, int y)
{
   bool success = false;
   if (y >= 0 && y < dimRows && x >= 0 && x < dimCols)
   {
      // empty check
      if (tilesOnBoard[y][x] == nullptr)
      {
         if (!loadingFromSave)
         {
            // if tile can be placed at x, y, place it
            if ((hasAdjacent(x, y) && canPlaceHorizontal(tileToPlace, x, y) &&
                   canPlaceVertical(tileToPlace, x, y)) ||
                isFirstTile())
            {
               tilesOnBoard[y][x] = tileToPlace;
               success            = true;
            }
         }
         // tile is loading from save, no validation (it does not require it)
         else
         {
            tilesOnBoard[y][x] = tileToPlace;
            success            = true;
         }
      }
   }

   return success;
}

std::string Board::saveBoard()
{
   std::string boardState = "";
   int rowSize            = tilesOnBoard.size();
   bool matchingTile      = false;
   // iterate through locations on the board and add them to a string
   for (int row = 0; row < rowSize; row++)
   {
      int colSize = tilesOnBoard[row].size();
      for (int col = 0; col < colSize; col++)
      {
         if (tilesOnBoard[row][col] != nullptr)
         {
            // converting row into alphbetical
            char rowChar = FIRST_BOARD_CHAR;
            for (int i = 0; i < rowSize; i++)
            {
               if (i == row)
               {
                  matchingTile = true;
                  boardState.append(tilesOnBoard[row][col]->toString() + "@" +
                                    rowChar + std::to_string(col) + ", ");
               }
               rowChar++;
            }
         }
      }
   }

   // removes the extra ", " from the end of the board state in save files
   if (matchingTile)
   {
      int size = boardState.size();
      boardState.erase(size - 1);
      boardState.erase(size - 2);
   }
   return boardState;
}

int Board::getDimCols()
{
   return dimCols;
}

int Board::getDimRows()
{
   return dimRows;
}

std::vector<std::vector<Tile*>> Board::getTilesOnBoard()
{
   return tilesOnBoard;
}
