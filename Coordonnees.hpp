#pragma once

class Coordonnees
{
public:
	Coordonnees() = default;
	Coordonnees(int x, int y);

	bool operator==(const Coordonnees& other);

	Coordonnees& operator=(const Coordonnees& other);

    bool operator<(const Coordonnees& coord) const {
        if (x < coord.x) return true;
        if (x > coord.x) return false;
        if (y < coord.y) return true;
        if (y > coord.y) return false;
        return false;
    }

	int x;
	int y;
};