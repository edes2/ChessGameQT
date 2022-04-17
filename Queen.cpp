#include "Queen.hpp"

Queen::Queen()
{

}

QString Queen::getImagePath() {
	QString path;
	if (side_ == white) {
		path = "50px/WhiteQueen.png";
	}
	else
	{
		path = "50px/BlackQueen.png";
	}
	return path;
}