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
   // Removes excess spaces
   boardState.erase(remove_if(boardState.begin(), boardState.end(), isspace),
      boardState.end());
   this->board = new Board(dimCols, dimRows, boardState);

   // tile bag contents
   std::string bagContents = "";
   getline(savedGame, bagContents);
   this->bag = new Bag(bagContents);

   // current player name
   std::string currentPlayerName = "";
   getline(savedGame, currentPlayerName);

   // For each player, set their bag and board and determine the starting player
   int startingPlayer = 0;
   for (int i = 0; i < numPlayers; i++)
   {
      players[i]->setBag(this->bag);
      players[i]->setBoard(this->board);
      if (currentPlayerName == players[i]->getName())
      {
         startingPlayer = i;
      }
   }

   this->startingPlayer = startingPlayer;

   savedGame.close();

   std::cout << std::endl;
   std::cout << "Qwirkle game successfully loaded" << std::endl;
}

Game::~Game()
{
   for (Player* player : players)
   {
      delete player;
   }

   delete board;
   delete bag;
}

void Game::initalisePlayers()
{
   // numPlayers is hardcoded as 2 in qwirkle.cpp (for group submission)
   for (int i = 0; i < numPlayers; i++)
   {
      players.push_back(new Player());
   }

   // Gets and sets the name for each player, sets their bag and board and draws
   // their initial 6 tiles
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
               if (isValidName(playerName))
               {
                  validName = true;
               }
               else
               {
                  throw std::invalid_argument(
                     "Please type a valid name with uppercase characters only "
                     "and no spaces.");
               }
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

      for (int j = 0; j < MAX_TILES; j++)
      {
         players[i]->drawTile();
      }
   }

   if (!std::cin.eof())
   {
      std::cout << std::endl;
      std::cout << "Let's Play!" << std::endl;
   }
}

