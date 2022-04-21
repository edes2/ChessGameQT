#include "ChessPiece.hpp"

void ChessPiece::setSide(side side) {
	side_ = side;
}

side ChessPiece::getSide() {
	return side_;
}

std::vector<Coordonnees> ChessPiece::mouvementsValides()
{
	std::vector<Coordonnees> mouvements;
	if (side_ == white)
	{
		if (position_.y == 6)
		{
			mouvements.push_back(Coordonnees(position_.x, position_.y - 2));

		}
		mouvements.push_back(Coordonnees(position_.x, position_.y - 1));
	}
	else
	{
		if (position_.y == 1)
		{

			mouvements.push_back(Coordonnees(position_.x, position_.y + 2));

		}
		mouvements.push_back(Coordonnees(position_.x, position_.y + 1));
	}
	return mouvements;
}

// Certains pions -> movement!=attaque Ex:Pawn
bool ChessPiece::estMovementValide(Coordonnees destination)//std::pair<int, int> destination) //= 0;
{
	return true;
	if (destination.x == position_.x) // meme colonne
	{
		if (side_ == white && (destination.y < position_.y))
		{
			if (position_.y == 6) // on a le droit de sauter de 2 cases
			{
				if (destination.y >= position_.y - 2)
				{
					return true;
				}
			}
			else {
				if (destination.y == position_.y - 1)
				{
					return true;
				}
			}
		}
		else if (side_ == black && (destination.y > position_.y)) // side_==black
		{
			if (position_.y == 1) // on a le droit de sauter de 2 cases
			{
				if (destination.y <= position_.y + 2)
				{
					return true;
				}
			}
			else {
				if (destination.y == position_.y + 1)
				{
					return true;
				}
			}
		}
	}
	return false;
}
bool ChessPiece::estAttaqueValide(Coordonnees destination)//std::pair<int, int> destination) //= 0;
{
	return true;
}
void ChessPiece::updatePos(Coordonnees position)//std::pair<int, int> position) {
{
	position_ = position;
}