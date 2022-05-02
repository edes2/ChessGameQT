#include "Pawn.hpp"


bool Pawn::estMovementValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
{
	if (destination.x == position_.x)
	{
		if (side_ == white && (destination.y < position_.y))
		{
			if (position_.y == 6)
			{
				if (destination.y >= position_.y - 2 && !tiles[Coordonnees(position_.x, position_.y - 1)])
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
				if (destination.y <= position_.y + 2 && !tiles[Coordonnees(position_.x,position_.y+1)])
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

bool Pawn::estAttaqueValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)//std::pair<int, int> destination) //= 0;
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