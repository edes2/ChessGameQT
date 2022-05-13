#pragma once

#include "ChessWindow.hpp"
#include "Coordinates.hpp"

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
			pButtons[x][y] = new QPushButton(this);
			pButtons[x][y]->setFixedSize(80,80);
			setColor(x, y);
			pButtons[x][y]->setIconSize(QSize(80, 80));
			QObject::connect(pButtons[x][y], &QPushButton::clicked, &mChess, [this, x, y]() { 
				mChess.caseAppuye(Coordinates(x, y));
			});
			layout->addWidget(pButtons[x][y], y, x);
		}
	}

	QObject::connect(&mChess, &ChessBoard::pieceDeplacee, this, &ChessWindow::pieceDeplacee);

	QObject::connect(&mChess, &ChessBoard::finPartie, this, &ChessWindow::finPartie);

	QObject::connect(&mChess, &ChessBoard::selectionPossible, this, &ChessWindow::selectionPossible);

	QObject::connect(&mChess, &ChessBoard::inputPawnTranform, this, &ChessWindow::inputPawnTranform);

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

	QObject::connect(pRestartButton, &QPushButton::clicked, &mChess, &ChessBoard::restartGame);

	setCentralWidget(widgetPrincipal);
	setWindowTitle("Chess");

	mChess.initGame();

	showPieces();
	
}

void ChessWindow::setColor(int x, int y)
{
	if ((x + y) % 2 == 0)
	{
		pButtons[x][y]->setStyleSheet("border: 0px ; background-color:#EEEED2;");
	}
	else
	{
		pButtons[x][y]->setStyleSheet("border: 0px ; background-color:#769656;");
	}
}

void ChessWindow::pieceDeplacee()
{
	showPieces();
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

void ChessWindow::showPieces()
{
	for (int y : range(8))
	{
		for (int x : range(8))
		{
			Coordinates position(x, y);
			setColor(x, y);
			if (mChess.mTiles[position])
			{
				QString path = mChess.mTiles[position]->getImagePath();
				QPixmap pixmap(path);
				QIcon iconBack(pixmap);
				pButtons[x][y]->setIcon(iconBack);
			}
			else
			{
				pButtons[x][y]->setIcon(QIcon());
			}
		}
	}
}

void ChessWindow::finPartie(side loser)
{
	QMessageBox message;
	if (loser == white)
	{
		message.setText("Checkmate, Black wins!");
		message.exec();
	}
	else
	{
		message.setText("Checkmate, White wins!");
		message.exec();
	}
}

void ChessWindow::selectionPossible(Coordinates position)
{
	int x = position.x;
	int y = position.y;
	pButtons[x][y]->setStyleSheet("border: 0px ; background-color:#e6d27a;");
}

void ChessWindow::inputPawnTranform(Coordinates iPosition)
{
	type pieceType;
	QMessageBox message;

	message.setText("Which piece do you want: ");

	QPushButton* rookButton = message.addButton(tr("Rook"), QMessageBox::NoRole);
	QPushButton* queenButton = message.addButton(tr("Queen"), QMessageBox::NoRole);
	QPushButton* knightButton = message.addButton(tr("Knight"), QMessageBox::NoRole);
	QPushButton* bishopButton = message.addButton(tr("Bishop"), QMessageBox::NoRole);

	message.setMinimumSize(200, 200);
	message.exec();

	
	mChess.pawnTranform(message.clickedButton()->text(), iPosition);
	
	//mChess.pawnTranform(pieceType, iPosition);
}