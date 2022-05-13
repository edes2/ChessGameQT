#include "Bishop.hpp"

Bishop::Bishop()
{
	mType = bishop;
}

bool Bishop::estMovementValide(Coordinates destination, std::map<Coordinates, std::shared_ptr<ChessPiece>> tiles) {
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
		Coordinates coordonnees(destination.x, destination.y);
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

bool Bishop::estAttaqueValide(Coordinates destination, std::map<Coordinates, std::shared_ptr<ChessPiece>> tiles)
{
	if (tiles[destination]->getSide() == mSide)
	{
		return false;
	}
	if (estMovementValide(destination, tiles))
	{
		return true;
	}
	return false;
}

QString Bishop::getImagePath() {
	QString path;
	if (mSide == white) {
		path = "images/WhiteBishop.png";
	}
	else
	{
		path = "images/BlackBishop.png";
	}
	return path;
}