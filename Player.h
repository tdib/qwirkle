#ifndef PLAYER_H
#define PLAYER_H

#include "Bag.h"
#include "Board.h"
#include "Tile.h"

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
   bool swapTile(Tile* tileToSwap);
   void addScore();

   std::string getName();
   void setName(std::string newName);
   int getScore();
   std::string getHand();

   bool isEmptyHand();

   void setBag(Bag* bag);
   void setBoard(Board* board);

private:
   Bag* bag;
   Board* board;
   LinkedList* hand;
   std::string name;
   int score;
};

#endif // PLAYER_H