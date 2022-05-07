#pragma once

#include "ChessPiece.hpp"

class Queen :
    public ChessPiece
{
public:
    Queen();
    ~Queen() override = default;

    QString getImagePath() override;

    bool estMovementValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles) override;
    bool estAttaqueValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles) override;

    bool checkDiagonalMov(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles);
    bool checkStraightMov(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles);

};

