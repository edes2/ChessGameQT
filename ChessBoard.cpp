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
			emit pieceDeplacee();
		}
		else
		{
			//tryMove(position);
			if (tryMove(position))
			{
				if (tiles[position] && !tiles[position]->getHasMoved()) // Si c est un castling, c est une case vide a tiles[position]
				{
					tiles[position]->setHasMoved();
				}
				std::cout << "move done\n";
				switchTurn();
				if (estEnEchec()) // On a switch de turn.
				{
					if (estEnEchecEtMath()) //je dois faire une fonction dans le roi !!!
					{
						//std::cout << "echec et math\n";
						fin=true;
					}
				}
				updateBoard();
			}
			std::cout << "Deselection case: \n";
			caseSelectionnee = nullptr;
			emit pieceDeplacee();
			if (fin)
			{
				partieTerminee();
			}
		}
	}
	else
	{
		if (tiles[position] && tiles[position]->getSide() == turn_)
		{
			caseSelectionnee = std::make_shared<Coordonnees>(position);
			std::cout << "Nouvelle selection d'une case: \n";
			std::cout << "X: " << (*caseSelectionnee).x << ", Y: " << (*caseSelectionnee).y << std::endl;
			mouvementsPossibles();
		}
	}
}

void ChessBoard::mouvementsPossibles()
{
	std::shared_ptr<ChessPiece> backup;
	for (int y : range(8))
	{
		for (int x : range(8))
		{
			backup = nullptr;
			Coordonnees coord(x, y);
			if (tiles[coord])
			{
				backup = tiles[coord];
			}
			if (tiles[coord] && tiles[*caseSelectionnee]->getType() == king && tiles[coord]->getType() == rook)
			{
				estBackup = true;
				if (tryMove(coord))
				{
					emit selectionPossible(coord);
				}
				estBackup = false;
			}
			else {
				if (tryMove(coord))
				{
				
					tiles[*caseSelectionnee] = move(tiles[coord]);
					tiles[*caseSelectionnee]->updatePos(*caseSelectionnee);

					if (backup)
					{
						tiles[coord] = move(backup);
						tiles[coord]->updatePos(coord);
					}
					// EMIT ? CASE EN BLEUE
					emit selectionPossible(coord);
				}
			}
		}
	}
	emit selectionPossible(*caseSelectionnee);
}

