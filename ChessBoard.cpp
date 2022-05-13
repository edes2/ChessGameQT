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

void ChessBoard::caseAppuye(Coordinates iPosition)
{
	if (pCaseSelectionnee)
	{
		if ((*pCaseSelectionnee) == iPosition)
		{
			pCaseSelectionnee = nullptr;
			emit pieceDeplacee();
		}
		else
		{
			if (tryMove(iPosition))
			{
				if (mTiles[iPosition] && !mTiles[iPosition]->getHasMoved())
				{
					mTiles[iPosition]->setHasMoved();
				}
				checkPawnTransform(iPosition);
				switchTurn();
				if (estEnEchec())
				{
					if (estEnEchecEtMath())
					{
						mFin=true;
					}
				}
				updateBoard();
			}
			pCaseSelectionnee = nullptr;
			emit pieceDeplacee();
			if (mFin)
			{
				partieTerminee();
			}
		}
	}
	else
	{
		if (mTiles[iPosition] && mTiles[iPosition]->getSide() == mTurn)
		{
			pCaseSelectionnee = std::make_shared<Coordinates>(iPosition);
			mouvementsPossibles();
		}
	}
}

void ChessBoard::checkPawnTransform(Coordinates iPosition)
{
	if (mTiles[iPosition] && mTiles[iPosition]->getType() == pawn && (iPosition.y == 7 || iPosition.y == 0))
	{
		emit inputPawnTranform(iPosition);
	}
}

void ChessBoard::pawnTranform(const QString& sPieceType, Coordinates iPosition)
{
	if (sPieceType == "Queen") { mTiles[iPosition] = std::make_shared<Queen>(); }
	else if (sPieceType=="Bishop") { mTiles[iPosition] = std::make_shared<Bishop>(); }
	else if (sPieceType == "Knight") { mTiles[iPosition] = std::make_shared<Knight>(); }
	else if (sPieceType == "Rook") { mTiles[iPosition] = std::make_shared<Rook>(); }
	mTiles[iPosition]->updatePos(iPosition);
	mTiles[iPosition]->setHasMoved();
	mTiles[iPosition]->setSide(mTurn);
}

void ChessBoard::mouvementsPossibles()
{
	std::shared_ptr<ChessPiece> backup;
	for (int y : range(8))
	{
		for (int x : range(8))
		{
			backup = nullptr;
			Coordinates coord(x, y);
			if (mTiles[coord])
			{
				backup = mTiles[coord];
			}
			if (mTiles[coord] && mTiles[*pCaseSelectionnee]->getType() == king && mTiles[coord]->getType() == rook)
			{
				mEstBackup = true;
				if (tryMove(coord))
				{
					emit selectionPossible(coord);
				}
				mEstBackup = false;
			}
			else {
				if (tryMove(coord))
				{
				
					mTiles[*pCaseSelectionnee] = move(mTiles[coord]);
					mTiles[*pCaseSelectionnee]->updatePos(*pCaseSelectionnee);

					if (backup)
					{
						mTiles[coord] = move(backup);
						mTiles[coord]->updatePos(coord);
					}
					emit selectionPossible(coord);
				}
			}
		}
	}
	emit selectionPossible(*pCaseSelectionnee);
}

bool ChessBoard::tryMove(Coordinates destination)
{
	if (mTiles[destination])
	{
		if (mTiles[*pCaseSelectionnee]->estAttaqueValide(destination, mTiles))
		{
			if (mTiles[*pCaseSelectionnee]->getType() == king && mTiles[destination]->getType() == rook && mTiles[destination]->getSide() == mTiles[destination]->getSide())
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
			std::shared_ptr<ChessPiece> backup = mTiles[destination];

			mTiles[destination] = move(mTiles[*pCaseSelectionnee]);
			mTiles[destination]->updatePos(destination);

			if (estEnEchec())
			{
				mTiles[*pCaseSelectionnee] = move(mTiles[destination]);
				mTiles[*pCaseSelectionnee]->updatePos(*pCaseSelectionnee);

				mTiles[destination] = backup;
				mTiles[destination]->updatePos(destination);
				return false;
			}
			else {
				return true;
			}
		}
	}
	else
	{
		if (mTiles[*pCaseSelectionnee]->estMovementValide(destination, mTiles))
		{
			mTiles[destination] = move(mTiles[*pCaseSelectionnee]);
			mTiles[destination]->updatePos(destination);
			if (estEnEchec())
			{
				mTiles[*pCaseSelectionnee] = move(mTiles[destination]);
				mTiles[*pCaseSelectionnee]->updatePos(*pCaseSelectionnee);
				return false;
			}
			else {
				return true;
			}			
		}
	}
	return false;
}

