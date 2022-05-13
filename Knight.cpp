#include "Knight.hpp"

Knight::Knight()
{
	mType = knight;
}

bool Knight::estMovementValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
{
	if ((abs(destination.x - mPosition.x) == 2) && (abs(destination.y - mPosition.y) == 1))
	{
		return true;
	}
	if ((abs(destination.x - mPosition.x) == 1) && (abs(destination.y - mPosition.y) == 2))
	{
		return true;
	}
	return false;
}

bool Knight::estAttaqueValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
{
	if (tiles[destination]->getSide() == mSide)
	{
		return false;
	}
	return estMovementValide(destination, tiles);
}

QString Knight::getImagePath() {
	QString path;
	if (mSide == white) {
		path = "images/WhiteKnight.png";
	}
	else
	{
		path = "images/BlackKnight.png";
	}
	return path;
}