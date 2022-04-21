#pragma once

#include <QString>
#include "namespace.hpp"
#include "Coordonnees.hpp"

class ChessPiece {
public:
	//ChessPiece() = default;
	~ChessPiece() = default;
	virtual QString getImagePath() = 0;

	//
	//isPathClear()
	//isMoveValid()
	side getSide();

	// Exemple pour un pawn
	virtual std::vector<Coordonnees> mouvementsValides();

	// Certains pions -> movement!=attaque Ex:Pawn
	virtual bool estMovementValide(Coordonnees destination);
	virtual bool estAttaqueValide(Coordonnees destination);
	virtual void setSide(side side);
	virtual void updatePos(Coordonnees position);
protected:
	side side_;
	Coordonnees position_;
};