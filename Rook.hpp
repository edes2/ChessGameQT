#pragma once

#include "ChessPiece.hpp"

class Rook :
    public ChessPiece
{
public:
    Rook();// = default;
    ~Rook() override = default;
    QString getImagePath() override;
    //std::vector<Coordonnees> movementsPossibles(std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles) override;
    //std::vector<Coordonnees> attaquesPossibles(std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles) override;
    bool estMovementValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles) override;// { return false; };
    bool estAttaqueValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles) override;// { return false; };
    //bool getHasMoved() const;
//private:
    //bool hasMoved;
};

