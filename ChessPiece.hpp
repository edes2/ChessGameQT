#pragma once

#include <QString>
#include "namespace.hpp"
#include "Coordonnees.hpp"
#include <map>

//using namespace std;

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
	//virtual std::vector<Coordonnees> mouvementsValides();

	// Certains pions -> movement!=attaque Ex:Pawn
	virtual std::vector<Coordonnees> movementsPossibles(std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles) = 0;
	virtual std::vector<Coordonnees> attaquesPossibles(std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles) = 0;
	virtual bool estMovementValide(Coordonnees destination) = 0;
	virtual bool estAttaqueValide(Coordonnees destination) = 0;
	virtual void setSide(side side);
	virtual void updatePos(Coordonnees position);
protected:
	side side_;
	Coordonnees position_;
};