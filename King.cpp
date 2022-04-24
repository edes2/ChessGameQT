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
	return false;
}
bool King::estAttaqueValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
{
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