#include "Queen.hpp"

Queen::Queen()
{

}

std::vector<Coordonnees> Queen::attaquesPossibles(std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
{
	std::vector<Coordonnees> attaques;

	return attaques;
}

std::vector<Coordonnees> Queen::movementsPossibles(std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
{
	std::vector<Coordonnees> x;
	return x;
}

bool Queen::estMovementValide(Coordonnees destination)
{
	return false;
}
bool Queen::estAttaqueValide(Coordonnees destination)
{
	return false;
}

QString Queen::getImagePath() {
	QString path;
	if (side_ == white) {
		path = "50px/WhiteQueen.png";
	}
	else
	{
		path = "50px/BlackQueen.png";
	}
	return path;
}