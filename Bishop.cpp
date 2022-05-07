#include "Bishop.hpp"

Bishop::Bishop()
{
	type_ = bishop;
}

bool Bishop::estMovementValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles) {
	int diffx = destination.x - position_.x;
	int diffy = destination.y - position_.y;
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
		while (coordonnees.x != position_.x && coordonnees.y != position_.y)
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

bool Bishop::estAttaqueValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
{
	if (tiles[destination]->getSide() == side_)
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
	if (side_ == white) {
		path = "images/WhiteBishop.png";
	}
	else
	{
		path = "images/BlackBishop.png";
	}
	return path;
}