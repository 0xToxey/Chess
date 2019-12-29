#pragma once

#include "constants.hpp"
#include "Player.hpp"
#include "ChessBoard.hpp"
#include <iostream>

namespace Utils
{
	// conveting from array index to string and vice versa
	std::tuple<unsigned int, unsigned int> positionStringToIndex(const std::string& position);
	std::string positionIndexToString(const std::tuple <const unsigned int, const unsigned int>& positionInt);
	
	// getting the index of the player whose turn is
	unsigned int WhoseTurnIsIt(const Player(&players)[NUM_OF_PLAYERS]);

}