void Game::playGame()
{
   bool gameRunning = true;
   while (!std::cin.eof() && gameRunning == true)
   {
      for (int i = startingPlayer; i < numPlayers; i++)
      {
         // Continues from a certain player's turn and resets to allow all other
         // players to have their turn after
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

               // Converting the rawUserInput into all uppercase
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

                  if (isValidTileInHand(players[i], tileToPlace) &&
                      isValidCoordinate(placementCoordinate))
                  {
                     int coordX = getColFromCoordinate(placementCoordinate);
                     int coordY = getRowFromCoordinate(placementCoordinate);

                     Tile* toPlace = players[i]->getTileFromHand(tileToPlace);

                     bool isFirstTile = board->isFirstTile();

                     if (board->placeTile(toPlace, coordX, coordY))
                     {
                        validInput = true;

                        if (isFirstTile)
                        {
                           players[i]->addScore(1);
                        }
                        else
                        {
                           int verticalScore =
                              board->calculateScoreVertical(coordX, coordY);
                           int horizontalScore =
                              board->calculateScoreHorizontal(coordX, coordY);

                           players[i]->addScore(verticalScore);
                           players[i]->addScore(horizontalScore);

                           // If qwirkle or double qwirkle
                           if (verticalScore == 12 && horizontalScore == 12)
                           {
                              std::cout << "DOUBLE QWIRKLE!!!!" << std::endl;
                           }
                           else if (verticalScore == 12 ||
                                    horizontalScore == 12)
                           {
                              std::cout << "QWIRKLE!!!" << std::endl;
                           }
                        }

                        players[i]->drawTile();
                     }
                     else
                     {
                        // return piece to hand (tile is in hand but invalid
                        // placement)
                        players[i]->addToHand(toPlace);
                        throw std::invalid_argument(
                           "That was not a valid placement for that tile. "
                           "Please try "
                           "again.");
                     }
                  }
                  else
                  {
                     // tile placement was wrong or not possible
                     throw std::invalid_argument(
                        "You do not have this tile. Please try again.");
                  }
               }
               else if (command == REPLACE && rawCommand.size() == 2)
               {
                  std::string tileToSwap = rawCommand[1];

                  if (!bag->getTilesInBag()->isEmpty())
                  {
                     if (players[i]->swapTile(tileToSwap))
                     {
                        validInput = true;
                     }
                     else
                     {
                        throw std::invalid_argument(
                           "You do not have this tile. Please try again.");
                     }
                  }
                  else
                  {
                     throw std::invalid_argument("The bag is empty!");
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
                        throw std::invalid_argument(
                           "The game could not be saved. Please try again.");
                     }
                  }
                  else
                  {
                     throw std::invalid_argument("Usage: save <filename>");
                  }
               }
               else if (command == HELP)
               {
                  std::cout
                     << "You may use the following (case insensitive) commands."
                     << std::endl;
                  std::cout << "-----------------------------------------------"
                            << std::endl;
                  std::cout << "Placing a tile:     place <tile> at <location>"
                            << std::endl;
                  std::cout << "Replacing a tile:   replace <tile>"
                            << std::endl;
                  std::cout << "Saving the game:    save <filename or relative "
                               "filepath>"
                            << std::endl;
                  std::cout << "Quitting the game:  quit" << std::endl;
               }
               else if (command == QUITGAME)
               {
                  validInput  = true;
                  gameRunning = false;
                  printQuitMessage();
               }
               else if (std::cin.eof())
               {
                  std::cout << std::endl;
                  validInput  = true;
                  gameRunning = false;
               }
               else
               {
                  throw std::invalid_argument(
                     "The command you typed was incorrect. Please use the "
                     "'help' command for more information.");
               }
            }
            catch (std::invalid_argument& e)
            {
               std::cout << e.what() << std::endl;
            }

            // checking if the current player's hand is empty. if both are true,
            // then the game is over!
            if (players[i]->isEmptyHand())
            {
               // Player who places their last tile first gets 6 extra points
               players[i]->addScore(6);
               gameRunning = false;
               bool isDraw = true;

               board->printBoard();

               std::cout << "Game over!!" << std::endl;

               // Set the winner initially to the first player
               Player* winner = players[0];

               for (int j = 0; j < numPlayers; j++)
               {
                  // Check if player[j]'s score is greater than the winner's
                  if (players[j]->getScore() > winner->getScore())
                  {
                     isDraw = false;
                     winner = players[j];
                  }
                  // else check for an equal score (draw condition)
                  else if (players[j]->getScore() != winner->getScore())
                  {
                     isDraw = false;
                  }

                  std::cout << "Score for " << players[j]->getName() << ": "
                            << players[j]->getScore() << std::endl;
               }

               // Different output if draw or normal win
               if (isDraw)
               {
                  std::cout << "It's a draw!" << std::endl;
               }
               else
               {
                  std::cout << winner->getName() << " won!" << std::endl;
               }
            }
         }
      }
   }
}

void Game::printGameState(Player* player)
{
   std::cout << std::endl;
   board->printBoard();
   std::cout << player->getName() << ", it's your turn" << std::endl;
   for (int i = 0; i < numPlayers; i++)
   {
      std::cout << "Score for " << players[i]->getName() << ": "
                << players[i]->getScore() << std::endl;
   }
   std::cout << std::endl;
   std::cout << "Your hand is" << std::endl;
   std::cout << player->getHand() << std::endl;
}

bool Game::saveGame(Player* player, std::string saveFileName)
{
   bool canSave = false;
   std::ofstream saveFile(saveFileName + ".save");

   if (saveFile.good())
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
      saveFile << player->getName();
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
            // for A0 - A9
            if (col >= 0 && col <= 9)
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
            // for A10 - A25
            if (col >= 10 && col <= 25)
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
   // Converts string coordinate to respective x coordinate (in integer form)
   // No need for validation checking as it has already been checked
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

   return x;
}

int Game::getRowFromCoordinate(std::string coordinate)
{
   // Converts string coordinate to respective y coordinate (in integer form)
   // No need for validation checking as it has already been checked
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

   return y;
}

void Game::printQuitMessage()
{
   std::cout << std::endl;
   std::cout << "Goodbye" << std::endl;
}
