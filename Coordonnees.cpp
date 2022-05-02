#include "Coordonnees.hpp"

Coordonnees::Coordonnees() : x(0), y(0) {};

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

Coordonnees& Coordonnees::operator-(const Coordonnees& other)
{
	x = x - other.x;
	y = y - other.y;
	return *this;
};

Coordonnees& Coordonnees::operator=(const Coordonnees& other)
{
	if (this == &other)
		return *this;
	x = other.x;
	y = other.y;
	return *this;
};

// On doit avoir ce overload d'opérateur sinon ne marche pas avec un std::map
bool Coordonnees::operator<(const Coordonnees& coord) const {
	if (x < coord.x) return true;
	if (x > coord.x) return false;
	if (y < coord.y) return true;
	if (y > coord.y) return false;
	return false;
}