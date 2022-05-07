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

TEST(ChessBoard, echecEtMath)
{
	ChessBoard chess;
	chess.initPartie();

	chess.caseAppuye(Coordonnees(4, 6)); // Selection
	chess.caseAppuye(Coordonnees(4, 4)); // Mouvement

	chess.caseAppuye(Coordonnees(4, 1)); // Selection
	chess.caseAppuye(Coordonnees(4, 2)); // Mouvement

	chess.caseAppuye(Coordonnees(3, 7)); // Selection
	chess.caseAppuye(Coordonnees(5, 5)); // Mouvement

	chess.caseAppuye(Coordonnees(4, 2)); // Selection
	chess.caseAppuye(Coordonnees(4, 3)); // Mouvement

	chess.caseAppuye(Coordonnees(5, 7)); // Selection
	chess.caseAppuye(Coordonnees(2, 4)); // Mouvement

	chess.caseAppuye(Coordonnees(0, 1)); // Selection
	chess.caseAppuye(Coordonnees(0, 2)); // Mouvement

	chess.caseAppuye(Coordonnees(5, 5)); // Selection
	chess.caseAppuye(Coordonnees(5, 1)); // Mouvement

	EXPECT_EQ(chess.getFin(), true);

}
#endif
