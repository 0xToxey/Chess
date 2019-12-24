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
	empty
};

class Piece
{
public:
	Piece(const PieceType& type, const std::string& currentPosition, const bool& white);  // C'TOR

	// GETTERS
	PieceType getType() const;
	std::string getCurrentPosition() const;
	bool isWhite() const;

	virtual bool checkIfCapableMove(const std::string& positionToMoveTo) = 0;

	void setCurrentPosition(const std::string& positionToMoveFrom);

protected:
	PieceType _type;
	std::string _currentPosition;
	bool _white;
};