#pragma once
#include <tuple>
#define NUM_OF_PLAYERS 2
#define NUM_OF_TILES 8

#define ASCII_LETTER_CONVERT 96
#define ASCII_NUMBER_CONVERT 48
#define EMPTY_TILE '#'


enum class PieceColor
{
	black,
	white,
	empty
};


Piece* getPieceByPosition(const Player(&players)[NUM_OF_PLAYERS], const std::string& position);
std::tuple<int, int> positionStringToInt(const std::string& position);
PieceColor getColorOfPieceByPosition(const char(&board)[NUM_OF_TILES][NUM_OF_TILES], const std::string& position);
