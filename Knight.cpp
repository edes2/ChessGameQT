#include "Knight.hpp"

Knight::Knight()
{

}

std::vector<Coordonnees> Knight::attaquesPossibles(std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
{
	std::vector<Coordonnees> attaques;

	return attaques;
}

std::vector<Coordonnees> Knight::movementsPossibles(std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
{
	std::vector<Coordonnees> x;
	return x;
}

bool Knight::estMovementValide(Coordonnees destination)
{
	return false;
}
bool Knight::estAttaqueValide(Coordonnees destination)
{
	return false;
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