#include "Bishop.hpp"

//Bishop::Bishop()
//{
//
//}

QString Bishop::getImagePath() {
	QString path;
	if (side_ == white) {
		path = "50px/WhiteBishop.png";
	}
	else
	{
		path = "50px/BlackBishop.png";
	}
	return path;
}