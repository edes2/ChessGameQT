#include "King.hpp"

int King::compteur = 0;

King::King()
{
	if (compteur >= 2)
	{
		throw MoreThanTwoKings();
	}
	++compteur;
	type_ = king;
}

King::~King()
{
	--compteur;
}

bool King::estMovementValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
{
	if ((abs(destination.x - position_.x) <= 1) && (abs(destination.y - position_.y) <= 1))
	{
		return true;
	}
	return false;
}
bool King::estAttaqueValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
{
	// Castling
	if (!hasMoved_) 
	{
		if (!tiles[destination]) { return false; }
		if (tiles[destination]->getSide() == side_ && tiles[destination]->getType() == rook)
		{
			if (tiles[destination]->getHasMoved() == false)
			{
				Coordonnees diff(destination.x - position_.x, destination.y - position_.y);
				if (diff.y == 0)
				{
					int i = 0;
					int j = 0;
					if (diff.x != 0)
					{
						i = diff.x / abs(diff.x) * -1;
					}

					Coordonnees coord(destination.x, destination.y);
					while (coord.x != position_.x || coord.y != position_.y)
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
	if (estMovementValide(destination, tiles) && tiles[destination] && tiles[destination]->getSide() != side_)
	{
		return true;
	}
	return false;
}

QString King::getImagePath() {
	QString path;
	if (side_ == white) {
		path = "images/WhiteKing.png";
	}
	else
	{
		path = "images/BlackKing.png";
	}
	return path;
}