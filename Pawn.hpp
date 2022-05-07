#pragma once

#include "ChessPiece.hpp"

class Pawn :
    public ChessPiece
{
public:
    Pawn();
    ~Pawn() override = default;

    QString getImagePath() override;

    bool estMovementValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles) override;
    bool estAttaqueValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles) override;
};

