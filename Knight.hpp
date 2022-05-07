#pragma once

#include "ChessPiece.hpp"

class Knight :
    public ChessPiece
{
public:
    Knight();
    ~Knight() override = default;

    QString getImagePath() override;

    bool estMovementValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles) override;
    bool estAttaqueValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles) override;
};

