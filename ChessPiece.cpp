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

void ChessPiece::setType(type iType)
{
	mType = iType;
}

void ChessPiece::updatePos(Coordinates position)
{
	mPosition = position;
}

Coordinates ChessPiece::getPos() const
{
	return mPosition;
}