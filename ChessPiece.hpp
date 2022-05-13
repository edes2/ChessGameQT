#pragma once

#include <QString>
#include "namespace.hpp"
#include "Coordonnees.hpp"
#include <map>

class ChessPiece {
public:
	ChessPiece();
	virtual ~ChessPiece() = default;

	virtual QString getImagePath() = 0;

	side getSide() const;
	virtual void setSide(side side);

	virtual bool estMovementValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles) = 0;
	virtual bool estAttaqueValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles) = 0;
	
	virtual void updatePos(Coordonnees position);

	Coordonnees getPos() const;

	type getType() const;

	bool getHasMoved() const;
	void setHasMoved();

protected:
	side mSide;
	type mType;

	Coordonnees mPosition;

	bool mHasMoved;
};