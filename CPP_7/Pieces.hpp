#pragma once
#include "Piece.hpp"

namespace ChessPieces
{
	class Rook : public Piece
	{
	public:
		// C'TOR
		Rook(const PieceType& type, const std::string& currentPosition, const bool& white);

		// Move
		virtual bool isCapableOfMoving(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& positionToMoveTo);
	
	protected:
		virtual bool isMovingAcrossPieces(
			const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
			const unsigned int& rowToMoveFrom, const unsigned int& columnToMoveFrom,
			const unsigned int& rowToMoveTo, const unsigned int& columnToMoveTo);

	};

	class King : public Piece
	{
	public:
		// C'TOR
		King(const PieceType& type, const std::string& currentPosition, const bool& white);

		// Move
		virtual bool isCapableOfMoving(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& positionToMoveTo);

	protected:
		// King always will be able to move without moving across other piece.
		virtual bool isMovingAcrossPieces(
			const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
			const unsigned int& rowToMoveFrom, const unsigned int& columnToMoveFrom,
			const unsigned int& rowToMoveTo, const unsigned int& columnToMoveTo);
	};

}