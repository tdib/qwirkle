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
   ~Player();
   // load constructor - loads player name, score, hand, and whether they are AI
   Player(std::string playerName, int playerScore, std::string playerHand,
      bool AIStatus);
   void setBag(Bag* bag);
   void setBoard(Board* board);
   void setName(std::string newName);
   int getScore();
   std::string getName();
   std::string getHandStr(bool colourPrinting);
   void setHand(std::string newHand);
   // add score to a given player
   void addScore(int score);
   // check if the player's hand is empty
   bool isEmptyHand();
   // give the player a tile from the bag
   bool drawTile();
   // take a tile out of the players hand using a string (e.g. B6)
   Tile* getTileFromHand(std::string tileToGet);
   // swap a given tile with the first tile in the tile bag
   bool swapTile(std::string tileToSwap);
   // check if a tile is in the players hand
   bool tileInHand(std::string tileToValidate);
   // used to return a tile to the hand (if a valid tile is selected but can't
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

   // used to determine whether the player is an AI or human player
   bool AIStatus;
};

#endif // PLAYER_H