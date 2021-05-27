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
   ~Bag();
   // load constructor - converts a string of tiles into a bag with actual tiles
   Bag(std::string bagContents);
   // used for saving the bag state - returns string of every tile in the bag in
   // order
   std::string saveBag();
   // take (pop) the first tile from the bag (front), returns the popped tile
   Tile* popTile();
   // add a tile to the bag (back)
   void pushTile(Tile* tile);
   // return linked list of every tile in the bag
   LinkedList* getTilesInBag();

private:
   LinkedList* tilesInBag;
   // randomizes the order of tiles and adds them to bag
   void scrambleTiles(std::vector<Tile*> tilesToScramble);
   // generate a defined number of tile sets
   void initialiseTiles();
};

#endif // BAG_H