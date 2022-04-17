#pragma once

#include "ChessPiece.hpp"

class Queen :
    public ChessPiece
{
public:
    Queen();
    QString getImagePath() override;
};

