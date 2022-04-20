#pragma once

#include "ChessPiece.hpp"

void ChessPiece::setSide(side side) {
	side_ = side;
}

side ChessPiece::getSide() {
	return side_;
}