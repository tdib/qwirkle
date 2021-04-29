#ifndef BAG_H
#define BAG_H

#include "LinkedList.h"
#include "TileCodes.h"

#include <algorithm>
#include <random>
#include <string>
#include <vector>

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
   LinkedList* getTilesInBag();

private:
   LinkedList* tilesInBag;
};

#endif // BAG_H