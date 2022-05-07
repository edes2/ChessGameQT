#pragma once

#include "ChessPiece.hpp"

class King :
    public ChessPiece
{
public:
    King();
    ~King() override;

    QString getImagePath() override;

    bool estMovementValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles) override;// { return false; };
    bool estAttaqueValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles) override;// { return false; };
private:
    static int compteur;
};

