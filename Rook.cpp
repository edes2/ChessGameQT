#include "Rook.hpp"

Rook::Rook()
{
	mType = rook;
}

bool Rook::estMovementValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
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
		if (!mHasMoved) { mHasMoved = true; }
		return true;
	}
	return false;
}
bool Rook::estAttaqueValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
{
	if (tiles[destination]->getSide() == mSide)
	{
		return false;
	}
	return estMovementValide(destination, tiles);
}

QString Rook::getImagePath() {
	QString path;
	if (mSide == white) {
		path = "images/WhiteRook.png";
	}
	else
	{
		path = "images/BlackRook.png";
	}
	return path;
}