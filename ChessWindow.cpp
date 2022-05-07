#pragma once

#include "ChessWindow.hpp"
#include "Coordonnees.hpp"
#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QHBoxLayout>
#include <QMessageBox>
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

	auto layoutPrincipal = new QVBoxLayout(widgetPrincipal);
	auto layout = new QGridLayout();
	layoutPrincipal->addLayout(layout);

	layoutPrincipal->setSpacing(0);

	layout->setVerticalSpacing(0);

	for (int y : range(8))
	{
		for (int x : range(8))
		{
			boutons[x][y] = new QPushButton(this);
			boutons[x][y]->setFixedSize(80,80);
			setColor(x, y);
			boutons[x][y]->setIconSize(QSize(80, 80));
			QObject::connect(boutons[x][y], &QPushButton::clicked, &chess_, [this, x, y]() { 
				chess_.caseAppuye(Coordonnees(x, y));
			});
			layout->addWidget(boutons[x][y], y, x);
		}
	}

	QObject::connect(&chess_, &ChessBoard::pieceDeplacee, this, &ChessWindow::pieceDeplacee);

	QObject::connect(&chess_, &ChessBoard::finPartie, this, &ChessWindow::finPartie);

	QObject::connect(&chess_, &ChessBoard::selectionPossible, this, &ChessWindow::selectionPossible);

	auto bottomLayout = new QHBoxLayout();
	layoutPrincipal->addLayout(bottomLayout);
	bottomLayout->addSpacing(10);
	turnLabel = new QLabel(this);
	turnLabel->setMinimumWidth(100);
	bottomLayout->addWidget(turnLabel);

	QObject::connect(&chess_, &ChessBoard::showTurn, this, &ChessWindow::showTurn);

	restartButton = new QPushButton(this);
	restartButton->setFixedSize(150, 50);
	restartButton->setText("Restart Game");
	bottomLayout->addWidget(restartButton);

	QObject::connect(restartButton, &QPushButton::clicked, &chess_, &ChessBoard::restartPartie);

	setCentralWidget(widgetPrincipal);
	setWindowTitle("Chess");

	chess_.initPartie();

	afficherPieces();
	
}

void ChessWindow::setColor(int x, int y)
{
	if ((x + y) % 2 == 0)
	{
		boutons[x][y]->setStyleSheet("border: 0px ; background-color:#FF1694;");
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

void ChessWindow::showTurn(side turn)
{
	if (turn == white)
	{
		turnLabel->setText("Tour des: Blancs");
	}
	else
	{
		turnLabel->setText("Tour des: Noirs");
	}
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
		}
	}
}

void ChessWindow::finPartie(side loser)
{
	QMessageBox message;
	if (loser == white)
	{
		message.setText("Les blancs sont en echec et math !");
		message.exec();
	}
	else
	{
		message.setText("Les noirs sont en echec et math!");
		message.exec();
	}
}

void ChessWindow::selectionPossible(Coordonnees position)
{
	int x = position.x;
	int y = position.y;
	boutons[x][y]->setStyleSheet("border: 0px ; background-color:#e6d27a;");
}