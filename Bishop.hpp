#pragma once

#include "ChessPiece.hpp"

class Bishop :
    public ChessPiece
{
public:
    //Bishop();
    QString getImagePath() override;
};

