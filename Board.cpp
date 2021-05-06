#include "Board.hpp"

Board::Board()
{
   this->dimX = 26; // Cols
   this->dimY = 26; // Rows
   tilesOnBoard.resize(dimY, std::vector<Tile*>(dimX, 0));

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

Board::Board(int dimX, int dimY, std::string boardState)
{
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

   for (int i = 0; i < dimX; i++)
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