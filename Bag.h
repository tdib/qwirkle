#ifndef BAG_H
#define BAG_H

#include <string>
#include "LinkedList.h"
#include <vector>

class Bag
{
   public:
      Bag();
      Bag(std::string bagInfo);
      Tile* popTile();
      void pushTile(Tile* tile);
      void scrambleTiles(std::vector<Tile*>* tilesToScramble);

   private:
      LinkedList* tiles;
};

#endif // BAG_H