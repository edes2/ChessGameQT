#pragma once

class Coordinates
{
public:
	Coordinates();
	Coordinates(int x, int y);

	bool operator==(const Coordinates& other) const;

	Coordinates& operator=(const Coordinates& other);

  //Coordinates& operator+(const Coordinates& other);
  Coordinates operator+(const Coordinates& other);
	Coordinates& operator-(const Coordinates& other);

	bool operator<(const Coordinates& coord) const;

	// Made public for ease of access
	int x; 
	int y;
};