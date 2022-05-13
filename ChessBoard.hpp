#pragma once

#include "namespace.hpp"
#include "Coordinates.hpp"
#include "ChessPiece.hpp"
#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QObject>
#include <map>
#pragma pop()

class ChessBoard : public QObject {
	Q_OBJECT
public:
	ChessBoard() = default;

	std::map<Coordinates, std::shared_ptr<ChessPiece>> mTiles; // Pour que ce soit facile d acces

	void initPartie();

	side getTurn();
	void switchTurn();

	bool getFin() const;

	void pawnTranform(const QString& sPieceType, Coordinates iPosition);

public slots:
	void caseAppuye(Coordinates iPosition);
	void restartPartie();
	//void pawnTranform(side iSide);
signals:
	void pieceDeplacee();
	void finPartie(side loser);
	void selectionPossible(Coordinates position);
	void showTurn(side turn);
	//void pawnTransform();
	void inputPawnTranform(Coordinates position);
private:
	bool tryMove(Coordinates destination);
	bool tryCastling(Coordinates position);

	bool estEnEchec();
	bool estEnEchecEtMath();

	void checkPawnTransform(Coordinates iPosition);

	void partieTerminee();
	void updateBoard();

	void mouvementsPossibles();
	
	std::shared_ptr<Coordinates> pCaseSelectionnee;
	std::shared_ptr<ChessPiece> pWhiteKing;
	std::shared_ptr<ChessPiece> pBlackKing;

	side mTurn;

	bool mEstBackup;
	bool mFin;
};
