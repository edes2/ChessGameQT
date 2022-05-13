#include "Queen.hpp"

Queen::Queen()
{
	mType = queen;
}

bool Queen::checkDiagonalMov(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles) 
{
	int diffx = destination.x - mPosition.x;
	int diffy = destination.y - mPosition.y;
	if (abs(diffx) == abs(diffy)) {
		int i;
		int j;
		if (diffx < 0)
		{
			i = 1;
		}
		else
		{
			i = -1;
		}
		if (diffy < 0)
		{
			j = 1;
		}
		else
		{
			j = -1;
		}
		Coordonnees coordonnees(destination.x, destination.y);
		while (coordonnees.x != mPosition.x && coordonnees.y != mPosition.y)
		{
			if (tiles[coordonnees] && tiles[coordonnees] != tiles[destination])
			{
				return false;
			}
			coordonnees.x += i;
			coordonnees.y += j;
		}
		return true;
	}

	return false;
}
bool Queen::checkStraightMov(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
{
	Coordonnees diff(destination.x - mPosition.x, destination.y - mPosition.y);
	if (diff.x == 0 || diff.y == 0)
	{
		int i = 0;
		int j = 0;
		if (diff.x != 0)
		{
			i = diff.x / abs(diff.x) * -1;
		}
		if (diff.y != 0)
		{
			j = diff.y / abs(diff.y) * -1;
		}
		Coordonnees coord(destination.x, destination.y);
		while (coord.x != mPosition.x || coord.y != mPosition.y)
		{
			if (tiles[coord] && tiles[coord] != tiles[destination])
			{
				return false;
			}
			coord.x += i;
			coord.y += j;
		}
		return true;
	}
	return false;
}

bool Queen::estMovementValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
{
	if (checkDiagonalMov(destination, tiles) || checkStraightMov(destination, tiles))
	{
		return true;
	}
	return false;
}
bool Queen::estAttaqueValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
{
	if (tiles[destination]->getSide() == mSide)
	{
		return false;
	}
	return estMovementValide(destination, tiles);
}

QString Queen::getImagePath() {
	QString path;
	if (mSide == white) {
		path = "images/WhiteQueen.png";
	}
	else
	{
		path = "images/BlackQueen.png";
	}
	return path;
}