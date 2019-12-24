#include "Piece.hpp"
#include <string>

Piece::Piece(const PieceType& type, const std::string& currentPosition, const bool& white) :
	_type(type),
	_currentPosition(currentPosition),
	_white(white)
{
};

PieceType Piece::getType() const
{
	return this->_type;
}

std::string Piece::getCurrentPosition() const
{
	return this->_currentPosition;
}

void Piece::setCurrentPosition(const std::string& positionToMoveFrom)
{
	this->_currentPosition = positionToMoveFrom;
}

bool Piece::isWhite() const
{
	return this->_white;
}
