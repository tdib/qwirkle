#include "Bag.hpp"

Bag::Bag()
    : tilesInBag(new LinkedList())
{
   initialiseTiles();
}

Bag::Bag(std::string bagContents)
    : tilesInBag(new LinkedList())
{
   // convert string of tiles into stringstream, iterate through and add
   // each one to the bag
   std::stringstream bagContentStream(bagContents);
   while (bagContentStream.good())
   {
      // parse a tile string (e.g. B6) into separate values (e.g B and 6)
      std::string currTile = "";
      std::getline(bagContentStream, currTile, ',');
      Colour tileColour     = currTile[0];
      std::string toConvert = "";
      toConvert.push_back(currTile[1]);
      Shape tileShape = atoi(toConvert.c_str());

      // iterate through colorus and shapes to determine what the string format
      // of the tile means
      Colour colours[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
      Shape shapes[]   = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};
      for (Colour colour : colours)
      {
         for (Shape shape : shapes)
         {
            if (tileShape == shape && tileColour == colour)
            {
               this->tilesInBag->push(new Tile(tileShape, tileColour));
            }
         }
      }
   }
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
   // add each tile into a vector
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

   // scramble the vector
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
   // scramble the tiles and then add them to the bag
   auto rng = std::default_random_engine {1}; // Static (for testing)
   // std::random_device rng; // Random (for real gameplay)
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

std::string Bag::saveBag()
{
   return tilesInBag->getContents(false);
}
