#pragma once

#include "ChessPiece.hpp"

class Knight :
    public ChessPiece
{
public:
    Knight();
    QString getImagePath() override;
};

