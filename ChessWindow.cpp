#pragma once

#include "ChessWindow.hpp"
#include "Coordonnees.hpp"
#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QHBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QLabel>
#include <QString>
#include <QVariant>
#include <QGraphicsItem>
#include <QGraphicsColorizeEffect>
#include <QPropertyAnimation>
#pragma pop()
#include <iostream>
#include <cppitertools/range.hpp>

using iter::range;

ChessWindow::ChessWindow(QWidget* parent) :
	QMainWindow(parent)
{
	auto widgetPrincipal = new QWidget(this);
	auto layoutPrincipal = new QGridLayout(widgetPrincipal);

	chess_.initPartie();

	layoutPrincipal->setSpacing(0);
	layoutPrincipal->setVerticalSpacing(0);

	for (int y : range(8))
	{
		for (int x : range(8))
		{
			boutons[x][y] = new QPushButton(this);
			boutons[x][y]->setFixedSize(80,80);
			setColor(x, y);
			//if ((x + y) % 2 == 0)
			//{
			//	boutons[x][y]->setStyleSheet("border: 0px ; background-color:#FF1694;"); //FF1694
			//}
			//else
			//{
			//	boutons[x][y]->setStyleSheet("border: 0px ; background-color:#FFFFFF;");
			//}
			boutons[x][y]->setIconSize(QSize(80, 80));
			QObject::connect(boutons[x][y], &QPushButton::clicked, &chess_, [this, x, y]() { 
				chess_.caseAppuye(Coordonnees(x, y));
			});
			layoutPrincipal->addWidget(boutons[x][y], y, x);
		}
	}

	QObject::connect(&chess_, &ChessBoard::pieceDeplacee, this, &ChessWindow::pieceDeplacee);

	QObject::connect(&chess_, &ChessBoard::finPartie, this, &ChessWindow::finPartie);

	QObject::connect(&chess_, &ChessBoard::selectionPossible, this, &ChessWindow::selectionPossible);

	// Un connect pour le reset (avec initPartie du modele)
	// Un connect pour un label qui affiche le tour
	// Un connect qui laisser l utilisateur choisir quel piece avoir qd pion arrive au bout?
	//CHANGER BOUTONS LISTE POUR GENRE DE MAP DE COORDONNEES??

	setCentralWidget(widgetPrincipal);
	setWindowTitle("Chess");

	afficherPieces();
	
}

void ChessWindow::setColor(int x, int y)
{
	if ((x + y) % 2 == 0)
	{
		boutons[x][y]->setStyleSheet("border: 0px ; background-color:#FF1694;"); //FF1694
	}
	else
	{
		boutons[x][y]->setStyleSheet("border: 0px ; background-color:#FFFFFF;");
	}
}

void ChessWindow::pieceDeplacee()
{
	afficherPieces();
}

void ChessWindow::afficherPieces()
{
	for (int y : range(8))
	{
		for (int x : range(8))
		{
			Coordonnees position(x, y);
			setColor(x, y);
			if (chess_.tiles[position])
			{
				QString path = chess_.tiles[position]->getImagePath();
				QPixmap pixmap(path);
				QIcon iconBack(pixmap);
				boutons[x][y]->setIcon(iconBack);
			}
			else
			{
				boutons[x][y]->setIcon(QIcon());
			}

			//if (chess_.tiles[position])
			//{
			//	chess_.tiles[position]->updatePos(position);
			//}


			/*QGraphicsColorizeEffect* eEffect = new QGraphicsColorizeEffect(boutons[x][y]);
			boutons[x][y]->setGraphicsEffect(eEffect);
			QPropertyAnimation* paAnimation = new QPropertyAnimation(eEffect, "color");
			paAnimation->setStartValue(QColor(Qt::blue));
			paAnimation->setEndValue("border: 0px ; background:light yellow;");
			paAnimation->setDuration(1000);
			paAnimation->start();*/
		}
	}
}

void ChessWindow::finPartie(side loser)
{
	if (loser == white)
	{
		std::cout << "Les blancs sont en echec et math!\n";
		//emit finPartie(white);
	}
	else
	{
		std::cout << "Les noirs sont en echec et math!\n";
		//emit finPartie(black);
	}
}

void ChessWindow::selectionPossible(Coordonnees position)
{
	// Piece selectionnee?
	int x = position.x;
	int y = position.y;
	boutons[x][y]->setStyleSheet("border: 0px ; background-color:#e6d27a;");
}