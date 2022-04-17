#include "Rook.hpp"

Rook::Rook()
{

}

QString Rook::getImagePath() {
	QString path;
	if (side_ == white) {
		path = "50px/WhiteRook.png";
	}
	else
	{
		path = "50px/BlackRook.png";
	}
	return path;
}