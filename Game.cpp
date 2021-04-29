#include "Game.h"

// Playing a fresh new game
Game::Game(int numPlayers)
{
   // setting the number of players :)
   this->numPlayers = numPlayers;

   // initialising board
   this->board = new Board();

   // initialising bag
   this->bag = new Bag();

   // initialising players
   initalisePlayers();

   // Set board and bag for all players (moved to initalisePlayers() for
   // efficiency, needa test it)
   // for (int i = 0; i < numPlayers; i++)
   // {
   //    players[i]->setBoard(this->board);
   //    players[i]->setBag(this->bag);
   // }

   // Draw tile six times (per player) -> i.e. initial hand drawing
   // for (int i = 0; i < 6; i++) {
   //    player->drawTile();
   // }
}

// Loading a saved game
Game::Game(std::string* fileName)
{
   // TODO
}

Game::~Game()
{
   // TODO

   for (Player* player : players)
   {
      delete player;
   }

   delete board;
   delete bag;
}

void Game::initalisePlayers()
{
   // M3: in the future, you'd ask for how many players and the vector would
   // count for that many

   // will update later by asking for how many players want to play
   int numPlayers = 2;

   for (int i = 0; i < numPlayers; i++)
   {
      players.push_back(new Player());
   }

   for (int j = 0; j < numPlayers; j++)
   {
      std::string playerName = " ";
      bool validName         = false;

      while (validName == false && !std::cin.eof())
      {
         std::cout << "Enter a name for player " << j + 1
                   << " (uppercase characters only)" << std::endl;
         std::cout << "> ";

         std::getline(std::cin, playerName);

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
      players[j]->setName(playerName);
      players[j]->setBoard(this->board);
      players[j]->setBag(this->bag);
   }

   if (!std::cin.eof())
   {
      std::cout << std::endl;
      std::cout << "Let's Play!" << std::endl;
   }
}

void Game::playGame()
{
   /**
    *
    * Should take input from the user
    * Depending on input, do the thing
    * CHECK IF INPUT STARTS WITH PLACE/REPLACE/ETC
    *
    * if place -> go to placeTile()
    * check that it exists in the hand
    *
    * if replace -> go to swapTile()
    * check that it exists in the hand
    *
    */

   bool gameRunning = true;

   // Ryan note for later: exception handling is bugged: ctrl+z throws an
   // exception so research more into them

   while (!std::cin.eof() && gameRunning == true)
   {
      // for (Player* player : players)
      for (int i = 0; i < numPlayers; i++)
      {
         bool validInput = false;

         while (validInput == false && gameRunning == true)
         {
            std::string rawUserInput = "";
            // Will change this output later on, using for testing atm :)
            std::cout << "it is player " << players[i]->getName() << "'s turn"
                      << std::endl;
            printState();
            try
            {
               std::cout << "> ";
               getline(std::cin, rawUserInput);

               // uppercase before putting the words into the vector
               std::transform(rawUserInput.begin(), rawUserInput.end(),
                  rawUserInput.begin(), ::toupper);
               std::vector<std::string> rawCommand =
                  splitString(rawUserInput, ' ');
               std::string command = "";

               if (rawCommand.size() > 0)
               {
                  command = rawCommand[0];
               }

               if (command == PLACE)
               {
                  if (rawCommand.size() == 4)
                  {
                     if (rawCommand[2] != "AT")
                     {
                        throw std::invalid_argument("Invalid Input");
                     }
                     // TODO:
                     // loop through hand, validate tile exists in hand and
                     // pick out the tile to place + placement coordinate.
                     // pass info to placeTile();

                     // IMPORTANT:
                     // 100% MAKE A METHOD to check if they type in a valid tile
                     std::string tileToPlace         = rawCommand[1];
                     std::string placementCoordinate = rawCommand[3];

                     std::cout << "placing " << tileToPlace;
                     std::cout << " at " << placementCoordinate << std::endl;

                     // LinkedList* tilesInHand = nullptr;
                     // tilesInHand             = player->getHand();
                     validInput = true;
                     // go through tilesInHand and make sure the user input
                     // matches a tile in the hand if match:
                     // player->placeTile(); else: throw
                     // std::invalid_argument("Invalid Input");
                  }
                  else
                  {
                     throw std::invalid_argument("Invalid Input");
                  }
               }
               else if (command == REPLACE)
               {
                  if (rawCommand.size() == 2)
                  {
                     std::string tileToReplace = rawCommand[1];
                     std::cout << "replacing tile " << tileToReplace
                               << std::endl;
                     // check if tile exists in the player's hand
                     // follow the spec :)
                     // replaceTile();
                     validInput = true;
                  }
                  else
                  {
                     throw std::invalid_argument("Invalid Input");
                  }
               }
               else if (command == SAVE)
               {
                  if (rawCommand.size() == 2)
                  {
                     std::string saveFileName = rawCommand[1];
                     std::cout << "Game successfully saved" << std::endl;
                     validInput = true;
                     // Need to now run a saveGame function :)
                     // saveGame(saveFileName);
                  }
                  else
                  {
                     throw std::invalid_argument("Invalid Input");
                  }
               }

               else if (command == QUITGAME)
               {
                  validInput  = true;
                  gameRunning = false;
                  // quitGame()?
                  // Do I even need a quit method?
               }
               else if (std::cin.eof())
               {
                  validInput  = true;
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
            {
               std::cout << e.what() << std::endl;
            }

            // checking if the current player's hand and the bag is empty
            // if both are true, game is over (and we award them 6 extra
            // points?)
            if (players[i]->isEmptyHand() && bag->getTilesInBag()->isEmpty())
            {
               gameRunning = false;
            }
         }
      }
   }
}

void Game::loadTiles(std::string* tilesInfo)
{
   // TODO (for loading tiles in from a saved file)
}

void Game::printState()
{
   board->printBoard();

   // TODO. Full implementation with Board.cpp, etc
}

bool Game::saveGame(std::string saveFileName)
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
   std::string rawCommand, char delimiter)
{
   std::istringstream stringStream(rawCommand);
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

   int size = players.size();
   if (size > 1)
   {
      for (int i = 0; i < size; i++)
      {
         if (players[i]->getName() == name)
         {
            isValid = false;
            throw std::invalid_argument("Invalid Input");
         }
      }
   }

   return isValid;
}