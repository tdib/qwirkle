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
   std::string txtColour = "";
   if (this->colour == RED)
   {
      txtColour = RED_TXT;
   }
   else if (this->colour == ORANGE)
   {
      txtColour = ORANGE_TXT;
   }
   else if (this->colour == YELLOW)
   {
      txtColour = YELLOW_TXT;
   }
   else if (this->colour == GREEN)
   {
      txtColour = GREEN_TXT;
   }
   else if (this->colour == BLUE)
   {
      txtColour = BLUE_TXT;
   }
   else if (this->colour == PURPLE)
   {
      txtColour = PURPLE_TXT;
   }
   std::cout << txtColour << this->colour << this->shape << RESET;
}

std::string Tile::toStringColour()
{
   std::string returnTile = "";
   std::string txtColour  = "";
   if (this->colour == RED)
   {
      txtColour = RED_TXT;
   }
   else if (this->colour == ORANGE)
   {
      txtColour = ORANGE_TXT;
   }
   else if (this->colour == YELLOW)
   {
      txtColour = YELLOW_TXT;
   }
   else if (this->colour == GREEN)
   {
      txtColour = GREEN_TXT;
   }
   else if (this->colour == BLUE)
   {
      txtColour = BLUE_TXT;
   }
   else if (this->colour == PURPLE)
   {
      txtColour = PURPLE_TXT;
   }
   returnTile += txtColour;
   returnTile += this->colour;
   returnTile += std::to_string(this->shape);
   returnTile += RESET;
   return returnTile;
}

std::string Tile::toString()
{
   return this->colour + std::to_string(this->shape);
}