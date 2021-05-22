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
   Player(std::string playerName, int playerScore, std::string playerHand,
      bool AIStatus);
   ~Player();
   void setBag(Bag* bag);
   void setBoard(Board* board);
   void setName(std::string newName);
   int getScore();
   std::string getName();
   std::string getHandStr();
   void setHand(std::string newHand);
   void addScore(int score);
   bool isEmptyHand();
   bool drawTile();
   Tile* getTileFromHand(std::string tileToGet);
   bool swapTile(std::string tileToSwap);
   bool tileInHand(std::string tileToValidate);
   // Used to return a tile to the hand (if a valid tile is selected but can't
   // be placed)
   void addToHand(Tile* tile);

   // INDIVIDUAL
   void setAIStatus(bool AIStatus);
   bool getAIStatus();
   LinkedList* getHand();

private:
   Bag* bag;
   Board* board;
   LinkedList* hand;
   std::string name;
   int score;

   // INDIVIDUAL
   bool AIStatus;
};

#endif // PLAYER_H