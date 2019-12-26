#pragma once
#include "constants.hpp"
#include <string>

class Piece
{
public:
	// C'TOR
	Piece(const PieceType& type);

	// GETTERS
	PieceType getType() const;

	// function checks if the piece can move to a destination
	virtual bool isCapableOfMoving(
		const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
		const std::string& posToMoveFrom,
		const std::string& posToMoveTo) = 0;

protected:
	// function checks if the piece is moving across pieces to a destination
	virtual bool isMovingAcrossPieces(
		const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
		const unsigned int& rowToMoveFrom, const unsigned int& colToMoveFrom,
		const unsigned int& rowToMoveTo, const unsigned int& colToMoveTo) = 0;

	PieceType _type;
};