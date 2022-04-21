#include "Coordonnees.hpp"

Coordonnees::Coordonnees(int x, int y) : x(x), y(y) {};

bool Coordonnees::operator==(const Coordonnees& other)
{
	if (other.x == x && other.y == y)
	{
		return true;
	}
	else {
		return false;
	}
}

Coordonnees& Coordonnees::operator=(const Coordonnees& other)
{
	if (this == &other)
		return *this;
	x = other.x;
	y = other.y;
	return *this;
};