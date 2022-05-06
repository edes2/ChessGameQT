#include "ChessPiece.hpp"

void ChessPiece::setSide(side side)
{
	side_ = side;
}

side ChessPiece::getSide() const
{
	return side_;
}

bool ChessPiece::getHasMoved() const
{
	return hasMoved;
}

void ChessPiece::setHasMoved()
{
	hasMoved = true;
}

type ChessPiece::getType() const
{
	return type_;
}

void ChessPiece::updatePos(Coordonnees position)
{
	position_ = position;
}

Coordonnees ChessPiece::getPos() const
{
	return position_;
}