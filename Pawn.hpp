#pragma once

#include "ChessPiece.hpp"

class Pawn :
    public ChessPiece
{
public:
    Pawn();// = default;
    ~Pawn() override = default;
    QString getImagePath() override;
    //std::vector<Coordonnees> movementsPossibles(std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles) override;
    //std::vector<Coordonnees> attaquesPossibles(std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles) override;
    bool estMovementValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles) override;
    bool estAttaqueValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles) override;
    //bool checkEnPassant(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles);
private:
    //bool avanceDeuxCases;
};

