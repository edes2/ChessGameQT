#pragma once

#include "ChessBoard.hpp"
#include "namespace.hpp"
#pragma warning(push, 0)
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#pragma pop()

class ChessWindow : public QMainWindow {
	Q_OBJECT
public:
	ChessWindow(QWidget* parent = nullptr);
	~ChessWindow() override = default;
public slots:
	void pieceDeplacee();
	void finPartie(side loser);
	void selectionPossible(Coordinates position);
	void showTurn(side turn);
	void inputPawnTranform(Coordinates iPosition);
signals:
private:
	ChessBoard mChess;  // Le Modèle
	QPushButton* pBoutons[8][8];
	void afficherPieces();
	void setColor(int x, int y);
	QPushButton* pRestartButton;
	QLabel* pTurnLabel;
};
