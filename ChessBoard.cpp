#pragma once

#include "ChessBoard.hpp"
#include <iostream>
#include <cppitertools/range.hpp>

#include "namespace.hpp"

#include "Pawn.hpp"
#include "King.hpp"
#include "Bishop.hpp"
#include "Queen.hpp"
#include "Rook.hpp"
#include "Knight.hpp"

using iter::range;

void ChessBoard::caseAppuye(Coordonnees position)
{
	if (caseSelectionnee)
	{
		if ((*caseSelectionnee) == position)
		{
			caseSelectionnee = nullptr;
			std::cout << "Deselection case: \n";
		}
		else
		{
			tryMove(position);
			std::cout << "Deselection case: \n";
			caseSelectionnee = nullptr;
			
		}
	}
	else
	{
		if (tiles[position] && tiles[position]->getSide() == turn_)
		{
			caseSelectionnee = std::make_unique<Coordonnees>(position);
			std::cout << "Nouvelle selection d'une case: \n";
			std::cout << "X: " << (*caseSelectionnee).x << ", Y: " << (*caseSelectionnee).y << std::endl;
		}
	}
}

void ChessBoard::tryMove(Coordonnees destination)
{
	if (tiles[destination])
	{
		/*std::vector<Coordonnees> attaques;
		attaques = tiles[*caseSelectionnee]->attaquesPossibles(tiles);
		for (auto&& it : attaques)
		{
			if (destination == it)
			{
				tiles[destination] = move(tiles[*caseSelectionnee]);
				switchTurn();

				std::cout << "Attaque d'une piece: \n";
				std::cout << "X: " << (*caseSelectionnee).x << ", Y: " << (*caseSelectionnee).y << std::endl;
				std::cout << "Vers case: \n";
				std::cout << "X: " << destination.x << ", Y: " << destination.y << std::endl;

				emit pieceDeplacee();
			}
		}*/
		if (tiles[*caseSelectionnee]->estAttaqueValide(destination, tiles))
		{
			tiles[destination] = move(tiles[*caseSelectionnee]);
			std::cout << "Attaque\n";
			switchTurn();

			emit pieceDeplacee();
		}
	}
	else
	{
		//std::vector<Coordonnees> mouvements;
		//mouvements = tiles[*caseSelectionnee]->movementsPossibles(tiles);//tiles); peut pas passer car c des unique_ptr dans la map???
		//for (auto&& it : mouvements)
		//{
		//	if (destination == it)
		//	{
		//		tiles[destination] = move(tiles[*caseSelectionnee]);
		//		switchTurn();

		//		std::cout << "Mouvement d'une piece: \n";
		//		std::cout << "X: " << (*caseSelectionnee).x << ", Y: " << (*caseSelectionnee).y << std::endl;
		//		std::cout << "Vers case: \n";
		//		std::cout << "X: " << destination.x << ", Y: " << destination.y << std::endl;

		//		emit pieceDeplacee();
		//	}
		//}
		if (tiles[*caseSelectionnee]->estMovementValide(destination, tiles))
		{
			tiles[destination] = move(tiles[*caseSelectionnee]);
			switchTurn();

			std::cout << "Mouvement d'une piece: \n";
			std::cout << "X: " << (*caseSelectionnee).x << ", Y: " << (*caseSelectionnee).y << std::endl;
			std::cout << "Vers case: \n";
			std::cout << "X: " << destination.x << ", Y: " << destination.y << std::endl;

			emit pieceDeplacee();
		}
	}
}

side ChessBoard::getTurn()
{
	return turn_;
}

void ChessBoard::switchTurn()
{
	if (turn_ == white) {
		turn_ = black;
	}
	else
	{
		turn_ = white;
	}
}

void ChessBoard::initPartie()
{
	turn_ = white;

	tiles[Coordonnees(0,0)] = std::make_shared<Rook>();

	tiles[Coordonnees(1, 0)] = std::make_shared<Knight>();

	tiles[Coordonnees(2, 0)] = std::make_shared<Bishop>();

	tiles[Coordonnees(3, 0)] = std::make_shared<Queen>();

	tiles[Coordonnees(4, 0)] = std::make_shared<King>();

	tiles[Coordonnees(5, 0)] = std::make_shared<Bishop>();

	tiles[Coordonnees(6, 0)] = std::make_shared<Knight>();

	tiles[Coordonnees(7, 0)] = std::make_shared<Rook>();

	///

	tiles[Coordonnees(0, 7)] = std::make_shared<Rook>();

	tiles[Coordonnees(1, 7)] = std::make_shared<Knight>();

	tiles[Coordonnees(2, 7)] = std::make_shared<Bishop>();

	tiles[Coordonnees(3, 7)] = std::make_shared<Queen>();

	tiles[Coordonnees(4, 7)] = std::make_shared<King>();

	tiles[Coordonnees(5, 7)] = std::make_shared<Bishop>();

	tiles[Coordonnees(6, 7)] = std::make_shared<Knight>();

	tiles[Coordonnees(7, 7)] = std::make_shared<Rook>();

	for (int y : range(1, 7))
	{
		for (int x : range(8))
		{
			std::shared_ptr<ChessPiece> piece = nullptr;
			if (y == 1) 
			{
				piece = std::make_shared<Pawn>();
				piece->setSide(black);
			}
			else if (y == 6) 
			{
				piece = std::make_shared<Pawn>();
				piece->setSide(white);
			}
			tiles[Coordonnees(x, y)] = move(piece);
		}
	}
	for (int x : range(8))
	{
		tiles[Coordonnees(x, 0)]->setSide(black);
		tiles[Coordonnees(x, 7)]->setSide(white);
	}
}
