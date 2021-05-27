#include "Game.hpp"

// Playing a fresh new game
Game::Game(int numPlayers, bool colourPrinting)
{
   // determines if tiles will be printed in colour or not
   this->colourPrinting = colourPrinting;

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
Game::Game(std::ifstream& savedGame, bool colourPrinting)
{
   // differentiate if it is a custom or regular format
   std::string firstLine = "";
   getline(savedGame, firstLine);
   if (firstLine == "#myFormat")
   {
      std::string numPlayersStr = "";
      getline(savedGame, numPlayersStr);
      this->numPlayers = std::stoi(numPlayersStr);

      players = new Player*[numPlayers];

      for (int i = 0; i < numPlayers; i++)
      {
         // player i name
         std::string playerName = "";
         getline(savedGame, playerName);

         // player i score
         std::string playerScoreStr = "";
         getline(savedGame, playerScoreStr);
         int playerScore = std::stoi(playerScoreStr);

         // player i hand
         std::string playerHand = "";
         getline(savedGame, playerHand);

         std::string AIStatusStr = "";
         getline(savedGame, AIStatusStr);
         bool AIStatus = AIStatusStr == "1";

         players[i] = new Player(playerName, playerScore, playerHand, AIStatus);
      }
   }
   else
   {
      // 2 is the default player count
      this->numPlayers = 2;
      players          = new Player*[2];

      // player one name (first line has already been buffered)
      std::string playerOneName = firstLine;

      // player one score
      std::string playerOneScoreStr = "";
      getline(savedGame, playerOneScoreStr);
      int playerOneScore = std::stoi(playerOneScoreStr);

      // player one hand
      std::string playerOneHand = "";
      getline(savedGame, playerOneHand);

      // create first player with false ai status
      players[0] =
         new Player(playerOneName, playerOneScore, playerOneHand, false);

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

      // create second player with false ai status
      players[1] =
         new Player(playerTwoName, playerTwoScore, playerTwoHand, false);
   }

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

   // For each player, set their bag and board and determine the starting
   // player
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

   this->colourPrinting = colourPrinting;
   this->startingPlayer = startingPlayer;

   savedGame.close();

   std::cout << std::endl;
   std::cout << "Qwirkle game successfully loaded" << std::endl;
}

Game::~Game()
{
   for (int i = 0; i < numPlayers; i++)
   {
      delete players[i];
   }
   delete[] players;

   delete board;
   delete bag;
}

void Game::initalisePlayers()
{
   this->players = new Player*[numPlayers];
   // Gets and sets the name for each player, sets their bag and board and draws
   // their initial 6 tiles
   for (int i = 0; i < numPlayers; i++)
   {
      std::string playerName = "";
      bool validName         = false;

      while (validName == false && !std::cin.eof())
      {
         std::cout << std::endl
                   << "Enter a name for player " << i + 1 << std::endl;
         std::cout << "> ";

         std::getline(std::cin, playerName);
         std::transform(playerName.begin(), playerName.end(),
            playerName.begin(), ::toupper);

         if (!std::cin.eof())
         {
            try
            {
               if (isValidName(playerName, i))
               {
                  validName = true;
               }
               else
               {
                  throw std::invalid_argument(
                     "Please type a valid name with no special characters");
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

      players[i] = new Player();
      if (isAIName(playerName))
      {
         AIMode = true;
         players[i]->setAIStatus(true);
         // remove the AI tag (" AI") and replace it with " (AI)"
         playerName = playerName.substr(
            0, playerName.length() - std::string(AI_NAMETAG).length());
         playerName = playerName + " (AI)";
      }
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

void Game::playGame(bool& hasQuit)
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
            if (players[i]->getAIStatus() == false)
            {
               validInput = parseUserInput(gameRunning, hasQuit, i);
            }
            else
            {
               playBestMove(players[i]);
               validInput = true;
            }
            // checking if the current player's hand is empty. if both are true,
            // then the game is over!
            if (players[i]->isEmptyHand())
            {
               finaliseGame(players[i]);
               gameRunning = false;
            }
         }
      }
   }
}

void Game::printGameState(Player* player)
{
   std::cout << std::endl;
   board->printBoard(colourPrinting);
   std::cout << player->getName() << ", it's your turn" << std::endl;
   for (int i = 0; i < numPlayers; i++)
   {
      std::cout << "Score for " << players[i]->getName() << ": "
                << players[i]->getScore() << std::endl;
   }
   std::cout << std::endl;
   std::cout << "Your hand is" << std::endl;
   std::cout << player->getHandStr(this->colourPrinting) << std::endl;
}

bool Game::customSaveGame(Player* player, std::string saveFileName)
{
   bool canSave = false;
   std::ofstream saveFile(saveFileName + ".save");

   if (saveFile.good())
   {
      saveFile << "#myFormat" << std::endl;
      saveFile << numPlayers << std::endl;
      for (int i = 0; i < numPlayers; i++)
      {
         saveFile << players[i]->getName() << std::endl;
         saveFile << players[i]->getScore() << std::endl;
         saveFile << players[i]->getHandStr(false) << std::endl;
         saveFile << players[i]->getAIStatus() << std::endl;
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
         saveFile << players[i]->getHandStr(false) << std::endl;
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

bool Game::isValidName(std::string name, int currNameIndex)
{
   int length   = name.length();
   bool isValid = true;

   if (length == 0)
   {
      isValid = false;
   }

   // check every character in the name for any invalid characters
   for (int i = 0; i < length && isValid; i++)
   {
      // TODO
      // if (!isupper(name[i]) && name[i] != ' ')
      if (!isalnum(name[i]) && name[i] != ' ')
      {
         isValid = false;
      }
   }

   if (isValid && currNameIndex > 0)
   {
      for (int i = 0; i < currNameIndex; i++)
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

   // validate tiles from a0-z9
   if (coordinate.size() == 2)
   {
      std::string str = "";
      for (char row = 'A'; row <= 'Z'; row++)
      {
         if (coordinate[0] == row)
         {
            str.push_back(coordinate[1]);
            int col = atoi(str.c_str());
            if (col >= 0 && col <= 9)
            {
               isValid = true;
            }
         }
      }
   }
   // validate tiles from a10-z25
   else if (coordinate.size() == 3)
   {
      std::string str = "";
      for (char row = 'A'; row <= 'Z'; row++)
      {
         if (coordinate[0] == row)
         {
            str.push_back(coordinate[1]);
            str.push_back(coordinate[2]);
            int col = atoi(str.c_str());
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

bool Game::placeTileCommand(std::vector<std::string> rawCommand, int currPlayer)
{
   bool validInput                 = false;
   std::string tileToPlace         = rawCommand[1];
   std::string placementCoordinate = rawCommand[3];

   if (isValidTileInHand(players[currPlayer], tileToPlace) &&
       isValidCoordinate(placementCoordinate))
   {
      int coordX = getColFromCoordinate(placementCoordinate);
      int coordY = getRowFromCoordinate(placementCoordinate);

      Tile* toPlace = players[currPlayer]->getTileFromHand(tileToPlace);

      bool isFirstTile = board->isFirstTile();

      if (board->placeTile(toPlace, coordX, coordY))
      {
         validInput = true;

         if (isFirstTile)
         {
            players[currPlayer]->addScore(1);
         }
         else
         {
            int verticalScore = board->calculateScoreVertical(coordX, coordY);
            int horizontalScore =
               board->calculateScoreHorizontal(coordX, coordY);
            // If qwirkle or double qwirkle
            if (verticalScore == 12 && horizontalScore == 12)
            {
               std::cout << "DOUBLE QWIRKLE!!!!" << std::endl;
            }
            else if (verticalScore == 12 || horizontalScore == 12)
            {
               std::cout << "QWIRKLE!!!" << std::endl;
            }
            players[currPlayer]->addScore(verticalScore + horizontalScore);
         }

         players[currPlayer]->drawTile();
      }
      else
      {
         // return piece to hand (tile is in hand but invalid
         // placement)
         players[currPlayer]->addToHand(toPlace);
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
   return validInput;
}

bool Game::replaceTileCommand(
   std::vector<std::string> rawCommand, int currPlayer)
{
   bool validInput        = false;
   std::string tileToSwap = rawCommand[1];

   if (!bag->getTilesInBag()->isEmpty())
   {
      if (players[currPlayer]->swapTile(tileToSwap))
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
   return validInput;
}

void Game::saveGameCommand(std::vector<std::string> rawCommand,
   std::vector<std::string> rawSaveCommand, int currPlayer)
{
   if (rawCommand.size() == 2)
   {
      std::string saveFileName = rawSaveCommand[1];
      if (numPlayers != 2 || colourPrinting || AIMode)
      {
         if (customSaveGame(players[currPlayer], saveFileName))
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
         if (saveGame(players[currPlayer], saveFileName))
         {
            std::cout << "Game successfully saved" << std::endl;
         }
         else
         {
            throw std::invalid_argument(
               "The game could not be saved. Please try again.");
         }
      }
   }
   else
   {
      throw std::invalid_argument("Usage: save <filename>");
   }
}

void Game::helpCommand()
{
   std::cout << "You may use the following (case insensitive) commands."
             << std::endl;
   std::cout << "-----------------------------------------------" << std::endl;
   std::cout << "Placing a tile:     place <tile> at <location>" << std::endl;
   std::cout << "Replacing a tile:   replace <tile>" << std::endl;
   std::cout << "Getting a hint:     hint" << std::endl;
   std::cout << "Saving the game:    save <filename or relative "
                "filepath>"
             << std::endl;
   std::cout << "Returning to menu:  menu" << std::endl;
   std::cout << "Quitting the game:  quit" << std::endl;
}

void Game::finaliseGame(Player* player)
{
   // Player who places their last tile first gets 6 extra points
   // TODO
   // players[currPlayer]->addScore(6);
   player->addScore(6);
   bool isDraw = false;

   board->printBoard(colourPrinting);

   std::cout << "Game over!!" << std::endl;

   // Set the winner initially to the first player
   Player* winner = players[0];

   // find player with the highest score (or draw)
   for (int i = 0; i < numPlayers; i++)
   {
      if (players[i]->getScore() > winner->getScore())
      {
         isDraw = false;
         winner = players[i];
      }
      // winner is initially player index 0, so do not compare this case
      else if (i != 0 && players[i]->getScore() == winner->getScore())
      {
         isDraw = true;
      }
      std::cout << "Score for " << players[i]->getName() << ": "
                << players[i]->getScore() << std::endl;
   }

   if (!isDraw)
   {
      std::cout << winner->getName() << " won with a score of "
                << winner->getScore() << "!" << std::endl
                << std::endl;
   }
   else
   {
      std::cout << "It's a draw!" << std::endl << std::endl;
   }
}

bool Game::parseUserInput(
   bool& gameRunning, bool& hasQuit, int currentPlayerIndex)
{
   std::string rawUserInput = "";
   bool validInput          = false;

   try
   {
      std::cout << std::endl;
      std::cout << "> ";
      getline(std::cin, rawUserInput);

      // Splitting up rawUserInput based on delimiter (spaces)
      // This specific splitString() is for case-sensitive save files
      std::vector<std::string> rawSaveCommand = splitString(rawUserInput, ' ');

      // Converting the rawUserInput into all uppercase
      std::transform(rawUserInput.begin(), rawUserInput.end(),
         rawUserInput.begin(), ::toupper);

      // Splitting up rawUserInput based on delimiter (spaces)
      std::vector<std::string> rawCommand = splitString(rawUserInput, ' ');

      std::string command = "";
      if (rawCommand.size() > 0)
      {
         command = rawCommand[0];
      }

      // placing a tile
      if (command == PLACE && rawCommand.size() == 4 && rawCommand[2] == "AT")
      {
         validInput = placeTileCommand(rawCommand, currentPlayerIndex);
      }
      // replacing a tile
      else if (command == REPLACE && rawCommand.size() == 2)
      {
         validInput = replaceTileCommand(rawCommand, currentPlayerIndex);
      }
      // saving the game
      else if (command == SAVE)
      {
         saveGameCommand(rawCommand, rawSaveCommand, currentPlayerIndex);
      }
      // providing help text
      else if (command == HELP)
      {
         helpCommand();
      }
      else if (command == HINT)
      {
         printHint(players[currentPlayerIndex]);
      }
      else if (command == MENU)
      {
         std::cout << std::endl;
         gameRunning = false;
      }
      // quitting the game
      else if (command == QUITGAME)
      {
         validInput  = true;
         gameRunning = false;
         hasQuit     = true;
         printQuitMessage();
      }
      // eof character
      else if (std::cin.eof())
      {
         std::cout << std::endl;
         validInput  = true;
         gameRunning = false;
      }
      // no command
      else if (command.empty())
      {
         throw std::invalid_argument("Please enter a command.");
      }
      // incorrectly formatted command
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

   return validInput;
}

bool Game::isAIName(std::string playerName)
{
   bool isAIName        = false;
   int playerNameLength = playerName.length();
   int aiTagLength      = std::string(AI_NAMETAG).length();
   // if the length of the player name is greater than the ai tag (" AI")
   if (playerNameLength > aiTagLength)
   {
      // if the player name ends with " AI"
      if (playerName.substr(playerNameLength - aiTagLength, aiTagLength)
             .compare(AI_NAMETAG) == 0)
      {
         isAIName = true;
      }
   }

   return isAIName;
}

bool Game::playBestMove(Player* player)
{
   bool hasPlayedMove  = false;
   Tile* iterationTile = nullptr;
   // declare variables to store values of the best move
   int highestScorePossible = 0;
   Tile* highestTile        = nullptr;
   int highestColPosition   = 0;
   int highestRowPosition   = 0;
   int highestTileIndex     = 0;

   // if ai is making the first move
   if (board->isFirstTile())
   {
      // select a random tile on the board and place there
      srand(time(0));
      int randRow = std::rand() % board->getDimRows();
      int randCol = std::rand() % board->getDimCols();
      board->placeTile(player->getHand()->grab(0), randCol, randRow);
   }
   else
   {
      // every space on the board (across and then down)
      for (int col = 0; col < board->getDimCols() && !hasPlayedMove; col++)
      {
         for (int row = 0; row < board->getDimRows() && !hasPlayedMove; row++)
         {
            // if current position is a valid spot to place a tile
            if (board->getTilesOnBoard()[row][col] == nullptr &&
                board->hasAdjacent(col, row))
            {
               // every tile in current player's hand
               for (int i = 0;
                    i < player->getHand()->getSize() && !hasPlayedMove; i++)
               {
                  // get the tile at the index of the iteration
                  iterationTile = player->getHand()->getTileAtIndex(i);
                  // if tile can be placed at the current location on the board
                  if (board->canPlaceHorizontal(iterationTile, col, row) &&
                      board->canPlaceVertical(iterationTile, col, row))
                  {
                     // calculate score of move and check if it is higher than
                     // highest
                     int verticalScore =
                        board->calculateScoreVertical(col, row);
                     int horizontalScore =
                        board->calculateScoreHorizontal(col, row);
                     int score = verticalScore + horizontalScore;
                     if (score > highestScorePossible)
                     {
                        // if it is the best move yet, set the variables to
                        // store this location and tile
                        highestScorePossible = score;
                        highestTile          = iterationTile;
                        highestColPosition   = col;
                        highestRowPosition   = row;
                        highestTileIndex     = i;
                     }
                  }
               }
            }
         }
      }

      // once the scanning is complete, place the highest scoring tile
      if (board->placeTile(highestTile, highestColPosition, highestRowPosition))
      {
         player->getHand()->grab(highestTileIndex);
         int verticalScore = board->calculateScoreVertical(
            highestColPosition, highestRowPosition);
         int horizontalScore = board->calculateScoreHorizontal(
            highestColPosition, highestRowPosition);
         int score = verticalScore + horizontalScore;
         player->addScore(score);
         player->drawTile();
         hasPlayedMove = true;
      }
      // if there is no tile found to be placed
      else
      {
         // replace first tile in hand
         if (!bag->getTilesInBag()->isEmpty())
         {
            player->swapTile(player->getHand()->getTileAtIndex(0)->toString());
         }
         else
         {
            finaliseGame(player);
         }
      }
   }

   return hasPlayedMove;
}

void Game::printHint(Player* player)
{
   // declare variables to store values of the best move
   int lowestScorePossible = INT8_MAX;
   Tile* lowestTile        = nullptr;
   int lowestColPosition   = 0;
   int lowestRowPosition   = 0;
   bool isPossibleMove     = false;

   if (board->isFirstTile())
   {
      std::cout << "There are no tiles on the board, you may place any tile "
                   "anywhere you like!"
                << std::endl;
   }
   else
   {
      // every space on the board (across and then down)
      for (int col = 0; col < board->getDimCols(); col++)
      {
         for (int row = 0; row < board->getDimRows(); row++)
         {
            if (board->getTilesOnBoard()[row][col] == nullptr &&
                board->hasAdjacent(col, row))
            {
               // every tile in current player's hand
               for (int i = 0; i < player->getHand()->getSize(); i++)
               {
                  // get the tile at the index of the iteration
                  Tile* iterationTile = player->getHand()->getTileAtIndex(i);

                  // if tile can be placed at the current location on the board
                  if (board->canPlaceHorizontal(iterationTile, col, row) &&
                      board->canPlaceVertical(iterationTile, col, row))
                  {
                     isPossibleMove = true;
                     // calculate score of move and check if it is higher than
                     // highest
                     int verticalScore =
                        board->calculateScoreVertical(col, row);
                     int horizontalScore =
                        board->calculateScoreHorizontal(col, row);
                     int score = verticalScore + horizontalScore;
                     if (score < lowestScorePossible)
                     {
                        // if it is the best move yet, set the variables to
                        // store this location and tile
                        lowestScorePossible = score;
                        lowestTile          = iterationTile;
                        lowestColPosition   = col;
                        lowestRowPosition   = row;
                     }
                  }
               }
            }
         }
      }

      if (isPossibleMove)
      {
         std::cout << "Psst! You could place tile " << lowestTile->toString()
                   << " at " << static_cast<char>(lowestRowPosition + 65)
                   << lowestColPosition << "!" << std::endl;
      }
      else
      {
         std::cout << "Hmmm, it looks like you don't have any possible moves "
                      "right now. Try replacing a tile."
                   << std::endl;
      }
   }
}

void Game::setAIMode(bool AIMode)
{
   this->AIMode = AIMode;
}
