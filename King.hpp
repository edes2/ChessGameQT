#pragma once

#include "ChessPiece.hpp"

class King :
    public ChessPiece
{
public:
    King();
    ~King() override;

    QString getImagePath() override;

    bool estMovementValide(Coordinates destination, std::map<Coordinates, std::shared_ptr<ChessPiece>> tiles) override;// { return false; };
    bool estAttaqueValide(Coordinates destination, std::map<Coordinates, std::shared_ptr<ChessPiece>> tiles) override;// { return false; };
};

