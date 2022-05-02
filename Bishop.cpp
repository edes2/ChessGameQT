#include "Bishop.hpp"
#include <cmath>

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
			if (tiles[coordonnees] && tiles[coordonnees] != tiles[destination])
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
	if (estMovementValide(destination, tiles))
	{
		return true;
	}
	/*
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
	*/
		
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