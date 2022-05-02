#pragma once
#include <exception>

struct MoreThanTwoKings : public std::exception {
	const char* what() const throw () {
		return "Cannot instantiate more than two kings";
	}
};

enum side {
	white,
	black
};