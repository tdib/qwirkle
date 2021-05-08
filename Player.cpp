#include "Player.hpp"

Player::Player()
    : bag(nullptr)
    , board(nullptr)
    , hand(new LinkedList())
    , name("")
    , score(0)
{
}

Player::Player(std::string playerName, int playerScore, std::string playerHand)
{
   this->bag   = nullptr;
   this->board = nullptr;
   this->hand  = new LinkedList();
   this->name  = playerName;
   this->score = playerScore;
   this->setHand(playerHand);
}

Player::~Player()
{
   while (!hand->isEmpty())
   {
      delete hand->pop();
   }

   delete hand;
}

void Player::setHand(std::string newHand)
{
   // create stringstream and iterate through, adding each tile to hand
   std::stringstream handTiles(newHand);
   while (handTiles.good())
   {
      std::string currTile = "";
      std::getline(handTiles, currTile, ',');
      Colour tileColour     = currTile[0];
      std::string toConvert = "";
      toConvert.push_back(currTile[1]);
      Shape tileShape = atoi(toConvert.c_str());

      Colour colours[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
      Shape shapes[]   = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};
      // check if tile is valid
      std::cout << tileColour << std::endl;
      std::cout << tileShape << std::endl;

      for (Colour colour : colours)
      {
         for (Shape shape : shapes)
         {
            if (tileShape == shape && tileColour == colour)
            {
               std::cout << "Adding " << tileColour << tileShape << " to hand."
                         << std::endl;
               this->hand->push(new Tile(tileShape, tileColour));
            }
         }
      }
   }
   // iterate through each tile in the string
   // validate tile
   // push tile to back of hand linkedlist
}

void Player::setBag(Bag* bag)
{
   this->bag = bag;
}

void Player::setBoard(Board* board)
{
   this->board = board;
}

bool Player::drawTile()
{
   bool canDraw = false;
   if (!bag->getTilesInBag()->isEmpty())
   {
      canDraw         = true;
      Tile* drawnTile = nullptr;

      drawnTile = bag->popTile();
      hand->push(drawnTile);
   }

   return canDraw;
}

bool Player::placeTile(Tile* tile, std::string coordinate)
{
   return false;
}

bool Player::swapTile(std::string tileToSwap)
{
   bool matchingTile = false;
   int tileIndex     = hand->findTileIndex(tileToSwap);

   if (tileIndex != -1)
   {
      Tile* tempTile = hand->grab(tileIndex);
      bag->pushTile(tempTile);
      drawTile();

      matchingTile = true;
   }

   return matchingTile;
}

void Player::addScore(int score)
{
}

std::string Player::getName()
{
   return this->name;
}

void Player::setName(std::string newName)
{
   this->name = newName;
}

int Player::getScore()
{
   return this->score;
}

std::string Player::getHand()
{
   return hand->getContents();
}

bool Player::isEmptyHand()
{
   return hand->isEmpty();
}

bool Player::tileInHand(std::string tileToValidate)
{
   return (hand->findTileIndex(tileToValidate) != -1);
}

Tile* Player::getTileFromHand(std::string tileToGet)
{
   Tile* tempTile = nullptr;
   int tileIndex  = hand->findTileIndex(tileToGet);

   if (tileIndex != -1)
   {
      tempTile = hand->grab(tileIndex);
   }

   return tempTile;
}