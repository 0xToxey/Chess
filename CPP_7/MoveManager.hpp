#pragma once
#include "Player.hpp"
#include "Pieces.hpp"
#include <string>

class MoveManager
{
public:
	MoveManager();

	// calls all necessary functions to check if a move is valid
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
	ChessPieces::Knight _knight;
	ChessPieces::Bishop _bishop;
	ChessPieces::Queen _queen;
	ChessPieces::Pawn _pawn;

	// checking if player is trying to move his own pieces
	bool isMovingOtherPlayerPieces(
		const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
		const std::string& posToMoveFrom,
		const bool& isWhite);
	
	// checking if player is eating is own pieces
	bool isEatingSelf(
		const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
		const std::string& posToMoveFrom,
		const std::string& posToMoveTo);
	
	// checking if a piece can move to a destination
	bool isCapableMove(
		const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
		const std::string& posToMoveFrom,
		const std::string& posToMoveTo);
	
	// checking if isnt moving
	bool isntMoving(const std::string& posToMoveFrom, const std::string& posToMoveTo);
	
	// checking if player is doing a self check
	bool isSelfCheck(
		char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
		const std::string& posToMoveFrom,
		const std::string& posToMoveTo,
		std::string& currPlayerKingPos,
		const bool& isWhite);

	// checking if made chess in a move
	bool didMakeCheck(
		char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
		const std::string& posToMoveFrom,
		const std::string& posToMoveTo,
		std::string otherPlayerKingPos,
		const bool& isWhite);

	// checking if made checkmate in a move
	bool didMakeCheckmate(
		char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
		const std::string& posToMoveFrom,
		const std::string& posToMoveTo,
		std::string& kingPosition,
		const bool& isWhite);
};
