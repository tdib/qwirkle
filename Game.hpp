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

#define DEFAULT_PLAYER_COUNT 2

class Game
{
public:
   Game(int numPlayers, bool colourPrinting);
   ~Game();
   // load all information relating to the game (e.g. board, players, etc),
   // and determine whether printing will occur in colour
   Game(std::ifstream& savedGame, bool colourPrinting);
   // alternate between the players and get input - handles the main
   // functionality of the turn system
   bool playGame();
   // return integer for x value (column) of given string coordinate
   int getColFromCoordinate(std::string coordinate);
   // return integer for y value (row) of given string coordinate
   int getRowFromCoordinate(std::string coordinate);
   void setAIMode(bool AIMode);

private:
   Board* board;
   Bag* bag;
   Player** players;
   int numPlayers;
   int startingPlayer;
   // get names of players, set them to AI (if applicable), draw their tiles
   void initalisePlayers();
   // print information relating to players (e.g. scores), and the board
   void printGameState(Player* player);
   // save the game in the default format
   bool saveGame(Player* player, std::string saveFileName);
   // splits the rawUserInput based on the delimiter. returns a vector of input
   std::vector<std::string> splitString(
      std::string rawUserInput, char delimiter);
   // ensure the given name is not a duplicate, or contain any invalid chars
   bool isValidName(std::string name, int currNameIndex);
   // ensures that the given tile is in the given player's hand
   bool isValidTileInHand(Player* player, std::string tileToValidate);
   // checks that the given (typed) coordinate is a valid coordinate on board
   bool isValidCoordinate(std::string coordinateToValidate);
   // say goodbye to the user
   void printQuitMessage();
   // place (and validate) a tile placement
   bool placeTileCommand(std::vector<std::string> rawCommand, int currPlayer);
   // replace the given tile in a hand with the first tile from bag
   bool replaceTileCommand(std::vector<std::string> rawCommand, int currPlayer);
   // determines if the game has custom features, and saves the game in
   // either default or custom format
   void saveGameCommand(std::vector<std::string> rawCommand,
      std::vector<std::string> rawSaveCommand, int currPlayer);
   // prints all possible commands to the user
   void helpCommand();
   // prints the finalised board state and calculates the winner (or draw)
   void finaliseGame(Player* player);

   // INDIVIDUAL

   // check if the player name ends in " AI", indicating they are an AI player
   bool isAIName(std::string playerName);
   // used for AI players to execute their turn
   bool playBestMove(Player* player);
   // used for providing a hint to a player, will print the lowest scored move
   void printHint(Player* player);
   // parse input from the user and determine what they want to do
   bool parseUserInput(bool& gameRunning, bool& hasQuit, int currtPlayerIndex);
   /*
    * save the game in the custom format as follows:
    *
    * #myFormat
    * <number of players>
    * <player x name>
    * <player x score>
    * <player x hand>
    * <player x ai status>
    * <board dimensions>
    * <tiles on board>
    * <tiles in bag>
    * <current player>
    */
   bool customSaveGame(Player* player, std::string saveFileName);

   // boolean to check if there is any AI within the current game -
   // used to determine if a regular or custom save game should be used
   bool AIMode;
   // keep track of whether tiles should be printed in colour
   bool colourPrinting;
};

#endif // ASSIGN2_GAME_H
