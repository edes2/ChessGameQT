#pragma once

#include "ChessPiece.hpp"

class King :
    public ChessPiece
{
public:
    King();
    QString getImagePath() override;
    std::vector<Coordonnees> movementsPossibles(std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles) override;
    std::vector<Coordonnees> attaquesPossibles(std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles) override;

    bool estMovementValide(Coordonnees destination) override;// { return false; };
    bool estAttaqueValide(Coordonnees destination) override;// { return false; };
private:
    static int compteur;
};

