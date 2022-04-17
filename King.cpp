#include "King.hpp"

King::King()
{

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