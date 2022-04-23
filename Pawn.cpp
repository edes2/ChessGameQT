#include "Pawn.hpp"

Pawn::Pawn()
{

}

std::vector<Coordonnees> Pawn::attaquesPossibles(std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
{
	std::vector<Coordonnees> attaques;
	if (side_ == white)
	{
		Coordonnees coordonnees(position_.x + 1, position_.y - 1);
		if (tiles[coordonnees])
		{
			attaques.push_back(coordonnees);
		}
		coordonnees.x = position_.x - 1;
		if (tiles[coordonnees])
		{
			attaques.push_back(coordonnees);
		}
	}

	else
	{

		Coordonnees coordonnees(position_.x + 1, position_.y + 1);
		if (tiles[coordonnees])
		{
			attaques.push_back(coordonnees);
		}
		coordonnees.x = position_.x - 1;
		if (tiles[coordonnees])
		{
			attaques.push_back(coordonnees);
		}
	}
	return attaques;
}


std::vector<Coordonnees> Pawn::movementsPossibles(std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
{
	std::vector<Coordonnees> mouvements;
	if (side_ == white)
	{
		if (position_.y == 6)
		{
			for (int i = 1; i <= 2; i++) // faire dans fonction?
			{
				Coordonnees coordonnees(position_.x, position_.y - i);
				if (!tiles[coordonnees]) //pas de piece qui bloque
				{
					mouvements.push_back(coordonnees);
				}
				else
				{
					break;
				}
			}
		}
		else {
			Coordonnees coordonnees(position_.x, position_.y - 1); // faire dans fonction?
			if (!tiles[coordonnees]) //pas de piece qui bloque
			{
				mouvements.push_back(coordonnees);
			}
		}
	}
	else
	{
		if (position_.y == 1)
		{
			for (int i = 1; i <= 2; i++) // faire dans fonction?
			{
				Coordonnees coordonnees(position_.x, position_.y + i);
				if (!tiles[coordonnees]) //pas de piece qui bloque
				{
					mouvements.push_back(coordonnees);
				}
				else
				{
					break;
				}
			}
		}
		else {
			Coordonnees coordonnees(position_.x, position_.y + 1); // faire dans fonction?
			if (!tiles[coordonnees]) //pas de piece qui bloque
			{
				mouvements.push_back(coordonnees);
			}
		}
	}
	return mouvements;
}


bool Pawn::estMovementValide(Coordonnees destination)
{
	if (destination.x == position_.x)
	{
		if (side_ == white && (destination.y < position_.y))
		{
			if (position_.y == 6)
			{
				if (destination.y >= position_.y - 2)
				{
					return true;
				}
			}
			else
			{
				if (destination.y == position_.y - 1)
				{
					return true;
				}
			}
		}
		else if (side_ == black && (destination.y > position_.y))
		{
			if (position_.y == 1)
			{
				if (destination.y <= position_.y + 2)
				{
					return true;
				}
			}
			else
			{
				if (destination.y == position_.y + 1)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool Pawn::estAttaqueValide(Coordonnees destination)//std::pair<int, int> destination) //= 0;
{
	if (side_ == white)
	{
		if (((destination.x == position_.x + 1) && (destination.y == position_.y - 1)) || ((destination.x == position_.x - 1) && (destination.y == position_.y - 1)))
		{
			return true;
		}
	}

	else
	{
		if (((destination.x == position_.x + 1) && (destination.y == position_.y + 1)) || ((destination.x == position_.x - 1) && (destination.y == position_.y + 1)))
		{
			return true;
		}
	}
	return false;
}

QString Pawn::getImagePath() {
	QString path;
	if (side_ == white) {
		path = "50px/WhitePawn.png";
	}
	else
	{
		path = "50px/BlackPawn.png";
	}
	return path;
}