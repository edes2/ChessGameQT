#pragma once

class Coordonnees
{
public:
	Coordonnees();
	Coordonnees(int x, int y);

	bool operator==(const Coordonnees& other) const;

	Coordonnees& operator=(const Coordonnees& other);
	//bool operator==(const Coordonnees& other) const
	//{
	//	if (other.x == x && other.y == y)
	//	{
	//		return true;
	//	}
	//	else {
	//		return false;
	//	}
	//}
	Coordonnees& operator-(const Coordonnees& other);

	bool operator<(const Coordonnees& coord) const;

	int x;
	int y;
};