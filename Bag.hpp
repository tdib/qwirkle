#ifndef BAG_H
#define BAG_H

#include "LinkedList.hpp"
#include "TileCodes.hpp"

#include <algorithm>
#include <random>
#include <sstream>
#include <string>
#include <vector>

class Bag
{
public:
   Bag();
   Bag(std::string bagContents);
   ~Bag();
   std::string saveBag();
   Tile* popTile();
   void pushTile(Tile* tile);
   LinkedList* getTilesInBag();

private:
   LinkedList* tilesInBag;
   // Randomizes the order of tiles
   void scrambleTiles(std::vector<Tile*> tilesToScramble);
   void initialiseTiles();
};

#endif // BAG_H