#include "Board.h"

Board::Board()
{
   tilesOnBoard.resize(26, std::vector<Tile*>(26, 0));
   int size = tilesOnBoard.size();

   for (int i = 0; i < size; i++)
   {
      for (int j = 0; j < size; j++)
      {
         tilesOnBoard[i][j] = nullptr;
      }
   }
}

Board::Board(std::string boardInfo)
{
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

   for (int i = 0; i < 78; i++)
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
            // print contents of [i][j] (will be something like G1)
         }
         std::cout << "|";
      }

      std::cout << std::endl;
      c++;
   }
}

Tile* Board::getTile(std::string tile)
{
   return nullptr;
}

int Board::calculateScore(Tile* placedTile)
{
   return -1;
}
