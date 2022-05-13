#pragma once

#include "namespace.hpp"
#include "Coordonnees.hpp"
#include "ChessPiece.hpp"
#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QObject>
#include <map>
#pragma pop()

class ChessBoard : public QObject {
	Q_OBJECT
public:
	ChessBoard() = default;

	std::map<Coordonnees, std::shared_ptr<ChessPiece>> mTiles; // Pour que ce soit facile d acces

	void initPartie();

	side getTurn();
	void switchTurn();

	bool getFin() const;

public slots:
	void caseAppuye(Coordonnees iPosition);
	void restartPartie();
signals:
	void pieceDeplacee();
	void finPartie(side loser);
	void selectionPossible(Coordonnees position);
	void showTurn(side turn);
private:
	bool tryMove(Coordonnees destination);
	bool tryCastling(Coordonnees position);

	bool estEnEchec();
	bool estEnEchecEtMath();

	void partieTerminee();
	void updateBoard();

	void mouvementsPossibles();
	
	std::shared_ptr<Coordonnees> pCaseSelectionnee;
	std::shared_ptr<ChessPiece> pWhiteKing;
	std::shared_ptr<ChessPiece> pBlackKing;

	side mTurn;

	bool mEstBackup;
	bool mFin;
};
