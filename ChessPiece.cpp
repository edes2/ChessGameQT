#include "ChessPiece.hpp"

ChessPiece::ChessPiece() : mHasMoved(false)
{

}

void ChessPiece::setSide(side side)
{
	mSide = side;
}

side ChessPiece::getSide() const
{
	return mSide;
}

bool ChessPiece::getHasMoved() const
{
	return mHasMoved;
}

void ChessPiece::setHasMoved()
{
	mHasMoved = true;
}

type ChessPiece::getType() const
{
	return mType;
}

void ChessPiece::updatePos(Coordonnees position)
{
	mPosition = position;
}

Coordonnees ChessPiece::getPos() const
{
	return mPosition;
}