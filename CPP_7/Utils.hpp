#pragma once

#include "constants.hpp"
#include "Player.hpp"
#include <iostream>

enum class PieceColor
{
	black,
	white,
	empty
};

std::tuple<int, int> positionStringToInt(const std::string& position);
PieceColor getColorOfPieceByPosition(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& position);
unsigned int checkPlayerTurn(const Player(&players)[NUM_OF_PLAYERS]);
PieceType getTypeOfPieceByPostion(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& position);
