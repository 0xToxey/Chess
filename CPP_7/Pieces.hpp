#pragma once
#include "Piece.hpp"

namespace ChessPieces
{
	class Rook : public Piece
	{
	public:
		Rook(const PieceType& type, const std::string& currentPosition);
		virtual void move(const std::string& placeToMove);
	};
}