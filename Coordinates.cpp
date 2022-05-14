#include "Coordinates.hpp"

Coordinates::Coordinates() : x(0), y(0) {};

Coordinates::Coordinates(int x, int y) : x(x), y(y) {};

bool Coordinates::operator==(const Coordinates& other) const
{
	if (other.x == x && other.y == y)
	{
		return true;
	}
	else {
		return false;
	}
}

//Coordinates& Coordinates::operator+(const Coordinates& other)
//{
//  x = x + other.x;
//  y = y + other.y;
//  return *this;
//}

Coordinates Coordinates::operator+(const Coordinates& other)
{
  Coordinates newObject;
  newObject.x = x + other.x;
  newObject.y = y + other.y;
  return newObject;
}

Coordinates& Coordinates::operator-(const Coordinates& other)
{
	x = x - other.x;
	y = y - other.y;
	return *this;
};

Coordinates& Coordinates::operator=(const Coordinates& other)
{
  if (this != &other)
  {
    x = other.x;
    y = other.y;
  }
  return *this;
};

// On doit avoir ce overload d'opérateur sinon ne marche pas avec un std::map
bool Coordinates::operator<(const Coordinates& coord) const {
	if (x < coord.x) return true;
	if (x > coord.x) return false;
	if (y < coord.y) return true;
	if (y > coord.y) return false;
	return false;
}