#include "Pawn.hpp"

Pawn::Pawn()
{

}

QString Pawn::getImagePath() {
	QString path;
	if (side_ == white) {
		path = "50px/WhitePawn.png";
	}
	else
	{
		path = "50px/BlackPawn.png";
	}
	return path;
}