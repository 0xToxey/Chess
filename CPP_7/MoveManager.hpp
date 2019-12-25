#pragma once
#include "Player.hpp"
#include "Pieces.hpp"
#include <string>

class MoveManager
{
public:
	MoveManager();

	MoveCode checkMove(
		char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
		const Player(&players)[NUM_OF_PLAYERS],
		const std::string& posToMoveFrom,
		const std::string& posToMoveTo);

	void makeMove(
		char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
		const std::string& posToMoveFrom,
		const std::string& posToMoveTo);


private:

	ChessPieces::Rook _rook;
	ChessPieces::King _king;

	MoveCode isMovingOtherPlayerPieces(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& posToMoveFrom, const bool& isWhite);
	MoveCode isEatingSelf(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& posToMoveFrom, const std::string& posToMoveTo);
	MoveCode isCapableMove(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& posToMoveFrom, const std::string& posToMoveTo);
	MoveCode isMoving(const std::string& posToMoveFrom, const std::string& posToMoveTo);
	MoveCode didMakeCheck(char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& posToMoveFrom, const std::string& posToMoveTo, const std::string& kingPosition, const bool& isWhite);
	MoveCode didMakeCheckmate(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& posToMoveFrom, const std::string& posToMoveTo, const std::string& kingPosition, const bool& isWhite);
	MoveCode isSelfCheck(char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& posToMoveFrom, const std::string& posToMoveTo, const std::string& kingPosition, const bool& isWhite);


};
