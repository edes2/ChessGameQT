// Les test pour le Modèle pour calculatrice simple.
// Par Francois-R.Boyer@PolyMtl.ca

#include "ChessBoard.hpp"
#include "ChessPiece.hpp"
#include "Coordonnees.hpp"
#include "namespace.hpp"

#if __has_include("gtest/gtest.h")
#include "gtest/gtest.h"
#endif
#ifdef TEST

TEST(ChessBoard, mouvements)
{
	ChessBoard chess;
	chess.initPartie();

	EXPECT_EQ(chess.tiles[Coordonnees(7, 7)]->getSide(), white);
	EXPECT_EQ(chess.tiles[Coordonnees(5, 0)]->getSide(), black);


	chess.caseAppuye(Coordonnees(4, 6)); // Selection
	chess.caseAppuye(Coordonnees(4, 4)); // Mouvement

	EXPECT_EQ(chess.tiles[Coordonnees(4, 4)]->getSide(), white);
	//EXPECT_EQ(chess.tiles[Coordonnees(4, 4)]->getSide(), white);

	chess.caseAppuye(Coordonnees(4, 1)); // Selection
	chess.caseAppuye(Coordonnees(4, 3)); // Mouvement

	EXPECT_EQ(chess.tiles[Coordonnees(4, 3)]->getSide(), black);

	chess.caseAppuye(Coordonnees(6, 7)); // Selection
	chess.caseAppuye(Coordonnees(5, 5)); // Mouvement

	EXPECT_EQ(chess.tiles[Coordonnees(5, 5)]->getPos(), Coordonnees(5,5));

	chess.caseAppuye(Coordonnees(3, 1)); // Selection
	chess.caseAppuye(Coordonnees(3, 2)); // Mouvement

	EXPECT_EQ(chess.tiles[Coordonnees(3, 2)]->getPos(), Coordonnees(3,2));

	chess.caseAppuye(Coordonnees(3, 6)); // Selection
	chess.caseAppuye(Coordonnees(3, 4)); // Mouvement

	EXPECT_EQ(chess.tiles[Coordonnees(3, 4)]->getPos(), Coordonnees(3, 4));

	EXPECT_EQ(chess.tiles[Coordonnees(5, 3)], nullptr); // Case vide
}
/*
TEST(Calc, simple) {
	Calc calc;
	calc.ajouterChiffre(1);
	calc.ajouterChiffre(4);
	calc.ajouterChiffre(3);
	EXPECT_EQ(calc.obtenirValeur(), 143);
	calc.effacer();
	calc.ajouterChiffre(2);
	calc.ajouterChiffre(1);
	calc.ajouterChiffre(8);
	EXPECT_EQ(calc.obtenirValeur(), 218);
}

TEST(Calc, operations) {
	Calc calc;
	calc.ajouterChiffre(1);
	calc.ajouterChiffre(4);
	calc.ajouterChiffre(3);
	calc.operationPlus();
	calc.ajouterChiffre(2);
	calc.ajouterChiffre(1);
	calc.ajouterChiffre(8);
	calc.operationEgal();
	EXPECT_EQ(calc.obtenirValeur(), 143 + 218);
	calc.ajouterChiffre(1);
	calc.ajouterChiffre(4);
	calc.ajouterChiffre(3);
	calc.operationMoins();
	calc.ajouterChiffre(2);
	calc.ajouterChiffre(1);
	calc.ajouterChiffre(8);
	calc.operationEgal();
	EXPECT_EQ(calc.obtenirValeur(), 143 - 218);
}

TEST(Calc, changement_operation) {
	Calc calc;
	calc.ajouterChiffre(1);
	calc.ajouterChiffre(4);
	calc.ajouterChiffre(3);
	calc.operationPlus();
	calc.operationMoins();
	calc.ajouterChiffre(2);
	calc.ajouterChiffre(1);
	calc.ajouterChiffre(8);
	calc.operationEgal();
	EXPECT_EQ(calc.obtenirValeur(), 143 - 218);
	calc.ajouterChiffre(1);
	calc.ajouterChiffre(4);
	calc.ajouterChiffre(3);
	calc.operationMoins();
	calc.operationPlus();
	calc.ajouterChiffre(2);
	calc.ajouterChiffre(1);
	calc.ajouterChiffre(8);
	calc.operationEgal();
	EXPECT_EQ(calc.obtenirValeur(), 143 + 218);
}
*/
#endif
