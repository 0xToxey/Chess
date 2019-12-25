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
		Player(&players)[NUM_OF_PLAYERS],
		const std::string& posToMoveFrom,
		const std::string& posToMoveTo);

	// doing a move without changing the turn
	void makeMove(
		char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
		const std::string& posToMoveFrom,
		const std::string& posToMoveTo);

	// doing a move and changing turn
	void makeMove(
		Player(&players)[NUM_OF_PLAYERS],
		char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
		const std::string& posToMoveFrom,
		const std::string& posToMoveTo);


private:

	ChessPieces::Rook _rook;
	ChessPieces::King _king;

	bool isMovingOtherPlayerPieces(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& posToMoveFrom, const bool& isWhite);
	bool isEatingSelf(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& posToMoveFrom, const std::string& posToMoveTo);
	bool isntCapableMove(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& posToMoveFrom, const std::string& posToMoveTo);
	bool isntMoving(const std::string& posToMoveFrom, const std::string& posToMoveTo);
	bool didMakeCheck(char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& posToMoveFrom, const std::string& posToMoveTo, std::string& kingPosition, const bool& isWhite);
	bool didMakeCheckmate(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& posToMoveFrom, const std::string& posToMoveTo, const std::string& kingPosition, const bool& isWhite);
	bool isSelfCheck(char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& posToMoveFrom, const std::string& posToMoveTo, std::string& kingPosition, const bool& isWhite);


};
