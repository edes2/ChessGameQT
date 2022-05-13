#pragma once

#include "ChessWindow.hpp"
#include "Coordonnees.hpp"

#pragma warning(push, 0)
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
			pBoutons[x][y] = new QPushButton(this);
			pBoutons[x][y]->setFixedSize(80,80);
			setColor(x, y);
			pBoutons[x][y]->setIconSize(QSize(80, 80));
			QObject::connect(pBoutons[x][y], &QPushButton::clicked, &mChess, [this, x, y]() { 
				mChess.caseAppuye(Coordonnees(x, y));
			});
			layout->addWidget(pBoutons[x][y], y, x);
		}
	}

	QObject::connect(&mChess, &ChessBoard::pieceDeplacee, this, &ChessWindow::pieceDeplacee);

	QObject::connect(&mChess, &ChessBoard::finPartie, this, &ChessWindow::finPartie);

	QObject::connect(&mChess, &ChessBoard::selectionPossible, this, &ChessWindow::selectionPossible);

	auto bottomLayout = new QHBoxLayout();
	layoutPrincipal->addLayout(bottomLayout);
	bottomLayout->addSpacing(10);
	pTurnLabel = new QLabel(this);
	pTurnLabel->setMinimumWidth(100);
	bottomLayout->addWidget(pTurnLabel);

	QObject::connect(&mChess, &ChessBoard::showTurn, this, &ChessWindow::showTurn);

	pRestartButton = new QPushButton(this);
	pRestartButton->setFixedSize(150, 50);
	pRestartButton->setText("Restart Game");
	bottomLayout->addWidget(pRestartButton);

	QObject::connect(pRestartButton, &QPushButton::clicked, &mChess, &ChessBoard::restartPartie);

	setCentralWidget(widgetPrincipal);
	setWindowTitle("Chess");

	mChess.initPartie();

	afficherPieces();
	
}

void ChessWindow::setColor(int x, int y)
{
	if ((x + y) % 2 == 0)
	{
		pBoutons[x][y]->setStyleSheet("border: 0px ; background-color:#EEEED2;");
	}
	else
	{
		pBoutons[x][y]->setStyleSheet("border: 0px ; background-color:#769656;");
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
		pTurnLabel->setText("Turn: White");
	}
	else
	{
		pTurnLabel->setText("Turn: Black");
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
			if (mChess.mTiles[position])
			{
				QString path = mChess.mTiles[position]->getImagePath();
				QPixmap pixmap(path);
				QIcon iconBack(pixmap);
				pBoutons[x][y]->setIcon(iconBack);
			}
			else
			{
				pBoutons[x][y]->setIcon(QIcon());
			}
		}
	}
}

void ChessWindow::finPartie(side loser)
{
	QMessageBox message;
	if (loser == white)
	{
		message.setText("Checkmate, Black win !");
		message.exec();
	}
	else
	{
		message.setText("Checkmate, White win !");
		message.exec();
	}
}

void ChessWindow::selectionPossible(Coordonnees position)
{
	int x = position.x;
	int y = position.y;
	pBoutons[x][y]->setStyleSheet("border: 0px ; background-color:#e6d27a;");
}