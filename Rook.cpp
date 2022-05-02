#include "Rook.hpp"

bool Rook::estMovementValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
{
	Coordonnees diff(destination.x - position_.x, destination.y - position_.y);
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
bool Rook::estAttaqueValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
{
	return estMovementValide(destination, tiles);
}

QString Rook::getImagePath() {
	QString path;
	if (side_ == white) {
		path = "50px/WhiteRook.png";
	}
	else
	{
		path = "50px/BlackRook.png";
	}
	return path;
}