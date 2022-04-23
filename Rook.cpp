#include "Rook.hpp"

Rook::Rook()
{

}

std::vector<Coordonnees> Rook::attaquesPossibles(std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
{
	std::vector<Coordonnees> attaques;

	return attaques;
}

std::vector<Coordonnees> Rook::movementsPossibles(std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
{
	std::vector<Coordonnees> x;
	return x;
}

bool Rook::estMovementValide(Coordonnees destination)
{
	return false;
}
bool Rook::estAttaqueValide(Coordonnees destination)
{
	return false;
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