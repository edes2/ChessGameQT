#pragma once

#include "ChessPiece.hpp"

class Queen :
    public ChessPiece
{
public:
    Queen();
    ~Queen() override = default;

    QString getImagePath() override;

    bool estMovementValide(Coordinates destination, std::map<Coordinates, std::shared_ptr<ChessPiece>> tiles) override;
    bool estAttaqueValide(Coordinates destination, std::map<Coordinates, std::shared_ptr<ChessPiece>> tiles) override;

    bool checkDiagonalMov(Coordinates destination, std::map<Coordinates, std::shared_ptr<ChessPiece>> tiles);
    bool checkStraightMov(Coordinates destination, std::map<Coordinates, std::shared_ptr<ChessPiece>> tiles);

};

