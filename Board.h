#include <string>
#include "Tile.h"
#include <vector>

class Board
{
   public:
      Board();
      Board(std::string boardInfo);
      void printBoard();
      Tile* getTile(std::string tile);
      int calculateScore(Tile* placedTile);

      std::vector<std::vector<Tile*>> tilesOnBoard;
};