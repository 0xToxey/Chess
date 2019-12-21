#include "Pieces.hpp"

ChessPieces::Rook::Rook(const PieceType& type, const std::string& currentPosition, const bool& white) :
	Piece(type, currentPosition, white)
{
};

void ChessPieces::Rook::checkIfCapableMove(const std::string& placeToMove)
{
}

ChessPieces::Empty::Empty(const PieceType& type, const std::string& currentPosition, const bool& white):
	Piece(type, currentPosition, white)
{
}

void ChessPieces::Empty::checkIfCapableMove(const std::string& placeToMove)
{
}
