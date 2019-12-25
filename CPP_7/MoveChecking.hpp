#pragma once
#include "Player.hpp"
#include "Pieces.hpp"
#include <string>

class MoveChecker
{
public:
	MoveChecker();

	MoveCode checkMove(
		const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
		const Player(&players)[NUM_OF_PLAYERS],
		const std::string& posToMoveFrom,
		const std::string& posToMoveTo);

private:

	ChessPieces::Rook _rook;
	ChessPieces::King _king;

	MoveCode isMovingOtherPlayerPieces(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& posToMoveFrom, const bool& isWhite);
	MoveCode IsEatingSelf(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& posToMoveFrom, const std::string& posToMoveTo);
	MoveCode isCapableMove(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& posToMoveFrom, const std::string& posToMoveTo);
	MoveCode isMoving(const std::string& posToMoveFrom, const std::string& posToMoveTo);

};
