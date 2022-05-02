#pragma once

#include "ChessPiece.hpp"

class Queen :
    public ChessPiece
{
public:
    Queen() = default;
    ~Queen() override = default;
    QString getImagePath() override;
    //std::vector<Coordonnees> movementsPossibles(std::map<Coordonnees, std::unique_ptr<ChessPiece>> tiles) override;
    //std::vector<Coordonnees> movementsPossibles(std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles) override;
    //std::vector<Coordonnees> attaquesPossibles(std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles) override;

    bool estMovementValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles) override;// { return false; };
    bool estAttaqueValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles) override;// { return false; };

    bool checkDiagonalMov(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles);
    bool checkStraightMov(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles);

};

