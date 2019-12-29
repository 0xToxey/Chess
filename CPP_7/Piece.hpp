#pragma once
#include "constants.hpp"
#include "ChessBoard.hpp"
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
		const ChessBoard& board,
		const std::string& posToMoveFrom,
		const std::string& posToMoveTo) const = 0;

protected:
	// function checks if the piece is moving across pieces to a destination
	virtual bool isMovingAcrossPieces(
		const ChessBoard& board,
		const unsigned int& rowToMoveFrom, const unsigned int& colToMoveFrom,
		const unsigned int& rowToMoveTo, const unsigned int& colToMoveTo) const = 0;

	PieceType _type;
};