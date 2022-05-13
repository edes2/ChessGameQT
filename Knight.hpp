#pragma once

#include "ChessPiece.hpp"

class Knight :
    public ChessPiece
{
public:
    Knight();
    ~Knight() override = default;

    QString getImagePath() override;

    bool estMovementValide(Coordinates destination, std::map<Coordinates, std::shared_ptr<ChessPiece>> tiles) override;
    bool estAttaqueValide(Coordinates destination, std::map<Coordinates, std::shared_ptr<ChessPiece>> tiles) override;
};

