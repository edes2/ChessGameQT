#pragma once

#include "ChessBoard.hpp"
#pragma warning(push, 0) // Sinon Qt fait des avertissements � /W4.
#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QLabel>
#pragma pop()

class ChessWindow : public QMainWindow {
	Q_OBJECT
public:
	ChessWindow(QWidget* parent = nullptr); // Construire les cases, les boutons, connecter chaque bouton au modele et position correspondante, mettre les images des pieces sur les cases qui ont des pieces.
	~ChessWindow() override = default;
public slots: // Les affichages qui peuvent etre connectes au modele et change lorsque modele change?
	void pieceDeplacee();
private:
	ChessBoard chess_;  // Le Mod�le (pourrait �tre un pointeur mais pas n�cessaire dans ce cas).
	QPushButton* boutons[8][8];
	void afficherPieces();
};
