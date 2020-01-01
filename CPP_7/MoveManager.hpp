#pragma once
#include "Player.hpp"
#include "Pieces.hpp"
#include "ChessBoard.hpp"
#include <string>

class MoveManager
{
public:
	// calls all necessary functions to check if a move is valid
	MoveCode checkMove(
		ChessBoard& board,
		Player(&players)[NUM_OF_PLAYERS],
		const std::string& posToMoveFrom,
		const std::string& posToMoveTo) const;

	// doing a move without changing the turn
	void makeMove(
		ChessBoard& board,
		const std::string& posToMoveFrom,
		const std::string& posToMoveTo) const;

	// doing a move and changing turn
	void makeMove(
		Player(&players)[NUM_OF_PLAYERS],
		ChessBoard& board,
		const std::string& posToMoveFrom,
		const std::string& posToMoveTo) const;

	bool isCheckOrMate(
		ChessBoard& board,
		const std::string& posToMoveFrom,
		const std::string& posToMoveTo);


private:

	ChessPieces::Rook _rook;
	ChessPieces::King _king;
	ChessPieces::Knight _knight;
	ChessPieces::Bishop _bishop;
	ChessPieces::Queen _queen;
	ChessPieces::Pawn _pawn;

	// checking if player is trying to move other player pieces
	bool isMovingOtherPlayerPieces(
		const ChessBoard& board,
		const std::string& posToMoveFrom,
		const bool& isWhite) const;
	
	// checking if player is eating is own pieces
	bool isEatingSelf(
		const ChessBoard& board,
		const std::string& posToMoveFrom,
		const std::string& posToMoveTo) const;
	
	// checking if a piece can move to a destination
	bool isCapableMove(
		const ChessBoard& board,
		const std::string& posToMoveFrom,
		const std::string& posToMoveTo) const;
	
	// checking if isnt moving
	bool isntMoving(const std::string& posToMoveFrom, const std::string& posToMoveTo) const;
	
	// checking if player is doing a self check
	bool isSelfCheck(
		ChessBoard& board,
		const std::string& posToMoveFrom,
		const std::string& posToMoveTo,
		std::string& currPlayerKingPos,
		const bool& isWhite) const;

	// checking if made chess in a move
	bool didMakeCheck(
		ChessBoard& board,
		const std::string& posToMoveFrom,
		const std::string& posToMoveTo,
		std::string otherPlayerKingPos,
		const bool& isWhite) const;

	// checking if made checkmate in a move
	bool didMakeCheckmate(
		ChessBoard& board,
		const std::string& posToMoveFrom,
		const std::string& posToMoveTo,
		std::string& kingPosition,
		const bool& isWhite) const;
};
