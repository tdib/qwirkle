#include "Game.h"

// Playing a fresh new game
Game::Game()
{
   // TODO

   // initialising board
   this->board = new Board();

   // initialising bag
   this->bag = new Bag();

   // initialising players
   initalisePlayers();

   // Set board and bag for all players
   for (Player* player : players)
   {
      player->setBoard(this->board);
      player->setBag(this->bag);

      // Draw tile five/six(?) times (per player)
   }
}

// Loading a saved game
Game::Game(std::string* fileName)
{
   // TODO
}

Game::~Game()
{
   // TODO
   delete board;
   delete bag;
   for (Player* player : players)
   {
      delete player;
   }
}

void Game::initalisePlayers()
{
   // move the qwirkle asking player name code here
   // M3: in the future, you'd ask for how many players and the vector would
   // count for that many

   // get the names of the two players (std::cin)
   // set their names
   // for each player, set their board and bag ->

   // will update later by asking for how many players want to play
   int numPlayers = 2;

   for (int i = 0; i < numPlayers; i++)
   {
      std::string playerName = " ";
      bool validName         = false;

      while (validName == false && !std::cin.eof())
      {
         std::cout << "Enter a name for player " << i + 1
                   << " (uppercase characters only, no spaces)" << std::endl;
         std::cout << "> ";

         std::getline(std::cin, playerName); // if we can, we would then check
                                             // against isValidName()

         try
         {
            validName = isValidName(playerName);
         }
         catch (std::invalid_argument& e)
         {
            std::cout << e.what() << std::endl;
         }
      }

      players.push_back(new Player());
      std::transform(
         playerName.begin(), playerName.end(), playerName.begin(), ::toupper);
      players[i]->setName(playerName);
   }
}

void Game::playGame()
{
   /**
    *
    * executeTurn()
    * Should take input from the user
    * Depending on input, do the thing
    * CHECK IF INPUT STARTS WITH PLACE/REPLACE/ETC
    *
    * if place -> go to placeTile()
    * check that it exists in the hand
    *
    *
    *
    * if replace -> go to swapTile()
    * check that it exists in the hand
    *
    */

   //
   // for (Player* player : players) {
   // executeTurn();
   // }

   bool gameRunning = true;

   while (!std::cin.eof() && gameRunning == true)
   {
      std::string input = "";

      try
      {
         std::cout << "> ";
         getline(std::cin, input);

         // uppercase before putting the words into the vector
         std::transform(input.begin(), input.end(), input.begin(), ::toupper);
         std::vector<std::string> rawUserInput = splitString(input, ' ');
         std::string command                   = "";

         if (rawUserInput.size() > 0)
         {
            command = rawUserInput[0];
         }

         if (command == PLACE)
         {
            std::cout << "place" << std::endl;
            // loop through hand, validate tile exists in hand and pick out the
            // tile to place + placement coordinate placeTile();
         }
         else if (command == REPLACE)
         {
            std::cout << "replace" << std::endl;
            // replaceTile();
         }
         else if (command == QUITGAME)
         {
            gameRunning = false;
         }
         else
         {
            throw std::invalid_argument("Invalid Input");
         }
      }
      catch (std::invalid_argument& e)
      {
         std::cout << e.what() << std::endl;
      }
      catch (std::exception& e)
      { // Martin tasukete. catch all or specific ones?
         std::cout << e.what() << std::endl;
      }
   }
}

void Game::loadTiles(std::string* tilesInfo)
{
   // TODO (for loading tiles in from a saved file)
}

void Game::printState()
{
   // TODO

   std::cout << std::endl;
   std::cout << " ";

   for (int i = 0; i < 26; i++)
   { // Columns
      std::cout << "  " << i;
   }

   std::cout << std::endl;
   std::cout << "  ";

   for (int j = 0; j < 47; j++)
   {
      std::cout << "--";
   }

   std::cout << std::endl;

   for (char k = 'A'; k <= 'Z'; k++)
   { // Rows
      std::cout << k << " |" << std::endl;
   }
}

bool Game::saveGame()
{
   // TODO
   // bool false if the file is open or something?
   return false;
}

void Game::quit()
{
   // TODO
   // crash :)
}

std::vector<std::string> Game::splitString(
   std::string rawUserInput, char delimiter)
{ // change to return std:;string array

   // TODO
   std::istringstream stringStream(rawUserInput);
   std::string currWord = "";
   std::vector<std::string> userCommand;
   while (std::getline(stringStream, currWord, delimiter))
   {
      userCommand.push_back(currWord);
   }
   return userCommand;
}

bool Game::isValidName(std::string name)
{
   int length   = name.length();
   bool isValid = true;
   for (int i = 0; i < length; i++)
   {
      if (!isupper(name[i]))
      {
         isValid = false;
         throw std::invalid_argument("Invalid Input");
      }
   }
   return isValid;
}