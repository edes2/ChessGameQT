#pragma once
#include <exception>

struct MoreThanTwoKings : public std::exception {
	const char* what() const throw () {
		return "Cannot instantiate more than two kings";
	}
};

enum type {
	rook,
	bishop,
	king,
	knight,
	queen,
	pawn
};

enum side {
	white,
	black
};