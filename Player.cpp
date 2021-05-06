#include "Player.hpp"

Player::Player()
    : bag(nullptr)
    , board(nullptr)
    , hand(new LinkedList())
    , name("")
    , score(0)
{
}

Player::Player(std::string playerInfo)
{
   /**
    * playeronename
    * playeronescore
    * playeronehand
    */

   std::string newName = "";
   // this->setName(std::getline(playerInfo, newName));
}

Player::~Player()
{
   while (!hand->isEmpty())
   {
      delete hand->pop();
   }

   delete hand;
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