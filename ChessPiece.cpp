#include "ChessPiece.hpp"

void ChessPiece::setSide(side side)
{
	side_ = side;
}

side ChessPiece::getSide()
{
	return side_;
}

void ChessPiece::updatePos(Coordonnees position)
{
	position_ = position;
}