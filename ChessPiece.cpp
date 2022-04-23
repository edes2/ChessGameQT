#include "ChessPiece.hpp"

void ChessPiece::setSide(side side)
{
	side_ = side;
}

side ChessPiece::getSide()
{
	return side_;
}

//std::vector<Coordonnees> ChessPiece::mouvementsValides()
//{
//	std::vector<Coordonnees> mouvements;
//	if (side_ == white)
//	{
//		if (position_.y == 6)
//		{
//			mouvements.push_back(Coordonnees(position_.x, position_.y - 2));
//
//		}
//		mouvements.push_back(Coordonnees(position_.x, position_.y - 1));
//	}
//	else
//	{
//		if (position_.y == 1)
//		{
//			mouvements.push_back(Coordonnees(position_.x, position_.y + 2));
//		}
//		mouvements.push_back(Coordonnees(position_.x, position_.y + 1));
//	}
//	return mouvements;
//}



void ChessPiece::updatePos(Coordonnees position)//std::pair<int, int> position) {
{
	position_ = position;
}