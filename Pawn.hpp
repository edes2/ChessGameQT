#pragma once

#include "ChessPiece.hpp"

class Pawn :
    public ChessPiece
{
public:
    Pawn();
    ~Pawn() override = default;

    QString getImagePath() override;

    bool estMovementValide(Coordinates destination, std::map<Coordinates, std::shared_ptr<ChessPiece>> tiles) override;
    bool estAttaqueValide(Coordinates destination, std::map<Coordinates, std::shared_ptr<ChessPiece>> tiles) override;
};

