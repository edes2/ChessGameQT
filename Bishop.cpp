#include "Bishop.hpp"

Bishop::Bishop()
{

}

//std::vector<Coordonnees> Bishop::attaquesPossibles(std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
//{
//	std::vector<Coordonnees> attaques;
//	
//	return attaques;
//}

//std::vector<Coordonnees> Bishop::movementsPossibles(std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
//{
//	std::vector<Coordonnees> mouvements;
//	int x = position_.x, y = position_.y; 
//	Coordonnees coordonnees(position_.x+1, position_.y+1);
//	while (!tiles[coordonnees] || coordonnees.x < 8 || coordonnees.y < 8) // BAS-DROITE
//	{
//		mouvements.push_back(coordonnees);
//		coordonnees.x++;
//		coordonnees.y++;
//	}
//	coordonnees.x = position_.x - 1;
//	coordonnees.y = position_.y + 1;
//	while (!tiles[coordonnees] || coordonnees.x >= 0 || coordonnees.y < 8) // BAS-GAUCHE
//	{
//		mouvements.push_back(coordonnees);
//		coordonnees.x--;
//		coordonnees.y++;
//	}
//	coordonnees.x = x - 1;
//	coordonnees.y = y - 1;
//	while (!tiles[coordonnees] || coordonnees.x >= 0 || coordonnees.y >= 0) // HAUT-GAUCHE
//	{
//
//		mouvements.push_back(coordonnees);
//		coordonnees.x--;
//		coordonnees.y--;
//	}
//	coordonnees.x = x + 1;
//	coordonnees.y = y - 1;
//	while (!tiles[coordonnees] || coordonnees.x < 8 || coordonnees.y >= 0) // HAUT-DROITE
//	{
//
//		mouvements.push_back(coordonnees);
//		coordonnees.x++;
//		coordonnees.y--;
//	}
//
//	/*for (int x = position_.x; x < 8; x++)
//	{
//		for (int y = position_.y; y < 8; y++)
//		{
//			Coordonnees coordonnees(x, y);
//			if (tiles[coordonnees])
//			{
//				break;
//			}
//			mouvements.push_back(coordonnees);
//		}
//	}
//	for (int x = position_.x; x >= 0; x--)
//	{
//		for (int y = position_.y; y < 8; y++)
//		{
//			Coordonnees coordonnees(x, y);
//			if (tiles[coordonnees])
//			{
//				break;
//			}
//			mouvements.push_back(coordonnees);
//		}
//	}
//	for (int x = position_.x; x < 8; x++)
//	{
//		for (int y = position_.y; y >= 0; y--)
//		{
//			Coordonnees coordonnees(x, y);
//			if (tiles[coordonnees])
//			{
//				break;
//			}
//			mouvements.push_back(coordonnees);
//		}
//	}
//	for (int x = position_.x; x >= 0; x--)
//	{
//		for (int y = position_.y; y >= 0; y--)
//		{
//			Coordonnees coordonnees(x, y);
//			if (tiles[coordonnees])
//			{
//				break;
//			}
//			mouvements.push_back(coordonnees);
//		}
//	}*/
//	return mouvements;
//}

bool Bishop::estMovementValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles) {
	int diffx = destination.x - position_.x;
	int diffy = destination.y - position_.y;
	if (abs(diffx) == abs(diffy)) {
		int i;
		int j;
		if (diffx < 0)
		{
			i = 1;
		}
		else
		{
			i = -1;
		}
		if (diffy < 0)
		{
			j = 1;
		}
		else
		{
			j = -1;
		}
		Coordonnees coordonnees(destination.x, destination.y);
		while (coordonnees.x != position_.x && coordonnees.y != position_.y)
		{
			if (tiles[coordonnees])
			{
				return false;
			}
			coordonnees.x += i;
			coordonnees.y += j;
		}
		return true;
	}
	return false;

}

bool Bishop::estAttaqueValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles) 
{
	if (tiles[destination]->getSide() == side_)
	{
		return false;
	}
	int diffx = destination.x - position_.x;
	int diffy = destination.y - position_.y;
	int i;
	int j;
	if (abs(diffx) == abs(diffy)) {

		if (diffx < 0)
		{
			i = 1;
		}
		else
		{
			i = -1;
		}
		if (diffy < 0)
		{
			j = 1;
		}
		else
		{
			j = -1;
		}
		destination.x = destination.x + i;
		destination.y = destination.y + j;

		if (estMovementValide(destination, tiles))
		{
			return true;
		}
	}
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