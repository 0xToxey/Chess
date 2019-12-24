#pragma once
#include "Piece.hpp"

namespace ChessPieces
{
	class Rook : public Piece
	{
	public:
		Rook(const PieceType& type, const std::string& currentPosition, const bool& white);
		virtual bool checkIfCapableMove(const std::string& positionToMoveTo);
	};

}