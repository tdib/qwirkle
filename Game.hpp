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
   void playGame();
   int getColFromCoordinate(std::string coordinate);
   int getRowFromCoordinate(std::string coordinate);

private:
   Board* board;
   Bag* bag;
   // std::vector<Player*> players;
   Player** players;
   int numPlayers;
   int startingPlayer;
   void initalisePlayers();
   void printGameState(Player* player);
   bool saveGame(Player* player, std::string saveFileName);
   // Splits the rawUserInput based on the delimiter. Returns a vector of input
   std::vector<std::string> splitString(
      std::string rawUserInput, char delimiter);
   bool isValidName(std::string name, int currNameIndex);
   bool isValidTileInHand(Player* player, std::string tileToValidate);
   bool isValidCoordinate(std::string coordinateToValidate);
   void printQuitMessage();
   bool placeTileCommand(std::vector<std::string> rawCommand, int currPlayer);
   bool replaceTileCommand(std::vector<std::string> rawCommand, int currPlayer);
   void saveGameCommand(std::vector<std::string> rawCommand,
      std::vector<std::string> rawSaveCommand, int currPlayer);
   void helpCommand();
   void finaliseGame(int currPlayer);

   // INDIVIDUAL
   // check if the player name ends in " AI", indicating they are an AI player
   bool isAIName(std::string playerName);
   bool playBestMove(Player* player);
   bool parseUserInput(bool& gameRunning, int currentPlayerIndex);
};

#endif // ASSIGN2_GAME_H
