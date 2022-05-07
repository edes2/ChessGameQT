#include "ChessPiece.hpp"

ChessPiece::ChessPiece() : hasMoved_(false)
{

}

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
	return hasMoved_;
}

void ChessPiece::setHasMoved()
{
	hasMoved_ = true;
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