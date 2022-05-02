#include "Knight.hpp"

// on sait deja que case appuyee est vide
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

// on sait que case appuye est piece
bool Knight::estAttaqueValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
{
	return estMovementValide(destination, tiles);
}

QString Knight::getImagePath() {
	QString path;
	if (side_ == white) {
		path = "50px/WhiteKnight.png";
	}
	else
	{
		path = "50px/BlackKnight.png";
	}
	return path;
}