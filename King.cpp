#include "King.hpp"

int King::compteur = 0;

King::King()
{
	if (compteur >= 2)
	{
		throw MoreThanTwoKings();
	}
	++compteur;
	//castling = false;
	type_ = king;
	hasMoved = false;
}

King::~King()
{
	--compteur;
}

//std::vector<Coordonnees> King::attaquesPossibles(std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
//{
//	std::vector<Coordonnees> attaques;
//
//	return attaques;
//}
//
//std::vector<Coordonnees> King::movementsPossibles(std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
//{
//	std::vector<Coordonnees> x;
//	return x;
//}

bool King::estMovementValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
{
	//si mov valide, verifier si echec
	if ((abs(destination.x - position_.x) <= 1) && (abs(destination.y - position_.y) <= 1))
	{
		//if (!hasMoved) { hasMoved = true; }
		return true;
	}
	return false;
}
bool King::estAttaqueValide(Coordonnees destination, std::map<Coordonnees, std::shared_ptr<ChessPiece>> tiles)
{
	// Castling
	if (!hasMoved) 
	{
		if (tiles[destination]->getSide() == side_ && tiles[destination]->getType() == rook)
		{
			if (tiles[destination]->getHasMoved() == false)
			{
				//////////
				Coordonnees diff(destination.x - position_.x, destination.y - position_.y);
				if (diff.y == 0)
				{
					int i = 0;
					int j = 0;
					if (diff.x != 0)
					{
						i = diff.x / abs(diff.x) * -1;
					}
					//if (diff.y != 0)
					//{
					//	j = diff.y / abs(diff.y) * -1;
					//}
					Coordonnees coord(destination.x, destination.y);
					while (coord.x != position_.x || coord.y != position_.y)
					{
						if (tiles[coord] && tiles[coord] != tiles[destination])
						{
							return false;
						}
						coord.x += i;
						coord.y += j;
					}
					return true; // Appeler autre fonction??? ET retourner false ici???
				}
				return false;
				////////////
			}
		}
	}
	if (estMovementValide(destination, tiles) && tiles[destination]->getSide() != side_)
	{
		//if (!hasMoved) { hasMoved = true; }
		return true;
	}
	return false;
}

QString King::getImagePath() {
	QString path;
	if (side_ == white) {
		path = "50px/WhiteKing.png";
	}
	else
	{
		path = "50px/BlackKing.png";
	}
	return path;
}