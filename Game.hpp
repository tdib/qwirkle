#ifndef ASSIGN2_GAME_H
#define ASSIGN2_GAME_H

#include "Bag.hpp"
#include "InputCodes.hpp"
#include "Player.hpp"
#include "Tile.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Game
{
public:
   Game(int numPlayers);
   Game(int numPlayers, std::ifstream& savedGame);
   ~Game();

   // Public or else qwirkle.cpp can't use them
   void playGame();
   void initalisePlayers();
   void printGameState(Player* player);
   bool saveGame(std::string saveFileName);
   std::vector<std::string> splitString(
      std::string rawUserInput, char delimiter);
   bool isValidName(std::string name);
   bool isValidTileInHand(Player* player, std::string tileToValidate);
   bool isValidCoordinate(std::string coordinateToValidate);
   int getColFromCoordinate(std::string coordinate);
   int getRowFromCoordinate(std::string coordinate);

private:
   // player as a vector

   Board* board;
   Bag* bag;
   std::vector<Player*> players;
   int numPlayers;
   int startingPlayer;
};

#endif // ASSIGN2_GAME_H
