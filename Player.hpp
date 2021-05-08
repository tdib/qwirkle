#ifndef PLAYER_H
#define PLAYER_H

#include "Bag.hpp"
#include "Board.hpp"
#include "Tile.hpp"
#include "TileCodes.hpp"

#include <iostream>
#include <sstream>
#include <string>

class Player
{
public:
   Player();
   Player(std::string playerName, int playerScore, std::string playerHand);
   ~Player();
   bool drawTile();
   bool placeTile(Tile* tile, std::string coordinate);
   bool swapTile(std::string tileToSwap);
   void addScore(int score);

   std::string getName();
   void setName(std::string newName);
   int getScore();
   std::string getHand();
   void setHand(std::string newHand);
   bool isEmptyHand();

   void setBag(Bag* bag);
   void setBoard(Board* board);

   bool tileInHand(std::string tileToValidate);
   Tile* getTileFromHand(std::string tileToGet);

private:
   Bag* bag;
   Board* board;
   LinkedList* hand;
   std::string name;
   int score;
};

#endif // PLAYER_H