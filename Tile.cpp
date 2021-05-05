#include "Tile.hpp"

Tile::Tile(Shape shape, Colour colour)
    : shape(shape)
    , colour(colour)
{
}

void Tile::printTile()
{
   std::cout << this->colour << this->shape;
}

std::string Tile::toString()
{
   return this->colour + std::to_string(this->shape);
}
