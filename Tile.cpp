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

void Tile::printTileColour()
{
   if (colour == RED)
   {
      std::cout << RED_TXT << this->colour << this->shape << RESET;
   }
   else if (colour == ORANGE)
   {
      std::cout << ORANGE_TXT << this->colour << this->shape << RESET;
   }
   else if (colour == YELLOW)
   {
      std::cout << YELLOW_TXT << this->colour << this->shape << RESET;
   }
   else if (colour == GREEN)
   {
      std::cout << GREEN_TXT << this->colour << this->shape << RESET;
   }
   else if (colour == BLUE)
   {
      std::cout << BLUE_TXT << this->colour << this->shape << RESET;
   }
   else if (colour == PURPLE)
   {
      std::cout << PURPLE_TXT << this->colour << this->shape << RESET;
   }
}

std::string Tile::toStringColour()
{
   std::string returnTile = "";
   if (colour == RED)
   {
      returnTile += RED_TXT;
      returnTile += this->colour;
      returnTile += std::to_string(this->shape);
      returnTile += RESET;
      return returnTile;
   }
   else if (colour == ORANGE)
   {
      returnTile += ORANGE_TXT;
      returnTile += this->colour;
      returnTile += std::to_string(this->shape);
      returnTile += RESET;
   }
   else if (colour == YELLOW)
   {
      returnTile += YELLOW_TXT;
      returnTile += this->colour;
      returnTile += std::to_string(this->shape);
      returnTile += RESET;
   }
   else if (colour == GREEN)
   {
      returnTile += GREEN_TXT;
      returnTile += this->colour;
      returnTile += std::to_string(this->shape);
      returnTile += RESET;
   }
   else if (colour == BLUE)
   {
      returnTile += BLUE_TXT;
      returnTile += this->colour;
      returnTile += std::to_string(this->shape);
      returnTile += RESET;
   }
   else if (colour == PURPLE)
   {
      returnTile += PURPLE_TXT;
      returnTile += this->colour;
      returnTile += std::to_string(this->shape);
      returnTile += RESET;
   }
   return returnTile;
}

std::string Tile::toString()
{
   return this->colour + std::to_string(this->shape);
}