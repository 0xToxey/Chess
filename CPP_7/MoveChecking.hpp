#pragma once
#include "Player.hpp"
#include "Pieces.hpp"
#include <string>

class MoveChecker
{
public:
	MoveChecker();

	int checkMove(
		const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
		const Player(&players)[NUM_OF_PLAYERS],
		const std::string& positionToMoveFrom,
		const std::string& positionToMoveTo);

private:

	ChessPieces::Rook _rook;
	ChessPieces::King _king;

	int case2(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& positionToMoveFrom, const bool& isWhite);
	int case3(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& positionToMoveFrom, const std::string& positionToMoveTo);
	int case6(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& positionToMoveFrom, const std::string& positionToMoveTo);
	int case7(const std::string& positionToMoveFrom, const std::string& positionToMoveTo);

};
