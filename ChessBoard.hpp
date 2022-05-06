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
	void initPartie();
	std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles;
	side getTurn();
	void switchTurn();
public slots: // Lorsque recoit changements de la vue.
	void caseAppuye(Coordonnees position);
signals: // Pour envoyer un signal lorsque le modele a change une valeur
	void pieceDeplacee();
	void finPartie(side loser);
	void selectionPossible(Coordonnees position);
private:
	bool tryMove(Coordonnees destination);
	bool estEnEchec();
	bool estEnEchecEtMath();
	void partieTerminee();
	void updateBoard();
	void mouvementsPossibles();
	bool tryCastling(Coordonnees position);
	std::shared_ptr<Coordonnees> caseSelectionnee;
	std::shared_ptr<ChessPiece> whiteKing;
	std::shared_ptr<ChessPiece> blackKing;
	side turn_;
	bool gagnantPartie;
};
