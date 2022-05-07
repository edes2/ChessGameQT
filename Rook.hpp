#pragma once

#include "ChessPiece.hpp"

class Rook :
    public ChessPiece
{
public:
    Rook();
    ~Rook() override = default;

    QString getImagePath() override;

    bool estMovementValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles) override;
    bool estAttaqueValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles) override;
};

