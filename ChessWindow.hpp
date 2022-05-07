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
	void selectionPossible(Coordonnees position);
	void showTurn(side turn);
private:
	ChessBoard chess_;  // Le Modèle
	QPushButton* boutons[8][8];
	void afficherPieces();
	void setColor(int x, int y);
	QPushButton* restartButton;
	QLabel* turnLabel;
};
