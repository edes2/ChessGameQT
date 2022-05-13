#include "King.hpp"

King::King()
{
	mType = king;
}

King::~King()
{
}

bool King::estMovementValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
{
	if ((abs(destination.x - mPosition.x) <= 1) && (abs(destination.y - mPosition.y) <= 1))
	{
		return true;
	}
	return false;
}
bool King::estAttaqueValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
{
	// Castling
	if (!mHasMoved) 
	{
		if (!tiles[destination]) { return false; }
		if (tiles[destination]->getSide() == mSide && tiles[destination]->getType() == rook)
		{
			if (tiles[destination]->getHasMoved() == false)
			{
				Coordonnees diff(destination.x - mPosition.x, destination.y - mPosition.y);
				if (diff.y == 0)
				{
					int i = 0;
					int j = 0;
					if (diff.x != 0)
					{
						i = diff.x / abs(diff.x) * -1;
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
		}
	}
	if (estMovementValide(destination, tiles) && tiles[destination] && tiles[destination]->getSide() != mSide)
	{
		return true;
	}
	return false;
}

QString King::getImagePath() {
	QString path;
	if (mSide == white) {
		path = "images/WhiteKing.png";
	}
	else
	{
		path = "images/BlackKing.png";
	}
	return path;
}