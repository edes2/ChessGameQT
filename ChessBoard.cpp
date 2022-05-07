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
			emit pieceDeplacee();
		}
		else
		{
			if (tryMove(position))
			{
				if (tiles[position] && !tiles[position]->getHasMoved())
				{
					tiles[position]->setHasMoved();
				}
				switchTurn();
				if (estEnEchec())
				{
					if (estEnEchecEtMath())
					{
						fin_=true;
					}
				}
				updateBoard();
			}
			caseSelectionnee = nullptr;
			emit pieceDeplacee();
			if (fin_)
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
				estBackup_ = true;
				if (tryMove(coord))
				{
					emit selectionPossible(coord);
				}
				estBackup_ = false;
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
					emit selectionPossible(coord);
				}
			}
		}
	}
	emit selectionPossible(*caseSelectionnee);
}

bool ChessBoard::tryMove(Coordonnees destination)
{
	if (tiles[destination])
	{
		if (tiles[*caseSelectionnee]->estAttaqueValide(destination, tiles))
		{
			if (tiles[*caseSelectionnee]->getType() == king && tiles[destination]->getType() == rook)
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
			std::shared_ptr<ChessPiece> backup = tiles[destination];

			tiles[destination] = move(tiles[*caseSelectionnee]);
			tiles[destination]->updatePos(destination);

			if (estEnEchec())
			{
				tiles[*caseSelectionnee] = move(tiles[destination]);
				tiles[*caseSelectionnee]->updatePos(*caseSelectionnee);

				tiles[destination] = backup;
				tiles[destination]->updatePos(destination);
				return false;
			}
			else {
				return true;
			}
		}
	}
	else
	{
		if (tiles[*caseSelectionnee]->estMovementValide(destination, tiles))
		{
			tiles[destination] = move(tiles[*caseSelectionnee]);
			tiles[destination]->updatePos(destination);
			if (estEnEchec())
			{
				tiles[*caseSelectionnee] = move(tiles[destination]);
				tiles[*caseSelectionnee]->updatePos(*caseSelectionnee);
				return false;
			}
			else {
				return true;
			}			
		}
	}
	return false;
}

bool ChessBoard::tryCastling(Coordonnees position)
{
	if (estEnEchec())
	{
		return false;
	}
	Coordonnees diff(position.x - (*caseSelectionnee).x, position.y - (*caseSelectionnee).y);

	Coordonnees nouvelleposKing((*caseSelectionnee).x, (*caseSelectionnee).y);
	Coordonnees nouvelleposRook(position.x, position.y);
	if (diff.x > 0)
	{
		nouvelleposKing.x = (*caseSelectionnee).x + 2;
		nouvelleposRook.x = position.x - 2;
	}
	else
	{
		nouvelleposKing.x = (*caseSelectionnee).x - 2;
		nouvelleposRook.x = position.x + 3;
	}
	tiles[nouvelleposKing] = move(tiles[*caseSelectionnee]);
	tiles[nouvelleposKing]->updatePos(nouvelleposKing);

	tiles[nouvelleposRook] = move(tiles[position]);
	tiles[nouvelleposRook]->updatePos(nouvelleposRook);

	if (estEnEchec())
	{
		tiles[*caseSelectionnee] = move(tiles[nouvelleposKing]);
		tiles[*caseSelectionnee]->updatePos(*caseSelectionnee);

		tiles[position] = move(tiles[nouvelleposRook]);
		tiles[position]->updatePos(position);
		return false;
	}
	else {
		if (estBackup_)
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
	std::shared_ptr<ChessPiece> backup;

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
						if (tryMove(Coordonnees(i, j)))
						{
							tiles[*caseSelectionnee] = move(tiles[Coordonnees(i, j)]);
							tiles[*caseSelectionnee]->updatePos(*caseSelectionnee);

							tiles[Coordonnees(i, j)] = move(backup);
							if (tiles[Coordonnees(i, j)])
							{
								tiles[Coordonnees(i, j)]->updatePos(Coordonnees(i, j));
							}
							return false;

						}
					}
				}
			}
		}
	}
	return true;
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
				if (tiles[coord]->getSide() != turn_)
				{
					if (tiles[coord]->estAttaqueValide(king->getPos(), tiles))
					{
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
	emit showTurn(turn_);
}

void ChessBoard::restartPartie()
{
	tiles.clear();
	whiteKing = nullptr;
	blackKing = nullptr;
	caseSelectionnee = nullptr;

	initPartie();

	emit pieceDeplacee();
}

void ChessBoard::initPartie()
{
	estBackup_ = false; // Pour percevoir les mouvements a l avance.
	fin_ = false; // Pour savoir quand la partie est finie

	turn_ = white;

	emit showTurn(turn_);

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
		emit finPartie(white);
	}
	else
	{
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
}

bool ChessBoard::getFin() const
{
	return fin_;
}