bool ChessBoard::tryMove(Coordonnees destination)
{
	//estEnEchec();
	if (tiles[destination])
	{
		//if ((tiles[*caseSelectionnee]->getSide() != tiles[destination]->getSide()) 
		//	&& tiles[*caseSelectionnee]->estAttaqueValide(destination, tiles))
		if (tiles[*caseSelectionnee]->estAttaqueValide(destination, tiles))
		{
			if (tiles[*caseSelectionnee]->getType() == king && tiles[destination]->getType() == rook)//rook && king//checkCastling(destination))
			{
				if (tryCastling(destination))
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			std::shared_ptr<ChessPiece> backup = tiles[destination]; // Pour echec

			tiles[destination] = move(tiles[*caseSelectionnee]);
			tiles[destination]->updatePos(destination); // Update manuellement pos ?pour si roi

			if (estEnEchec())
			{
				//Revenir en arriere
				std::cout << "Attaque not valid, echec \n";
				tiles[*caseSelectionnee] = move(tiles[destination]);
				tiles[*caseSelectionnee]->updatePos(*caseSelectionnee);

				tiles[destination] = backup;
				tiles[destination]->updatePos(destination);
				return false;
			}
			else {
				std::cout << "Attaque\n";
				//switchTurn();
				//emit pieceDeplacee();
				return true;
			}
		}
	}
	else
	{
		if (tiles[*caseSelectionnee]->estMovementValide(destination, tiles))
		{
			tiles[destination] = move(tiles[*caseSelectionnee]);
			//std::shared_ptr<ChessPiece> backup = tiles[destination]; // Pour echec
			tiles[destination]->updatePos(destination); // Update manuellement pos ?pour si roi
			if (estEnEchec())
			{
				//Revenir en arriere
				std::cout << "Move not valid, echec \n";
				tiles[*caseSelectionnee] = move(tiles[destination]);
				tiles[*caseSelectionnee]->updatePos(*caseSelectionnee);
				//tiles[destination] = backup;
				return false;
			}
			else {
				//switchTurn();

				std::cout << "Mouvement d'une piece: \n";
				std::cout << "X: " << (*caseSelectionnee).x << ", Y: " << (*caseSelectionnee).y << std::endl;
				std::cout << "Vers case: \n";
				std::cout << "X: " << destination.x << ", Y: " << destination.y << std::endl;
				//emit pieceDeplacee();
				return true;
			}			
		}
	}
	return false;
}

bool ChessBoard::tryCastling(Coordonnees position)
{
	// verifier si le king est deja en echec
	if (estEnEchec())
	{
		return false;
	}
	Coordonnees diff(position.x - (*caseSelectionnee).x, position.y - (*caseSelectionnee).y);
	//std::shared_ptr<ChessPiece> backup = tiles[position]; //backup position du rook

	Coordonnees nouvelleposKing((*caseSelectionnee).x, (*caseSelectionnee).y);
	Coordonnees nouvelleposRook(position.x, position.y);
	if (diff.x > 0) //rook de droite
	{
		nouvelleposKing.x = (*caseSelectionnee).x + 2;
		nouvelleposRook.x = position.x - 2;//(position.x - 2, position.y);
	}
	else
	{
		nouvelleposKing.x = (*caseSelectionnee).x - 2;
		//nouvelleposKing((*caseSelectionnee).x - 2, (*caseSelectionnee).y);
		nouvelleposRook.x = position.x + 3;
		//nouvelleposRook(position.x + 3, position.y);
	}
	tiles[nouvelleposKing] = move(tiles[*caseSelectionnee]);
	tiles[nouvelleposKing]->updatePos(nouvelleposKing);

	tiles[nouvelleposRook] = move(tiles[position]);
	tiles[nouvelleposRook]->updatePos(nouvelleposRook);

	if (estEnEchec())
	{
		//Revenir en arriere
		std::cout << "castling not valid, echec \n";
		tiles[*caseSelectionnee] = move(tiles[nouvelleposKing]);
		tiles[*caseSelectionnee]->updatePos(*caseSelectionnee);

		tiles[position] = move(tiles[nouvelleposRook]);
		tiles[position]->updatePos(position);
		return false;
	}
	else {
		std::cout << "Castling!\n";
		//switchTurn();
		//emit pieceDeplacee();
		if (estBackup) //var bool
		{
			tiles[*caseSelectionnee] = move(tiles[nouvelleposKing]);
			tiles[*caseSelectionnee]->updatePos(*caseSelectionnee);
			
			tiles[position] = move(tiles[nouvelleposRook]);
			tiles[position]->updatePos(position);
		}
		else {
			tiles[nouvelleposKing]->setHasMoved();
			tiles[nouvelleposRook]->setHasMoved();
		}
		return true;
	}
	
}

bool ChessBoard::estEnEchecEtMath()
{
	//bool blancEchecMath=true;
	std::shared_ptr<ChessPiece> backup;
	// On check si blanc en echec et math
	//if (!estEnEchec()) {
	//	//blancEchecMath = false;
	//	return false;
	//}
	for (int y : range(8))
	{
		for (int x : range(8))
		{
			if (tiles[Coordonnees(x, y)] && tiles[Coordonnees(x, y)]->getSide() == turn_)
			{
				caseSelectionnee = std::make_shared<Coordonnees>(Coordonnees(x, y));
				for (int j : range(8))
				{
					for (int i : range(8))
					{

						backup = tiles[Coordonnees(i, j)];
						if (tryMove(Coordonnees(i, j))) // Coordonnees(i,j) != Coordonnees(x,y) && 
						{
							//On revient en arriere
							tiles[*caseSelectionnee] = move(tiles[Coordonnees(i, j)]);
							tiles[*caseSelectionnee]->updatePos(*caseSelectionnee);

							tiles[Coordonnees(i, j)] = move(backup);
							if (tiles[Coordonnees(i, j)])
							{
								tiles[Coordonnees(i, j)]->updatePos(Coordonnees(i, j));
							}
							return false; // Il y a une solution possible !

						}
					}
				}
			}
		}
	}
	return true;
	/*
	std::shared_ptr<Coordonnees> backup = caseSelectionnee;
	std::shared_ptr<ChessPiece> backupPiece;
	bool EchecMathWhite = true;
	bool EchecMathBlack = true;
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; i <= 1; i++)
		{
			caseSelectionnee = std::make_shared<Coordonnees>(whiteKing->getPos());
			///
			Coordonnees destination(whiteKing->getPos().x + i, whiteKing->getPos().y + j);
			if ((tiles[destination] == nullptr) || (tiles[destination]->getSide() != whiteKing->getSide()))
			{
				if (tiles[destination])
				{
					backupPiece = tiles[destination];
				}
				tiles[destination] = move(tiles[*caseSelectionnee]);
				tiles[destination]->updatePos(destination);
				if (!estEnEchec())
				{
					EchecMathWhite = false;
					//return false; // il y a une way out
				}
				// On revient en arriere.
				tiles[*caseSelectionnee] = move(tiles[destination]);
				tiles[*caseSelectionnee]->updatePos(*caseSelectionnee);
				if (backupPiece)
				{
					tiles[destination] = move(backupPiece);
					tiles[destination]->updatePos(destination);
				}
			}
			
			// Black King
			caseSelectionnee = std::make_shared<Coordonnees>(blackKing->getPos());
			///
			destination = Coordonnees(blackKing->getPos().x + i, blackKing->getPos().y + j);
			if ((tiles[destination] == nullptr) || (tiles[destination]->getSide() != blackKing->getSide()))
			{
				if (tiles[destination])
				{
					backupPiece = tiles[destination];
				}
				tiles[destination] = move(tiles[*caseSelectionnee]);
				tiles[destination]->updatePos(destination);
				if (!estEnEchec())
				{
					EchecMathBlack = false;
					//return false; // il y a une way out
				}
				// On revient en arriere.
				tiles[*caseSelectionnee] = move(tiles[destination]);
				tiles[*caseSelectionnee]->updatePos(*caseSelectionnee);
				if (backupPiece)
				{
					tiles[destination] = move(backupPiece);
					tiles[destination]->updatePos(destination);
				}
			}
		}
	}
	if (EchecMathBlack) { std::cout << "Echec et Math roi noir\n"; };
	if (EchecMathWhite) { std::cout << "Echec et Math roi blanc\n"; };
	//caseSelectionnee = backup;
	*/
}

bool ChessBoard::estEnEchec()
{
	std::shared_ptr<ChessPiece> king;
	if (turn_ == white)
	{
		king = whiteKing;
	}
	else
	{
		king = blackKing;
	}
	for (int y : range(8))
	{
		for (int x : range(8))
		{
			Coordonnees coord(x, y);
			if (tiles[coord])
			{
				//if (tiles[coord] == whiteKing || tiles[coord] == blackKing) {
				//	//skip?
				//	int a = 0;
				//}
				if (tiles[coord]->getSide() != turn_) // Piece enemie
				{
					if (tiles[coord]->estAttaqueValide(king->getPos(), tiles))
					{
						std::cout << "Roi en echec\n";

						return true;
					}
				}
			}
		}
	}
	return false;
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

// comment faire dans une seule boucle???
void ChessBoard::initPartie()
{
	estBackup = false; // Pour percevoir les mouvements a l avance.
	fin = false; // Pour savoir quand la partie est finie

	turn_ = white;

	tiles[Coordonnees(0,0)] = std::make_shared<Rook>();

	tiles[Coordonnees(1, 0)] = std::make_shared<Knight>();

	tiles[Coordonnees(2, 0)] = std::make_shared<Bishop>();

	tiles[Coordonnees(3, 0)] = std::make_shared<Queen>();

	tiles[Coordonnees(4, 0)] = std::make_shared<King>();
	blackKing = tiles[Coordonnees(4, 0)];

	tiles[Coordonnees(4, 7)] = std::make_shared<King>();
	whiteKing = tiles[Coordonnees(4, 7)];

	tiles[Coordonnees(5, 0)] = std::make_shared<Bishop>();

	tiles[Coordonnees(6, 0)] = std::make_shared<Knight>();

	tiles[Coordonnees(7, 0)] = std::make_shared<Rook>();

	tiles[Coordonnees(0, 7)] = std::make_shared<Rook>();

	tiles[Coordonnees(1, 7)] = std::make_shared<Knight>();

	tiles[Coordonnees(2, 7)] = std::make_shared<Bishop>();

	tiles[Coordonnees(3, 7)] = std::make_shared<Queen>();

	tiles[Coordonnees(5, 7)] = std::make_shared<Bishop>();

	tiles[Coordonnees(6, 7)] = std::make_shared<Knight>();

	tiles[Coordonnees(7, 7)] = std::make_shared<Rook>();

	for (int y : range(1, 7))
	{
		for (int x : range(8))
		{
			std::shared_ptr<ChessPiece> piece = nullptr;
			Coordonnees coord(x, y);
			if (y == 1) 
			{
				piece = std::make_shared<Pawn>();
				piece->setSide(black);
				piece->updatePos(coord);
			}
			else if (y == 6)
			{
				piece = std::make_shared<Pawn>();
				piece->setSide(white);
				piece->updatePos(coord);
			}
			tiles[Coordonnees(x, y)] = move(piece);
		}
	}

	for (int x : range(8))
	{
		Coordonnees coord0(x, 0);
		Coordonnees coord7(x, 7);
		tiles[coord0]->setSide(black);
		tiles[coord0]->updatePos(coord0);
		tiles[coord7]->setSide(white);
		tiles[coord7]->updatePos(coord7);
	}
}

void ChessBoard::partieTerminee()
{
	side losingSide = turn_;
	if (losingSide == white)
	{
		//std::cout << "Les blancs sont en echec et math!\n";
		emit finPartie(white);
	}
	else
	{
		//std::cout << "Les noirs sont en echec et math!\n";
		emit finPartie(black);
	}
}

void ChessBoard::updateBoard()
{
	for (int y : range(8))
	{
		for (int x : range(8))
		{
			Coordonnees position(x, y);
			if (tiles[position])
			{
				tiles[position]->updatePos(position);
			}
		}
	}
	//emit pieceDeplacee();
}
