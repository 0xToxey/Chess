#pragma once
#include "constants.hpp"
#include <string>

class Piece
{
public:
	// C'TOR
	Piece(const PieceType& type, const std::string& currentPosition, const bool& white);

	// GETTERS
	PieceType getType() const;
	std::string getCurrentPosition() const;
	bool isWhite() const;

	// SETTRES
	void setCurrentPosition(const std::string& posToMoveFrom);

	virtual bool isCapableOfMoving(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& positionToMoveTo) = 0;

protected:
	virtual bool isMovingAcrossPieces(
		const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
		const unsigned int& rowToMoveFrom, const unsigned int& colToMoveFrom,
		const unsigned int& rowToMoveTo, const unsigned int& colToMoveTo) = 0;
	
	PieceType _type;
	std::string _currentPosition;
	bool _white;
};