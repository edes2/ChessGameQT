#pragma once

class Coordonnees
{
public:
	Coordonnees();
	Coordonnees(int x, int y);

	bool operator==(const Coordonnees& other);

	Coordonnees& operator=(const Coordonnees& other);

	Coordonnees& operator-(const Coordonnees& other);

	bool operator<(const Coordonnees& coord) const;

	int x;
	int y;
};