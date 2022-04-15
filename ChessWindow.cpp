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
	chess_ = new ChessBoard();

	auto widgetPrincipal = new QWidget(this);
	auto layoutPrincipal = new QGridLayout(widgetPrincipal);//QVBoxLayout(widgetPrincipal);

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
	int id = 0;
	for (int y : range(8))
	{
		//auto layout = new QGridLayout(); // Pas possible de donner directement le parent au layout (le constructeur prend un QWidget* et un layout n'en est pas un; on ne peut pas mettre un parent qui a déjà un layout; si on met on parent temporaire, addLayout n'accepte pas de changer le parent).
		//layoutPrincipal->addLayout()
		//layoutPrincipal->addLayout(layout);
		for (int x : range(8))
		{
			QPushButton* bouton = new QPushButton(this);
			//QColor vert(Qt::green);
			//QPalette palette;
			//palette.setColor(QPalette::Base, vert);
			//bouton->setPalette(palette);
			//bouton->setAutoFillBackground(true);
			bouton->setFixedSize(40, 40);
			//bouton->setObjectName(QString::number(id++));
			if ((x + y) % 2 == 0) {
				bouton->setStyleSheet("border: 0px ; background:rgb(238,238,210);");
			}
			else {
				bouton->setStyleSheet("border: 0px ; background:rgb(118,150,86);");
			}
			//bouton->update();
			//bouton->show();
			//std::pair<int, int> pos = std::make_pair(x,y);
			QObject::connect(bouton, &QPushButton::clicked, chess_, [this, x, y]() { chess_->caseAppuye(std::make_pair(x,y)); });
			layoutPrincipal->addWidget(bouton, y, x);
		}
	}
	
	setCentralWidget(widgetPrincipal);
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