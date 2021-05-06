#include "Game.hpp"

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

         if (!std::cin.eof())
         {
            try
            {
               validName = isValidName(playerName);
            }
            catch (std::invalid_argument& e)
            {
               std::cout << e.what() << std::endl;
            }
         }
         else
         {
            std::cout << std::endl;
         }
      }

      players.push_back(new Player());
      std::transform(
         playerName.begin(), playerName.end(), playerName.begin(), ::toupper);
      players[j]->setName(playerName);
      players[j]->setBoard(this->board);
      players[j]->setBag(this->bag);

      // Works perfectly
      for (int i = 0; i < 6; i++)
      {
         players[j]->drawTile();
      }
   }

   if (!std::cin.eof())
   {
      std::cout << std::endl;
      std::cout << "Let's Play!" << std::endl;
      std::cout << std::endl;
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

   while (!std::cin.eof() && gameRunning == true)
   {
      for (int i = 0; i < numPlayers; i++)
      {
         bool validInput = false;

         // Move all to print state?
         if (gameRunning == true)
         {
            std::cout << players[i]->getName() << ", it's your turn"
                      << std::endl;
            for (int j = 0; j < numPlayers; j++)
            {
               std::cout << "Score for " << players[j]->getName() << ": "
                         << players[j]->getScore() << std::endl;
            }
            printState();
            std::cout << "Your hand is" << std::endl;
            std::cout << players[i]->getHand() << std::endl;
         }

         while (validInput == false && gameRunning == true)
         {
            std::string rawUserInput = "";

            try
            {
               std::cout << std::endl;
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

                     std::string tileToPlace         = rawCommand[1];
                     std::string placementCoordinate = rawCommand[3];

                     // validCoordinate is incomplete. Need to check for 'A21'
                     if (isValidTile(players[i], tileToPlace) &&
                         isValidCoordinate(placementCoordinate))
                     {
                        // TODO: Need to check that the placement is legal
                        // according to the rules of Qwirkle.
                        //
                        // Might have to be this way due to a scenario where we
                        // grab a valid tile for a valid coordinate, but then
                        // the coordinate happens to already contain a tile. we
                        // cant put the grabbed tile back into the same hand
                        // spot :(
                        int coodX = getColFromCoordinate(placementCoordinate);
                        int coodY = getRowFromCoordinate(placementCoordinate);

                        if (board->isEmptySpot(coodX, coodY))
                        {
                           std::cout << std::endl;
                           Tile* toPlace = nullptr;
                           toPlace = players[i]->getTileFromHand(tileToPlace);
                           board->placeTile(toPlace, coodX, coodY);
                           // update player score?
                           players[i]->drawTile();
                           validInput = true;
                        }
                        else
                        {
                           throw std::invalid_argument("Invalid Input");
                        }
                     }
                     else
                     {
                        throw std::invalid_argument("Invalid Input");
                     }
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
                     std::string tileToSwap = rawCommand[1];

                     if (!bag->getTilesInBag()->isEmpty())
                     {
                        if (isValidTile(players[i], tileToSwap))
                        {
                           if (players[i]->swapTile(tileToSwap))
                           {
                              std::cout << std::endl;
                              validInput = true;
                           }
                           else
                           {
                              throw std::invalid_argument("Invalid Input");
                           }
                        }
                     }
                     else
                     {
                        throw std::invalid_argument("Invalid Input");
                     }
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
               }
               else if (std::cin.eof())
               {
                  std::cout << std::endl;
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
            if (players[i]->isEmptyHand())
            {
               std::cout << "Game over" << std::endl;
               for (int k = 0; k < numPlayers; k++)
               {
                  std::cout << "Score for " << players[k]->getName() << ": "
                            << players[k]->getScore() << std::endl;
               }
               // TODO: figure out which player has the highest score
               std::cout << "Player ... won!" << std::endl;

               // Does the player who ran out first get extra points?
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

bool Game::isValidTile(Player* player, std::string tileToValidate)
{
   bool isValid = false;

   if (player->tileInHand(tileToValidate) == true)
   {
      isValid = true;
   }
   else
   {
      throw std::invalid_argument("Invalid Input");
   }

   return isValid;
}

bool Game::isValidCoordinate(std::string coordinate)
{
   bool isValid = false;

   if (coordinate.size() == 2)
   {
      for (char A = 'A'; A <= 'Z'; A++)
      {
         if (coordinate[0] == A)
         {
            int y = coordinate[1] - '0'; // magiccc :C ty stack
            if (y >= 0 && y <= 9)        // for A0 - A9
            {
               isValid = true;
            }
         }
      }
   }
   // how tf do i do this man
   else if (coordinate.size() == 3)
   {
      std::string str = "";
      for (char A = 'A'; A <= 'Z'; A++)
      {
         if (coordinate[0] == A)
         {
            if (coordinate[1] != ' ')
            {
               str.push_back(coordinate[1]);
               str.push_back(coordinate[2]);
               int col = atoi(str.c_str());
               if (col >= 10 && col <= 25) // for A10 - A25
               {
                  isValid = true;
               }
            }
         }
      }
   }

   if (!isValid)
   {
      throw std::invalid_argument("Invalid Input");
   }
   return isValid;
}

int Game::getColFromCoordinate(std::string coordinate)
{
   int x = 0;

   if (coordinate.size() == 2)
   {
      x = coordinate[1] - '0'; // magiccc :C ty stack
   }
   // how tf do i do this man
   else if (coordinate.size() == 3)
   {
      std::string str = "";
      str.push_back(coordinate[1]);
      str.push_back(coordinate[2]);
      x = atoi(str.c_str());
   }

   return x;
}

int Game::getRowFromCoordinate(std::string coordinate)
{
   int y = 0;

   int row = 0;
   for (char A = 'A'; A <= 'Z'; A++)
   {
      if (coordinate[0] == A)
      {
         y = row;
      }
      row++;
   }

   return y;
}
