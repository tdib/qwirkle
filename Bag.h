#ifndef BAG_H
#define BAG_H

#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include "LinkedList.h"
#include "TileCodes.h"

class Bag
{
   public:
      Bag();
      Bag(std::string bagInfo);
      ~Bag();
      Tile* popTile();
      void pushTile(Tile* tile);
      void scrambleTiles(std::vector<Tile*> tilesToScramble);
      void initialiseTiles();

   private:
      LinkedList* tiles;
};

#endif // BAG_H