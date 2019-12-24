#pragma once
#include "Piece.hpp"

namespace ChessPieces
{
	class Rook : public Piece
	{
	public:
		Rook(const PieceType& type, const std::string& currentPosition, const bool& white);
		virtual bool checkIfCapableMove(const char(&board)[NUM_OF_TILES][NUM_OF_TILES], const std::string& positionToMoveTo);
	protected:
		virtual bool isMovingAcrossPieces(const char(&board)[NUM_OF_TILES][NUM_OF_TILES], const unsigned int& rowToMoveFrom, const unsigned int& columnToMoveFrom, const unsigned int& rowToMoveTo, const unsigned int& columnToMoveTo);

	};

}