#include "Game.hpp"

// Playing a fresh new game
Game::Game(int numPlayers)
{
   // setting the number of players :)
   this->numPlayers = numPlayers;

   // On a fresh game, set the starting player to players[0]
   this->startingPlayer = 0;

   // initialising board
   this->board = new Board();

   // initialising bag
   this->bag = new Bag();

   // initialising players
   initalisePlayers();
}

// Loading a saved game
Game::Game(int numPlayers, std::ifstream& savedGame)
{
   this->numPlayers = numPlayers;
   // this->startingPlayer = ?;
   // needs input validation for file
   // idk if you check and validate the file as you go or at the start
   // also, need to

   // player one name
   std::string playerOneName = "";
   getline(savedGame, playerOneName);

   // player one score
   std::string playerOneScoreStr = "";
   getline(savedGame, playerOneScoreStr);
   int playerOneScore = std::stoi(playerOneScoreStr);

   // player one hand
   std::string playerOneHand = "";
   getline(savedGame, playerOneHand);

   this->players.push_back(
      new Player(playerOneName, playerOneScore, playerOneHand));

   // player two name
   std::string playerTwoName = "";
   getline(savedGame, playerTwoName);

   // player two score
   std::string playerTwoScoreStr = "";
   getline(savedGame, playerTwoScoreStr);
   int playerTwoScore = std::stoi(playerTwoScoreStr);

   // player two hand
   std::string playerTwoHand = "";
   getline(savedGame, playerTwoHand);

   this->players.push_back(
      new Player(playerTwoName, playerTwoScore, playerTwoHand));

   // board dimensions
   std::string dimStr = "";
   getline(savedGame, dimStr);
   size_t commaIndex = dimStr.find(",");
   int dimCols       = std::stoi(dimStr.substr(commaIndex + 1));
   int dimRows       = std::stoi(dimStr.substr(0, commaIndex));

   // board state
   std::string boardState = "";
   getline(savedGame, boardState);
   this->board = new Board(dimCols, dimRows, boardState);

   // tile BAG contents
   std::string bagContents = "";
   getline(savedGame, bagContents);
   this->bag = new Bag(bagContents);

   for (int i = 0; i < numPlayers; i++)
   {
      players[i]->setBag(this->bag);
      players[i]->setBoard(this->board);
   }

   // current player name
   std::string currentPlayerName = "";
   getline(savedGame, currentPlayerName);

   int startingPlayer = 0;
   for (int i = 0; i < numPlayers; i++)
   {
      if (currentPlayerName == players[i]->getName())
      {
         startingPlayer = i;
      }
   }

   this->startingPlayer = startingPlayer;

   savedGame.close();

   std::cout << std::endl;
   std::cout << "Qwirkle game successfully loaded" << std::endl;
   std::cout << std::endl;
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
   for (int i = 0; i < numPlayers; i++)
   {
      players.push_back(new Player());
   }

   for (int i = 0; i < numPlayers; i++)
   {
      std::string playerName = " ";
      bool validName         = false;

      while (validName == false && !std::cin.eof())
      {
         std::cout << "Enter a name for player " << i + 1
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
      players[i]->setName(playerName);
      players[i]->setBoard(this->board);
      players[i]->setBag(this->bag);

      // Works perfectly
      for (int j = 0; j < 6; j++)
      {
         players[i]->drawTile();
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
      for (int i = startingPlayer; i < numPlayers; i++) // need to update others
      {
         // Continues from a certain player's turn and resets to allow all other
         // players to have their turn
         if (startingPlayer != 0)
         {
            startingPlayer = 0;
         }

         bool validInput = false;

         if (gameRunning == true)
         {
            printGameState(players[i]);
         }

         while (validInput == false && gameRunning == true)
         {
            std::string rawUserInput = "";

            try
            {
               std::cout << std::endl;
               std::cout << "> ";
               getline(std::cin, rawUserInput);

               // Splitting up rawUserInput based on delimited (spaces)
               // This specific splitString() is for case-sensitive save files
               std::vector<std::string> rawSaveCommand =
                  splitString(rawUserInput, ' ');

               // Converting rawUserInput into all uppercase
               std::transform(rawUserInput.begin(), rawUserInput.end(),
                  rawUserInput.begin(), ::toupper);

               // Splitting up rawUserInput based on delimiter (spaces)
               std::vector<std::string> rawCommand =
                  splitString(rawUserInput, ' ');

               std::string command = "";
               if (rawCommand.size() > 0)
               {
                  command = rawCommand[0];
               }

               if (command == PLACE && rawCommand.size() == 4 &&
                   rawCommand[2] == "AT")
               {
                  std::string tileToPlace         = rawCommand[1];
                  std::string placementCoordinate = rawCommand[3];

                  // validCoordinate is incomplete. Need to check for 'A21'
                  if (isValidTileInHand(players[i], tileToPlace) &&
                      isValidCoordinate(placementCoordinate))
                  {
                     // TODO: Need to check that the placement is legal
                     // according to the rules of Qwirkle.
                     // Might have to be this way due to a scenario where we
                     // grab a valid tile for a valid coordinate, but then
                     // the coordinate happens to already contain a tile. we
                     // cant put the grabbed tile back into the same hand
                     // spot :(
                     int coordX = getColFromCoordinate(placementCoordinate);
                     int coordY = getRowFromCoordinate(placementCoordinate);

                     if (board->isEmptySpot(coordX, coordY))
                     {
                        std::cout << std::endl;
                        Tile* toPlace = nullptr;
                        toPlace = players[i]->getTileFromHand(tileToPlace);
                        board->placeTile(toPlace, coordX, coordY);

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
               else if (command == REPLACE && rawCommand.size() == 2)
               {
                  std::string tileToSwap = rawCommand[1];

                  if (!bag->getTilesInBag()->isEmpty())
                  {
                     if (isValidTileInHand(players[i], tileToSwap))
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
                     std::string saveFileName = rawSaveCommand[1];
                     if (saveGame(players[i], saveFileName))
                     {
                        std::cout << "Game successfully saved" << std::endl;
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
               for (int j = 0; j < numPlayers; j++)
               {
                  std::cout << "Score for " << players[j]->getName() << ": "
                            << players[j]->getScore() << std::endl;
               }
               // TODO: figure out which player has the highest score (easy with
               // 2 players, tad bit harder with more)
               std::cout << "Player ... won!" << std::endl;

               // Does the player who ran out of tiles first get extra points?
               gameRunning = false;
            }
         }
      }
   }
}

void Game::printGameState(Player* player)
{
   std::cout << player->getName() << ", it's your turn" << std::endl;
   for (int i = 0; i < numPlayers; i++)
   {
      std::cout << "Score for " << players[i]->getName() << ": "
                << players[i]->getScore() << std::endl;
   }
   board->printBoard();
   std::cout << "Your hand is" << std::endl;
   std::cout << player->getHand() << std::endl;
}

bool Game::saveGame(Player* player, std::string saveFileName)
{
   bool canSave = false;

   std::ofstream saveFile(saveFileName + ".save");
   // WHAT OFSTREAM FUNCTIONS DO WE USE TO CHECK THAT A FILE IS GOOD >:(
   if (!saveFile.fail())
   {
      for (int i = 0; i < numPlayers; i++)
      {
         saveFile << players[i]->getName() << std::endl;
         saveFile << players[i]->getScore() << std::endl;
         saveFile << players[i]->getHand() << std::endl;
      }
      saveFile << board->getDimCols() << "," << board->getDimRows()
               << std::endl;
      saveFile << board->saveBoard() << std::endl;
      saveFile << bag->saveBag() << std::endl;
      saveFile << player->getName() << std::endl;
      canSave = true;
   }

   saveFile.close();
   return canSave;
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

bool Game::isValidTileInHand(Player* player, std::string tileToValidate)
{
   bool isValid = false;

   if (player->tileInHand(tileToValidate) == true)
   {
      isValid = true;
   }

   return isValid;
}

bool Game::isValidCoordinate(std::string coordinate)
{
   bool isValid = false;

   if (coordinate.size() == 2)
   {
      std::string str = "";
      for (char A = 'A'; A <= 'Z'; A++)
      {
         if (coordinate[0] == A)
         {
            str.push_back(coordinate[1]);
            int col = atoi(str.c_str());
            if (col >= 0 && col <= 9) // for A0 - A9
            {
               isValid = true;
            }
         }
      }
   }
   else if (coordinate.size() == 3)
   {
      std::string str = "";
      for (char A = 'A'; A <= 'Z'; A++)
      {
         if (coordinate[0] == A)
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

   return isValid;
}

int Game::getColFromCoordinate(std::string coordinate)
{
   int x = 0;
   if (coordinate.size() == 2)
   {
      std::string str = "";
      str.push_back(coordinate[1]);
      x = atoi(str.c_str());
   }
   else if (coordinate.size() == 3)
   {
      std::string str = "";
      str.push_back(coordinate[1]);
      str.push_back(coordinate[2]);
      x = atoi(str.c_str());
   }
   // No need for validation checking as it has already been checked :)
   return x;
}

int Game::getRowFromCoordinate(std::string coordinate)
{
   int y   = 0;
   int row = 0;
   for (char A = 'A'; A <= 'Z'; A++)
   {
      if (coordinate[0] == A)
      {
         y = row;
      }
      row++;
   }
   // No need for validation checking as it has already been checked :)
   return y;
}
