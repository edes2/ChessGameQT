#include "Pawn.hpp"

Pawn::Pawn()
{
	mType = pawn;
}

bool Pawn::estMovementValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
{
	if (destination.x == mPosition.x)
	{
		if (mSide == white && (destination.y < mPosition.y))
		{
			if (mPosition.y == 6)
			{
				if (destination.y >= mPosition.y - 2 && !tiles[Coordonnees(mPosition.x, mPosition.y - 1)])
				{
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
				if (destination.y <= mPosition.y + 2 && !tiles[Coordonnees(mPosition.x,mPosition.y+1)])
				{
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

bool Pawn::estAttaqueValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)//std::pair<int, int> destination) //= 0;
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