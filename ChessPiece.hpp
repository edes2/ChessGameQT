#pragma once

#include <QString>
#include "namespace.hpp"

class ChessPiece {
public:
	ChessPiece() = default;
	virtual QString getImagePath()=0;

	// Certains pions -> movement!=attaque Ex:Pawn
	virtual bool estMovementValide(std::pair<int, int> destination) //= 0;
	{
		if (destination.first == position_.first) // meme colonne
		{
			if (side_ == white && (destination.second < position_.second))
			{
				if (position_.second == 6) // on a le droit de sauter de 2 cases
				{
					if (destination.second >= position_.second - 2)
					{
						return true;
					}
				}
				else {
					if (destination.second == position_.second - 1)
					{
						return true;
					}
				}
			}
			else if (side_ == black && (destination.second > position_.second)) // side_==black
			{
				if (position_.second == 1) // on a le droit de sauter de 2 cases
				{
					if (destination.second <= position_.second + 2)
					{
						return true;
					}
				}
				else {
					if (destination.second == position_.second + 1)
					{
						return true;
					}
				}
			}
		}
		return false;
	}
	virtual bool estAttaqueValide(std::pair<int, int> destination) //= 0;
	{
		return false;
	}
	virtual void setSide(side side);
	virtual void updatePos(std::pair<int, int> position) {
		position_ = position;
	}
protected:
	side side_;
	std::pair<int, int> position_;
};