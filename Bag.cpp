#include "Bag.hpp"

Bag::Bag()
    : tilesInBag(new LinkedList())
{
   initialiseTiles();
}

Bag::Bag(std::string bagInfo)
    : tilesInBag(new LinkedList())
{
   // TODO: Parse bagInfo and generate tiles
}

Bag::~Bag()
{
   while (!tilesInBag->isEmpty())
   {
      delete tilesInBag->pop();
   }
   delete tilesInBag;
   tilesInBag = nullptr;
}

void Bag::initialiseTiles()
{
   Colour colours[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
   Shape shapes[]   = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};

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
   return tilesInBag->pop();
}

void Bag::pushTile(Tile* tile)
{
   tilesInBag->push(tile);
}

void Bag::scrambleTiles(std::vector<Tile*> tilesToScramble)
{
   // auto rng = std::default_random_engine {}; // Static (for testing)
   std::random_device rng; // Random (for real gameplay)
   std::shuffle(std::begin(tilesToScramble), std::end(tilesToScramble), rng);
   for (Tile* tile : tilesToScramble)
   {
      tilesInBag->push(tile);
   }
}

LinkedList* Bag::getTilesInBag()
{
   return tilesInBag;
}