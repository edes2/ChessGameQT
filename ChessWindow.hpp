#pragma once

#include "ChessBoard.hpp"
#include "namespace.hpp"
#include "Rook.hpp"
#pragma warning(push, 0)
#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QLabel>
#pragma pop()

class RAIIRook {
public:
	RAIIRook(QPushButton* bouton) : bouton_(bouton) {
		rook_ = new Rook;
		QString path = rook_->getImagePath();
		QPixmap pixmap(path);
		QIcon iconBack(pixmap);
		bouton->setIcon(iconBack);
	}
	~RAIIRook() { 
		delete rook_;
		bouton_->setIcon(QIcon());
	}
	Rook* getRook() { return rook_; }
private:
	Rook* rook_;
	QPushButton* bouton_;
};

class ChessWindow : public QMainWindow {
	Q_OBJECT
public:
	ChessWindow(QWidget* parent = nullptr); // Construire les cases, les boutons, connecter chaque bouton au modele et position correspondante, mettre les images des pieces sur les cases qui ont des pieces.
	~ChessWindow() override = default;
public slots: // Les affichages qui peuvent etre connectes au modele et change lorsque modele change?
	void pieceDeplacee();
private:
	ChessBoard chess_;  // Le Modèle (pourrait être un pointeur mais pas nécessaire dans ce cas).
	QPushButton* boutons[8][8];
	void afficherPieces();
	RAIIRook* raii_; // Pour implementer le RAII
};
