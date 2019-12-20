#pragma once
#define BOARD_PLACES
#include <string>

enum class PieceType{
	king,
	queen,
	pawn,
	rook,
	knight,
	bishop,
};

class Piece
{
public:
	Piece(const PieceType& type, const std::string& currentPosition);  // C'TOR

	// GETTERS
	PieceType getType() const;
	std::string getCurrentPosition() const;

	virtual void move(const std::string& placeToMove) = 0;

protected:
	PieceType _type;
	std::string _currentPosition;
};