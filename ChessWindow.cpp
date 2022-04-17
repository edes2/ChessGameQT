#pragma once

#include "ChessWindow.hpp"
#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QHBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QLabel>
#include <QString>
#include <QVariant>
#pragma pop()
#include <iostream>
#include <cppitertools/range.hpp>

using iter::range;

ChessWindow::ChessWindow(QWidget* parent) :
	QMainWindow(parent)
{

	auto widgetPrincipal = new QWidget(this);
	auto layoutPrincipal = new QGridLayout(widgetPrincipal);//QVBoxLayout(widgetPrincipal);

	chess_.initPartie();

	layoutPrincipal->setSpacing(0);
	layoutPrincipal->setVerticalSpacing(0);
	/*
	auto groupeBoutons = new QButtonGroup(this);
	for (int i : range(10)) {
		//auto bouton = nouveauBouton(QString::number(i));//new QPushButton(this);
		//bouton->setText("Button"+i);
		auto bouton = new QPushButton(this);
		bouton->setText(QString::number(i));
		bouton->setFixedSize(40, 40);
		groupeBoutons->addButton(bouton, i); // L'ID du bouton est i (doit être un entier).
		layout->addWidget(bouton);
	}
	*/
	//int id = 0;
	for (int y : range(8))
	{
		//auto layout = new QGridLayout(); // Pas possible de donner directement le parent au layout (le constructeur prend un QWidget* et un layout n'en est pas un; on ne peut pas mettre un parent qui a déjà un layout; si on met on parent temporaire, addLayout n'accepte pas de changer le parent).
		//layoutPrincipal->addLayout()
		//layoutPrincipal->addLayout(layout);
		for (int x : range(8))
		{
			boutons[x][y] = new QPushButton(this);
			//QPushButton* bouton = new QPushButton(this);
			//QColor vert(Qt::green);
			//QPalette palette;
			//palette.setColor(QPalette::Base, vert);
			//bouton->setPalette(palette);
			//bouton->setAutoFillBackground(true);
			boutons[x][y]->setFixedSize(40, 40);

			//bouton->setObjectName(QString::number(id++));
			if ((x + y) % 2 == 0) {
				boutons[x][y]->setStyleSheet("border: 0px ; background:rgb(238,238,210);");
			}
			else {
				boutons[x][y]->setStyleSheet("border: 0px ; background:rgb(118,150,86);");
			}

			// FAIRE UNE FONCTION REFRESH TILES OU LES PLACER ICI POUR DEBUT
			// Appeler la fonction virtual de la piece pour loader la bonne image
			boutons[x][y]->setIconSize(QSize(40, 40));
			/////////
			//bouton->update();
			//bouton->show();
			//std::pair<int, int> pos = std::make_pair(x,y);
			QObject::connect(boutons[x][y], &QPushButton::clicked, &chess_, [this, x, y]() { chess_.caseAppuye(std::make_pair(x,y)); });
			layoutPrincipal->addWidget(boutons[x][y], y, x);
		}
	}

	QObject::connect(&chess_, &ChessBoard::pieceDeplacee, this, &ChessWindow::pieceDeplacee);
	
	setCentralWidget(widgetPrincipal);
	setWindowTitle("Chess");

	afficherPieces();
	/*
	for (int i : range(10))
	{
		auto bouton = new QPushButton(this);
		//bouton->setText("Button"+i);
		bouton->setFixedSize(40, 40);
		layout->addWidget(bouton);
	}
	*/
		
		//layout->addWidget(nouveauBouton(QString::number(i), [this, i]() { calc_.ajouterChiffre(i); }));
}


void ChessWindow::pieceDeplacee()
{
	std::cout << "vALeur changee!\n";
	afficherPieces();
}

void ChessWindow::afficherPieces()
{
	for (int y : range(8))
	{
		//auto layout = new QGridLayout(); // Pas possible de donner directement le parent au layout (le constructeur prend un QWidget* et un layout n'en est pas un; on ne peut pas mettre un parent qui a déjà un layout; si on met on parent temporaire, addLayout n'accepte pas de changer le parent).
		//layoutPrincipal->addLayout()
		//layoutPrincipal->addLayout(layout);
		for (int x : range(8))
		{
			// afficher les images des chesspieces ici si oui
			std::pair<int, int> position = std::make_pair(x, y);
			if (chess_.tiles[position])
			{
				QString path = chess_.tiles[position]->getImagePath();
				QPixmap pixmap(path);
				QIcon iconBack(pixmap);
				boutons[x][y]->setIcon(iconBack);
			}
			else
			{
				boutons[x][y]->setIcon(QIcon()); //Mettre une icône vide pour l'enlever
			}
			if (chess_.tiles[position])
			{
				chess_.tiles[position]->updatePos(position); // Pour que piece garde son emplacement ???
			}
		}
	}
}