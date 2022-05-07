#include "Knight.hpp"

Knight::Knight()
{
	type_ = knight;
}

bool Knight::estMovementValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
{
	if ((abs(destination.x - position_.x) == 2) && (abs(destination.y - position_.y) == 1))
	{
		return true;
	}
	if ((abs(destination.x - position_.x) == 1) && (abs(destination.y - position_.y) == 2))
	{
		return true;
	}
	return false;
}

bool Knight::estAttaqueValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
{
	if (tiles[destination]->getSide() == side_)
	{
		return false;
	}
	return estMovementValide(destination, tiles);
}

QString Knight::getImagePath() {
	QString path;
	if (side_ == white) {
		path = "images/WhiteKnight.png";
	}
	else
	{
		path = "images/BlackKnight.png";
	}
	return path;
}