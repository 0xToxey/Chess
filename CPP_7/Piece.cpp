#include "Piece.hpp"

Piece::Piece(const PieceType& type) :
	_type(type)
{
};

PieceType Piece::getType() const
{
	return this->_type;
}