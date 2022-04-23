#include "Bishop.hpp"

Bishop::Bishop()
{

}

std::vector<Coordonnees> Bishop::attaquesPossibles(std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
{
	std::vector<Coordonnees> attaques;
	
	return attaques;
}

std::vector<Coordonnees> Bishop::movementsPossibles(std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
{
	std::vector<Coordonnees> mouvements;
	for (int x = position_.x; x < 8; x++)
	{
		for (int y = position_.y; y < 8; y++)
		{
			Coordonnees coordonnees(x, y);
			if (tiles[coordonnees])
			{
				break;
			}
			mouvements.push_back(coordonnees);
		}
	}
	for (int x = position_.x; x >= 0; x--)
	{
		for (int y = position_.y; y < 8; y++)
		{
			Coordonnees coordonnees(x, y);
			if (tiles[coordonnees])
			{
				break;
			}
			mouvements.push_back(coordonnees);
		}
	}
	for (int x = position_.x; x < 8; x++)
	{
		for (int y = position_.y; y >= 0; y--)
		{
			Coordonnees coordonnees(x, y);
			if (tiles[coordonnees])
			{
				break;
			}
			mouvements.push_back(coordonnees);
		}
	}
	for (int x = position_.x; x >= 0; x--)
	{
		for (int y = position_.y; y >= 0; y--)
		{
			Coordonnees coordonnees(x, y);
			if (tiles[coordonnees])
			{
				break;
			}
			mouvements.push_back(coordonnees);
		}
	}
	return mouvements;
}

bool Bishop::estMovementValide(Coordonnees destination) {
	return false;
}

bool Bishop::estAttaqueValide(Coordonnees destination) {
	return false;
}

QString Bishop::getImagePath() {
	QString path;
	if (side_ == white) {
		path = "50px/WhiteBishop.png";
	}
	else
	{
		path = "50px/BlackBishop.png";
	}
	return path;
}