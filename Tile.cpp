#include "Tile.h"
#include <iostream>

Tile::Tile(Shape shape, Colour colour)
{
   this->shape = shape;
   this->colour = colour;
}

void Tile::printTile(Tile tile)
{
   std::cout << tile.colour << tile.shape;
}