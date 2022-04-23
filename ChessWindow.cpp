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
#pragma pop()
#include <iostream>
#include <cppitertools/range.hpp>

using iter::range;
using namespace Vue;

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
			boutons[x][y]->setFixedSize(70, 70);
			if ((x + y) % 2 == 0)
			{
				boutons[x][y]->setStyleSheet("border: 0px ; background:#FF1694;");
			}
			else
			{
				boutons[x][y]->setStyleSheet("border: 0px ; background:#FFFFFF;");
			}
			boutons[x][y]->setIconSize(QSize(70, 70));
			QObject::connect(boutons[x][y], &QPushButton::clicked, &chess_, [this, x, y]() { chess_.caseAppuye(Coordonnees(x, y)); });//std::make_pair(x,y)); });
			layoutPrincipal->addWidget(boutons[x][y], y, x);
		}
	}

	QObject::connect(&chess_, &ChessBoard::pieceDeplacee, this, &ChessWindow::pieceDeplacee);
	
	setCentralWidget(widgetPrincipal);
	setWindowTitle("Chess");

	afficherPieces();
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
		for (int x : range(8))
		{
			Coordonnees position(x, y);
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
			if (chess_.tiles[position])
			{
				chess_.tiles[position]->updatePos(position);
			}
		}
	}
}