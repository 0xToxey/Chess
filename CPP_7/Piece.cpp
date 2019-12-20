#include "Piece.hpp"
#include <string>

Piece::Piece(const PieceType& type, const std::string& currentPosition) :
	_type(type),
	_currentPosition(currentPosition)
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
