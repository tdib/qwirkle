#include "Board.hpp"

Board::Board()
{
   this->dimX = 26;
   this->dimY = 26;
   tilesOnBoard.resize(dimX, std::vector<Tile*>(dimY, 0));

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

Board::Board(std::string boardInfo)
{
}

Board::~Board()
{
   int size = tilesOnBoard.size();

   for (int i = 0; i < size; i++)
   {
      for (int j = 0; j < size; j++)
      {
         if (tilesOnBoard[i][j] != nullptr)
         {
            delete tilesOnBoard[i][j];
         }
      }
   }
}

void Board::printBoard()
{
   // Crappy Board print out for now
   std::cout << "   ";

   for (int i = 0; i < 26; i++)
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

   for (int i = 0; i < 79; i++)
   {
      std::cout << "-";
   }

   std::cout << std::endl;

   char c = 'A';

   for (int i = 0; i < 26; i++)
   {
      std::cout << c << " |";
      for (int j = 0; j < 26; j++)
      {
         if (tilesOnBoard[i][j] == nullptr)
         {
            std::cout << "  ";
         }
         else
         {
            tilesOnBoard[i][j]->printTile();
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
   int size     = tilesOnBoard.size();

   for (int row = 0; row < size; row++)
   {
      for (int col = 0; col < size; col++)
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
   int size = tilesOnBoard.size();
   for (int row = 0; row < size; row++)
   {
      for (int col = 0; col < size; col++)
      {
         if (x == col && y == row)
         {
            tilesOnBoard[row][col] = tileToPlace;
         }
      }
   }
}