#pragma once
#include "constants.hpp"
#include <string>
#include <array>

class ChessBoard
{
public:
	ChessBoard(const char* arrayBoard);

	char& operator[] (const std::string& position);
	char operator[] (const std::string& position) const;

	// getting type/color/piece of a piece by position/index
	PieceColor getColorOfPieceByPosition(const std::string& position) const;
	PieceType getTypeOfPieceByPosition(const std::string& position) const;
	char getPieceByIndex(const unsigned int& row, const unsigned int& col) const;


private:
	char _board[TILES_PER_SIDE][TILES_PER_SIDE];
};