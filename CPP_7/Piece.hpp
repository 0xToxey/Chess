#pragma once
#include "constants.hpp"
#include <string>

class Piece
{
public:
	Piece(const PieceType& type, const std::string& currentPosition, const bool& white);  // C'TOR

	// GETTERS
	PieceType getType() const;
	std::string getCurrentPosition() const;
	bool isWhite() const;

	virtual bool checkIfCapableMove(const char(&board)[NUM_OF_TILES][NUM_OF_TILES], const std::string& positionToMoveTo) = 0;
	void setCurrentPosition(const std::string& positionToMoveFrom);

protected:
	virtual bool isMovingAcrossPieces(const char(&board)[NUM_OF_TILES][NUM_OF_TILES], const unsigned int& rowToMoveFrom, const unsigned int& columnToMoveFrom, const unsigned int& rowToMoveTo, const unsigned int& columnToMoveTo) = 0;
	
	PieceType _type;
	std::string _currentPosition;
	bool _white;
};