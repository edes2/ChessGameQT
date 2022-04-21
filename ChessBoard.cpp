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

void ChessBoard::caseAppuye(Coordonnees position)//std::pair<int, int> position)
{
	if (caseSelectionnee) // Il y a déjà une pièce sélectionnée
	{
		if ((*caseSelectionnee) == position) //Si on clique sur la meme case ça deselectionne
		{
			caseSelectionnee = nullptr;
			std::cout << "Deselection case: \n";
		}
		else
		{
			tryMove(position);
			std::cout << "Deselection case: \n";
			caseSelectionnee = nullptr; // On reset caseSelect apres le mouvement
			/*
			std::vector<std::pair<int, int>> movements = tiles[position]->mouvementsValides(tiles);
			for (auto&& it : movements)
			{
				if (position == it)
				{

				}
			}
			*/
			
		}
		/////////////// faire ceci dans fonction
		/*
		if (!tiles[position]) //La case est vide, on peut donc deplacer piece (il faut valider mouvement bien sur)
		{
			// void checkValidMove();
			tiles[position] = move(tiles[*caseSelectionnee]);
			
			//emit pieceDeplacee();// Envoyer signal a la vue
			std::cout << "Mouvement d'une piece: \n";
			std::cout << "X: " << (*caseSelectionnee).first << ", Y: " << (*caseSelectionnee).second << std::endl;
			std::cout << "Vers case: \n";
			std::cout << "X: " << position.first << ", Y: " << position.second << std::endl;
			
			
			emit pieceDeplacee();
		}
		*/
		
		////////////
	}
	else
	{
		if (tiles[position] && tiles[position]->getSide() == turn_)// Verifier si c'est une piece
		{
			caseSelectionnee = std::make_unique<Coordonnees>(position);
			std::cout << "Nouvelle selection d'une case: \n";
			std::cout << "X: " << (*caseSelectionnee).x << ", Y: " << (*caseSelectionnee).y << std::endl;
		}
	}

	//if (caseSelectionnee
	//std::cout << "X: " << position.first << ", Y: " << position.second << std::endl;
}

void ChessBoard::tryMove(Coordonnees destination)//std::pair<int, int> destination)
{
	//pieceEmplacement = caseSelectionnee;
	//piece->estMovementValide(destionation/typepiecedestination, emplacement)
	if (tiles[destination]) // On veut attaquer une piece
	{
		if (tiles[*caseSelectionnee]->estAttaqueValide(destination))//, tiles))
		{
			//pieceAttaque(destination); // Piece est dans select et destination
			std::cout << "Attaque\n";
			switchTurn();
		}
	}
	else
	{
		if (tiles[*caseSelectionnee]->estMovementValide(destination))//, tiles))
		{
			//pieceMouvement(destination); // Piece est dans select et destination
			// void checkValidMove();
			tiles[destination] = move(tiles[*caseSelectionnee]);
			switchTurn();

				//emit pieceDeplacee();// Envoyer signal a la vue
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

	tiles[Coordonnees(0,0)] = std::make_unique<Rook>();

	tiles[Coordonnees(1, 0)] = std::make_unique<Knight>();

	tiles[Coordonnees(2, 0)] = std::make_unique<Bishop>();

	tiles[Coordonnees(3, 0)] = std::make_unique<Queen>();

	tiles[Coordonnees(4, 0)] = std::make_unique<King>();

	tiles[Coordonnees(5, 0)] = std::make_unique<Bishop>();

	tiles[Coordonnees(6, 0)] = std::make_unique<Knight>();

	tiles[Coordonnees(7, 0)] = std::make_unique<Rook>();

	///

	tiles[Coordonnees(0, 7)] = std::make_unique<Rook>();

	tiles[Coordonnees(1, 7)] = std::make_unique<Knight>();

	tiles[Coordonnees(2, 7)] = std::make_unique<Bishop>();

	tiles[Coordonnees(3, 7)] = std::make_unique<Queen>();

	tiles[Coordonnees(4, 7)] = std::make_unique<King>();

	tiles[Coordonnees(5, 7)] = std::make_unique<Bishop>();

	tiles[Coordonnees(6, 7)] = std::make_unique<Knight>();

	tiles[Coordonnees(7, 7)] = std::make_unique<Rook>();

	for (int y : range(1, 7))
	{
		for (int x : range(8))
		{
			// Il faut remplir avec pieces, pas chesspiece !!!!!!!
			std::unique_ptr<ChessPiece> piece = nullptr;
			if (y == 1) {
				piece = std::make_unique<Pawn>();
				piece->setSide(black);
			}
			else if (y == 6) {
				piece = std::make_unique<Pawn>();
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