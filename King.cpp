#include "King.hpp"

int King::compteur = 0;

King::King()
{
	if (compteur >= 2)
	{
		throw MoreThanTwoKings();
	}
	++compteur;
}

King::~King()
{
	--compteur;
}

//std::vector<Coordonnees> King::attaquesPossibles(std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
//{
//	std::vector<Coordonnees> attaques;
//
//	return attaques;
//}
//
//std::vector<Coordonnees> King::movementsPossibles(std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
//{
//	std::vector<Coordonnees> x;
//	return x;
//}

bool King::estMovementValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
{

	//si mov valide, verifier si echec
	if ((abs(destination.x - position_.x) <= 1) && (abs(destination.y - position_.y) <= 1))
	{
		return true;
	}
	return false;
}
bool King::estAttaqueValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
{
	if (estMovementValide(destination, tiles) && tiles[destination]->getSide() != side_)
	{
		return true;
	}
	return false;
}

QString King::getImagePath() {
	QString path;
	if (side_ == white) {
		path = "50px/WhiteKing.png";
	}
	else
	{
		path = "50px/BlackKing.png";
	}
	return path;
}