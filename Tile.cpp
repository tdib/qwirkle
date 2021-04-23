#include "Tile.h"
#include <iostream>

Tile::Tile(Shape shape, Colour colour):
   shape(shape),
   colour(colour)
{

}

void Tile::printTile()
{
   std::cout << this->colour << this->shape;
}

std::string Tile::getTile()
{
   return this->colour + std::to_string(this->shape);
}

