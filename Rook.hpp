#pragma once

#include "ChessPiece.hpp"

class Rook :
    public ChessPiece
{
public:
    Rook();
    QString getImagePath() override;
};

