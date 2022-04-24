#include "Rook.hpp"

Rook::Rook()
{

}


bool Rook::estMovementValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
{
	return false;
}
bool Rook::estAttaqueValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
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