#include "Knight.hpp"

Knight::Knight()
{

}

QString Knight::getImagePath() {
	QString path;
	if (side_ == white) {
		path = "50px/WhiteKnight.png";
	}
	else
	{
		path = "50px/BlackKnight.png";
	}
	return path;
}