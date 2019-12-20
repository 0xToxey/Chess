#include "Pieces.hpp"

ChessPieces::Rook::Rook(const PieceType& type, const std::string& currentPosition) :
	Piece(type, currentPosition)
{
};

void ChessPieces::Rook::move(const std::string& placeToMove)
{
}
