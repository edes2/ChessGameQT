#include "Queen.hpp"

Queen::Queen()
{

}


bool Queen::estMovementValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
{
	return false;
}
bool Queen::estAttaqueValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
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