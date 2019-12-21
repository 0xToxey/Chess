#pragma once
#include "Piece.hpp"

namespace ChessPieces
{
	class Rook : public Piece
	{
	public:
		Rook(const PieceType& type, const std::string& currentPosition, const bool& white);
		virtual void checkIfCapableMove(const std::string& placeToMove);
	};

	class Empty : public Piece
	{
	public:
		Empty(const PieceType& type, const std::string& currentPosition, const bool& white);
		virtual void checkIfCapableMove(const std::string& placeToMove);
	};
}