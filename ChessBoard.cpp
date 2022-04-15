#pragma once

#include "ChessBoard.hpp"
#include <iostream>
void ChessBoard::caseAppuye(std::pair<int, int> position)
{
	std::cout << "X: " << position.first << ", Y: " << position.second << std::endl;
}