#pragma once
#include <exception>

struct MoreThanTwoKings : public std::exception {
	const char* what() const throw () {
		return "Cannot instantiate more than two kings";
	}
};

namespace Modele {
	class ChessBoard;
	class ChessPiece;
};

namespace Vue {
	class ChessWindow;
};

enum side {
	white,
	black
};