bool ChessBoard::tryCastling(Coordinates position)
{
	if (estEnEchec())
	{
		return false;
	}
	Coordinates diff(position.x - (*pCaseSelectionnee).x, position.y - (*pCaseSelectionnee).y);

	Coordinates nouvelleposKing((*pCaseSelectionnee).x, (*pCaseSelectionnee).y);
	Coordinates nouvelleposRook(position.x, position.y);
	if (diff.x > 0)
	{
		nouvelleposKing.x = (*pCaseSelectionnee).x + 2;
		nouvelleposRook.x = position.x - 2;
	}
	else
	{
		nouvelleposKing.x = (*pCaseSelectionnee).x - 2;
		nouvelleposRook.x = position.x + 3;
	}
	mTiles[nouvelleposKing] = move(mTiles[*pCaseSelectionnee]);
	mTiles[nouvelleposKing]->updatePos(nouvelleposKing);

	mTiles[nouvelleposRook] = move(mTiles[position]);
	mTiles[nouvelleposRook]->updatePos(nouvelleposRook);

	if (estEnEchec())
	{
		mTiles[*pCaseSelectionnee] = move(mTiles[nouvelleposKing]);
		mTiles[*pCaseSelectionnee]->updatePos(*pCaseSelectionnee);

		mTiles[position] = move(mTiles[nouvelleposRook]);
		mTiles[position]->updatePos(position);
		return false;
	}
	else {
		if (mEstBackup)
		{
			mTiles[*pCaseSelectionnee] = move(mTiles[nouvelleposKing]);
			mTiles[*pCaseSelectionnee]->updatePos(*pCaseSelectionnee);
			
			mTiles[position] = move(mTiles[nouvelleposRook]);
			mTiles[position]->updatePos(position);
		}
		else {
			mTiles[nouvelleposKing]->setHasMoved();
			mTiles[nouvelleposRook]->setHasMoved();
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
			if (mTiles[Coordinates(x, y)] && mTiles[Coordinates(x, y)]->getSide() == mTurn)
			{
				pCaseSelectionnee = std::make_shared<Coordinates>(Coordinates(x, y));
				for (int j : range(8))
				{
					for (int i : range(8))
					{

						backup = mTiles[Coordinates(i, j)];
						if (tryMove(Coordinates(i, j)))
						{
							mTiles[*pCaseSelectionnee] = move(mTiles[Coordinates(i, j)]);
							mTiles[*pCaseSelectionnee]->updatePos(*pCaseSelectionnee);

							mTiles[Coordinates(i, j)] = move(backup);
							if (mTiles[Coordinates(i, j)])
							{
								mTiles[Coordinates(i, j)]->updatePos(Coordinates(i, j));
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
	if (mTurn == white)
	{
		king = pWhiteKing;
	}
	else
	{
		king = pBlackKing;
	}
	for (int y : range(8))
	{
		for (int x : range(8))
		{
			Coordinates coord(x, y);
			if (mTiles[coord])
			{
				if (mTiles[coord]->getSide() != mTurn)
				{
					if (mTiles[coord]->estAttaqueValide(king->getPos(), mTiles))
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
	return mTurn;
}

void ChessBoard::switchTurn()
{
	if (mTurn == white) {
		mTurn = black;
	}
	else
	{
		mTurn = white;
	}
	emit showTurn(mTurn);
}

void ChessBoard::restartPartie()
{
	mTiles.clear();
	pWhiteKing = nullptr;
	pBlackKing = nullptr;
	pCaseSelectionnee = nullptr;

	initPartie();

	emit pieceDeplacee();
}

void ChessBoard::initPartie()
{
	mEstBackup = false; // Pour percevoir les mouvements a l avance.
	mFin = false; // Pour savoir quand la partie est finie

	mTurn = white;

	emit showTurn(mTurn);

	mTiles[Coordinates(0,0)] = std::make_shared<Rook>();

	mTiles[Coordinates(1, 0)] = std::make_shared<Knight>();

	mTiles[Coordinates(2, 0)] = std::make_shared<Bishop>();

	mTiles[Coordinates(3, 0)] = std::make_shared<Queen>();

	mTiles[Coordinates(4, 0)] = std::make_shared<King>();

	pBlackKing = mTiles[Coordinates(4, 0)];

	mTiles[Coordinates(4, 7)] = std::make_shared<King>();

	pWhiteKing = mTiles[Coordinates(4, 7)];

	mTiles[Coordinates(5, 0)] = std::make_shared<Bishop>();

	mTiles[Coordinates(6, 0)] = std::make_shared<Knight>();

	mTiles[Coordinates(7, 0)] = std::make_shared<Rook>();

	mTiles[Coordinates(0, 7)] = std::make_shared<Rook>();

	mTiles[Coordinates(1, 7)] = std::make_shared<Knight>();

	mTiles[Coordinates(2, 7)] = std::make_shared<Bishop>();

	mTiles[Coordinates(3, 7)] = std::make_shared<Queen>();

	mTiles[Coordinates(5, 7)] = std::make_shared<Bishop>();

	mTiles[Coordinates(6, 7)] = std::make_shared<Knight>();

	mTiles[Coordinates(7, 7)] = std::make_shared<Rook>();

	for (int y : range(1, 7))
	{
		for (int x : range(8))
		{
			std::shared_ptr<ChessPiece> piece = nullptr;
			Coordinates coord(x, y);
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
			mTiles[Coordinates(x, y)] = move(piece);
		}
	}

	for (int x : range(8))
	{
		Coordinates coord0(x, 0);
		Coordinates coord7(x, 7);
		mTiles[coord0]->setSide(black);
		mTiles[coord0]->updatePos(coord0);
		mTiles[coord7]->setSide(white);
		mTiles[coord7]->updatePos(coord7);
	}
}

void ChessBoard::partieTerminee()
{
	side losingSide = mTurn;
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
			Coordinates position(x, y);
			if (mTiles[position])
			{
				mTiles[position]->updatePos(position);
			}
		}
	}
}

bool ChessBoard::getFin() const
{
	return mFin;
}
