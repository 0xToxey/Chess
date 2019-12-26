#pragma once

#include "constants.hpp"
#include "Player.hpp"
#include <iostream>

namespace Utils
{
	// conveting from array index to string and vice versa
	std::tuple<unsigned int, unsigned int> positionStringToIndex(const std::string& position);
	std::string positionIndexToString(const std::tuple <unsigned int, unsigned int>& positionInt);

	// getting type/color of a piece by position
	PieceColor getColorOfPieceByPosition(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& position);
	PieceType getTypeOfPieceByPosition(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& position);

	// getting the index of the player whose turn is
	unsigned int WhoseTurnIsIt(const Player(&players)[NUM_OF_PLAYERS]);
	
	// inserting a piece into a board array
	void insertPieceIntoBoard(char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const char& piece, const std::string& position);
}