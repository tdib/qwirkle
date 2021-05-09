#include "Board.hpp"

Board::Board()
{
   this->dimCols = 26; // X
   this->dimRows = 26; // Y
   this->tilesOnBoard.resize(dimRows, std::vector<Tile*>(dimCols, 0));

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
   this->dimCols = dimCols; // Cols
   this->dimRows = dimRows; // Rows
   this->tilesOnBoard.resize(dimRows, std::vector<Tile*>(dimCols, 0));
   std::stringstream boardTiles(boardState);

   // iterate through boardstate
   while (boardTiles.good())
   {
      Tile* tileToPlace          = nullptr;
      std::string tileToPlaceStr = "";
      std::getline(boardTiles, tileToPlaceStr, '@');
      // DUPLICATED CODE - MAKE METHOD FOR THIS?
      Colour tileColour     = tileToPlaceStr[0];
      std::string toConvert = "";
      toConvert.push_back(tileToPlaceStr[1]);
      Shape tileShape = atoi(toConvert.c_str());

      Colour colours[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
      Shape shapes[]   = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};
      // check if tile is valid
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
      // currently delimiting with a single comma, should be ", " (with a space)
      std::getline(boardTiles, coordToPlace, ',');
      // find the tile on board
      // CODE YOINKED FROM GAME.CPP
      // bool isValid = false;

      if (coordToPlace.size() == 2)
      {
         std::string str = "";
         for (char A = 'A'; A <= 'Z'; A++)
         {
            if (coordToPlace[0] == A)
            {
               str.push_back(coordToPlace[1]);
               int col = atoi(str.c_str());
               if (col >= 0 && col <= 9) // for A0 - A9
               {
                  // isValid = true;
               }
            }
         }
      }
      else if (coordToPlace.size() == 3)
      {
         std::string str = "";
         for (char A = 'A'; A <= 'Z'; A++)
         {
            if (coordToPlace[0] == A)
            {
               str.push_back(coordToPlace[1]);
               str.push_back(coordToPlace[2]);
               int col = atoi(str.c_str());
               if (col >= 10 && col <= 25) // for A10 - A25
               {
                  // isValid = true;
               }
            }
         }
      }

      // place tileToPlace there
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

      // END YOINK
      placeTile(tileToPlace, x, y);
   }
   // place each tile at its given location

   int rowSize = tilesOnBoard.size();
   for (int row = 0; row < rowSize; row++)
   {
      int colSize = tilesOnBoard[row].size();
      for (int col = 0; col < colSize; col++)
      {
         // check if boardState contains piece of this iteration
         // tilesOnBoard[row][col] = that piece
         // else
         // tilesOnBoard[row][col] = nullptr
      }
   }
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

void Board::printBoard()
{
   std::cout << "   ";

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

   std::cout << std::endl;
   std::cout << "  ";

   // Static 79 for the 26x26 board
   for (int i = 0; i < 79; i++)
   {
      std::cout << "-";
   }

   std::cout << std::endl;

   char c      = 'A';
   int rowSize = tilesOnBoard.size();
   for (int row = 0; row < rowSize; row++)
   {
      std::cout << c << " |";
      int colSize = tilesOnBoard[row].size();
      for (int col = 0; col < colSize; col++)
      {
         if (tilesOnBoard[row][col] == nullptr)
         {
            std::cout << "  ";
         }
         else
         {
            tilesOnBoard[row][col]->printTile();
         }
         std::cout << "|";
      }

      std::cout << std::endl;
      c++;
   }

   std::cout << "  ";

   for (int i = 0; i < 79; i++)
   {
      std::cout << "-";
   }

   std::cout << std::endl;
}

Tile* Board::getTile(std::string tile)
{
   return nullptr;
}

int Board::calculateScore(Tile* placedTile)
{
   return -1;
}

// isEmptySpot and placeTile both use the crappy coordinate.size beacuse i need
// to convert the coordinate information each time i need to read it >:(
// maybe we need a convert coordinate thing in game.cpp?
bool Board::isEmptySpot(int x, int y)
{
   bool isEmpty = false;
   int rowSize  = tilesOnBoard.size();
   for (int row = 0; row < rowSize; row++)
   {
      int colSize = tilesOnBoard[row].size();
      for (int col = 0; col < colSize; col++)
      {
         if (x == col && y == row)
         {
            if (tilesOnBoard[row][col] == nullptr)
            {
               isEmpty = true;
            }
         }
      }
   }

   return isEmpty;
}

void Board::placeTile(Tile* tileToPlace, int x, int y)
{
   int rowSize = tilesOnBoard.size();
   for (int row = 0; row < rowSize; row++)
   {
      int colSize = tilesOnBoard[row].size();
      for (int col = 0; col < colSize; col++)
      {
         if (x == col && y == row)
         {
            tilesOnBoard[row][col] = tileToPlace;
         }
      }
   }
}

std::string Board::saveBoard()
{
   std::string boardState = "";
   int rowSize            = tilesOnBoard.size();
   bool matchingTile      = false;
   for (int row = 0; row < rowSize; row++)
   {
      int colSize = tilesOnBoard[row].size();
      for (int col = 0; col < colSize; col++)
      {
         if (tilesOnBoard[row][col] != nullptr)
         {
            // Converting row into alphbetical
            char c = 'A';
            for (int i = 0; i < rowSize; i++)
            {
               if (i == row)
               {
                  matchingTile = true;
                  boardState.append(tilesOnBoard[row][col]->toString() + "@" +
                                    c + std::to_string(col) + ", ");
               }
               c++;
            }
         }
      }
   }

   // Sorry guys :C
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
