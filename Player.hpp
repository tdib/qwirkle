#ifndef PLAYER_H
#define PLAYER_H

#include "Bag.hpp"
#include "Board.hpp"
#include "Tile.hpp"

#include <iostream>
#include <string>

class Player
{
public:
   Player();
   Player(std::string playerInfo);
   ~Player();
   bool drawTile();
   bool placeTile(Tile* tile, std::string coordinate);
   bool swapTile(std::string tileToSwap);
   void addScore(int score);

   std::string getName();
   void setName(std::string newName);
   int getScore();
   std::string getHand();

   bool isEmptyHand();

   void setBag(Bag* bag);
   void setBoard(Board* board);

   bool tileInHand(std::string tileToValidate);

private:
   Bag* bag;
   Board* board;
   LinkedList* hand;
   std::string name;
   int score;
};

#endif // PLAYER_H