#include "Pieces.hpp"
#include "Utils.hpp"

ChessPieces::Rook::Rook(const PieceType& type, const std::string& currentPosition, const bool& white) :
	Piece(type, currentPosition, white)
{
};

bool ChessPieces::Rook::checkIfCapableMove(const std::string& positionToMoveTo)
{
	unsigned int rowToMoveFrom, columnToMoveFrom, rowToMoveTo, columnToMoveTo;

	std::tie(rowToMoveFrom, columnToMoveFrom) = positionStringToInt(this->getCurrentPosition());
	std::tie(rowToMoveTo, columnToMoveTo) = positionStringToInt(positionToMoveTo);

	// checking if player is trying to move into a different column or different row
	if (rowToMoveFrom != rowToMoveTo && columnToMoveFrom != columnToMoveTo)
	{
		return false;
	}
	return true;
}
