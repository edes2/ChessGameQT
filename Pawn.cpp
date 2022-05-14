#include "Pawn.hpp"

Pawn::Pawn() : movedTwoTiles(false)
{
	mType = pawn;
}

bool Pawn::estMovementValide(Coordinates destination, std::map<Coordinates, std::shared_ptr<ChessPiece>> tiles)
{
  if (isEnPassant(destination, tiles))
  {
    return true;
  }
	if (destination.x == mPosition.x)
	{
		if (mSide == white && (destination.y < mPosition.y))
		{
			if (mPosition.y == 6)
			{
				if (destination.y >= mPosition.y - 2 && !tiles[Coordinates(mPosition.x, mPosition.y - 1)])
				{
          movedTwoTiles = true;
					return true;
				}
			}
			else
			{
				if (destination.y == mPosition.y - 1)
				{
					return true;
				}
			}
		}
		else if (mSide == black && (destination.y > mPosition.y))
		{
			if (mPosition.y == 1)
			{
				if (destination.y <= mPosition.y + 2 && !tiles[Coordinates(mPosition.x,mPosition.y+1)])
				{
          movedTwoTiles = true;
					return true;
				}
			}
			else
			{
				if (destination.y == mPosition.y + 1)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool Pawn::estAttaqueValide(Coordinates destination, std::map<Coordinates, std::shared_ptr<ChessPiece>> tiles)//std::pair<int, int> destination) //= 0;
{
	if (tiles[destination]->getSide() == mSide)
	{
		return false;
	}
	if (mSide == white)
	{
		if (((destination.x == mPosition.x + 1) && (destination.y == mPosition.y - 1)) || ((destination.x == mPosition.x - 1) && (destination.y == mPosition.y - 1)))
		{
			return true;
		}
	}
	else
	{
		if (((destination.x == mPosition.x + 1) && (destination.y == mPosition.y + 1)) || ((destination.x == mPosition.x - 1) && (destination.y == mPosition.y + 1)))
		{
			return true;
		}
	}
	return false;
}

bool Pawn::isEnPassant(Coordinates destination, std::map<Coordinates, std::shared_ptr<ChessPiece>> tiles)
{
  Coordinates pawnPos1 = mPosition;
  Coordinates pawnPos2 = mPosition;

  if (mSide == white)
  {
    if ((destination == (pawnPos1 + Coordinates(1, -1))) || (destination == (pawnPos2 + Coordinates(-1, -1))))
    {
      Coordinates enemyPawn = destination + Coordinates(0, 1);
      if (tiles[enemyPawn]
        && tiles[enemyPawn]->getType() == pawn
        && tiles[enemyPawn]->getSide() != mSide
        )
      {
        Pawn* pPawn = dynamic_cast<Pawn*>(tiles[enemyPawn].get()); // pas sur que ca marche
        if (pPawn)
        {
          if (pPawn->movedTwoTiles)
          {
            mIsMoveEnPassant = true;
            return true;
          }
        }
      }
    }
  }
  else
  {
    if ((destination == (pawnPos1 + Coordinates(1, 1))) || (destination == (pawnPos2 + Coordinates(-1, 1))))
    {
      Coordinates enemyPawn = destination + Coordinates(0, -1);
      if (tiles[enemyPawn]
        && tiles[enemyPawn]->getType() == pawn
        && tiles[enemyPawn]->getSide() != mSide
        )
      {
        Pawn* pPawn = dynamic_cast<Pawn*>(tiles[enemyPawn].get()); // pas sur que ca marche
        if (pPawn)
        {
          if (pPawn->movedTwoTiles)
          {
            mIsMoveEnPassant = true;
            return true;
          }
        }
      }
    }
  }
  mIsMoveEnPassant = false;
  return false;
}

QString Pawn::getImagePath() {
	QString path;
	if (mSide == white) {
		path = "images/WhitePawn.png";
	}
	else
	{
		path = "images/BlackPawn.png";
	}
	return path;
}