#pragma once

#include "ChessPiece.hpp"

class Queen :
    public ChessPiece
{
public:
    Queen();
    QString getImagePath() override;
    //std::vector<Coordonnees> movementsPossibles(std::map<Coordonnees, std::unique_ptr<ChessPiece>> tiles) override;
    std::vector<Coordonnees> movementsPossibles(std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles) override;
    std::vector<Coordonnees> attaquesPossibles(std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles) override;

    bool estMovementValide(Coordonnees destination) override;// { return false; };
    bool estAttaqueValide(Coordonnees destination) override;// { return false; };
};

