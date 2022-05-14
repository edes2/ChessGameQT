#pragma once

#include <QString>
#include "namespace.hpp"
#include "Coordinates.hpp"
#include <map>

class ChessPiece {
public:
	ChessPiece();
	virtual ~ChessPiece() = default;

	virtual QString getImagePath() = 0;

	side getSide() const;
	virtual void setSide(side side);

	virtual bool estMovementValide(Coordinates destination, std::map<Coordinates, std::shared_ptr<ChessPiece>> tiles) = 0;
	virtual bool estAttaqueValide(Coordinates destination, std::map<Coordinates, std::shared_ptr<ChessPiece>> tiles) = 0;
	
	virtual void updatePos(Coordinates position);

	Coordinates getPos() const;

	type getType() const;
	void setType(type iType);

	bool getHasMoved() const;
	void setHasMoved();

  bool mIsMoveEnPassant;

protected:
	side mSide;
	type mType;

	Coordinates mPosition;

	bool mHasMoved;
};