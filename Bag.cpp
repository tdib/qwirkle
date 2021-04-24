#include "Bag.h"

Bag::Bag():
   tiles(new LinkedList())
{
   
}

Bag::Bag(std::string bagInfo)
{
   
}

Bag::~Bag()
{
   while (!tiles->isEmpty())
   {
      delete tiles->pop();
   }
   delete tiles;
   tiles = nullptr;
}

void Bag::initialiseTiles()
{
   // iterate through every tile for however many sets are defined
   int tileSets = 2;
   std::vector<Tile*> tempTiles;
   for (int i = 0; i < tileSets; i++)
   {
      for (Colour colour : colours)
      {
         for (Shape shape : shapes)
         {
            tempTiles.push_back(new Tile(shape, colour));
         }
      }
   }
   scrambleTiles(tempTiles);
}

Tile* Bag::popTile()
{
   return this->popTile();
}

void Bag::pushTile(Tile* tile)
{
   tiles->push(tile);
}

void Bag::scrambleTiles(std::vector<Tile*> tilesToScramble)
{
   auto rng = std::default_random_engine {};
   std::shuffle(std::begin(tilesToScramble), std::end(tilesToScramble), rng);
   for (Tile* tile : tilesToScramble)
   {
      tiles->push(tile);
   }
}
