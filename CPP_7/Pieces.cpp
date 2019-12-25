#include "Pieces.hpp"
#include "Utils.hpp"
#include <tuple>

ChessPieces::Rook::Rook(const PieceType& type, const std::string& currentPosition, const bool& white) :
	Piece(type, currentPosition, white)
{
}

bool ChessPieces::Rook::isCapableOfMoving(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& positionToMoveTo)
{
	unsigned int rowToMoveFrom, colToMoveFrom, rowToMoveTo, colToMoveTo;

	std::tie(rowToMoveFrom, colToMoveFrom) = positionStringToInt(this->getCurrentPosition());
	std::tie(rowToMoveTo, colToMoveTo) = positionStringToInt(positionToMoveTo);

	// checking if player is trying to move into a different column or different row
	if (rowToMoveFrom != rowToMoveTo && colToMoveFrom != colToMoveTo)
	{
		return false;
	}
	// checking if player is trying to move across other pieces
	if (isMovingAcrossPieces(board, rowToMoveFrom, colToMoveFrom, rowToMoveTo, colToMoveTo))
	{
		return false;
	}
	
	return true;
}

bool ChessPieces::Rook::isMovingAcrossPieces(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const unsigned int& rowToMoveFrom, const unsigned int& columnToMoveFrom, const unsigned int& rowToMoveTo, const unsigned int& columnToMoveTo)
{
	if (rowToMoveFrom == rowToMoveTo)
	{
		const unsigned int distance = std::abs((int)(columnToMoveFrom - columnToMoveTo));
		const unsigned int startingColumn = ((columnToMoveFrom < columnToMoveTo) ? columnToMoveFrom : columnToMoveTo) + 1;
		const unsigned int endingColumn = ((columnToMoveFrom > columnToMoveTo) ? columnToMoveFrom : columnToMoveTo);

		for (unsigned int i = startingColumn; i < endingColumn; i++)
		{
			if (board[rowToMoveFrom][i] != EMPTY_TILE)
			{
				return true;
			}
		}
	}
	else if (columnToMoveFrom == columnToMoveTo)
	{
		const unsigned int distance = std::abs((int)(rowToMoveFrom - rowToMoveTo));
		const unsigned int startingRow = ((rowToMoveFrom < rowToMoveTo) ? rowToMoveFrom : rowToMoveTo) + 1;
		const unsigned int endingRow = ((rowToMoveFrom > rowToMoveTo) ? rowToMoveFrom : rowToMoveTo);

		for (unsigned int i = startingRow; i < endingRow; i++)
		{
			if (board[i][columnToMoveFrom] != EMPTY_TILE)
			{
				return true;
			}
		}
	}

	return false;
}

ChessPieces::King::King(const PieceType& type, const std::string& currentPosition, const bool& white) :
	Piece(type, currentPosition, white)
{
}

bool ChessPieces::King::isCapableOfMoving(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& positionToMoveTo)
{
	// Move variables
	unsigned int rowToMoveFrom, colToMoveFrom, rowToMoveTo, colToMoveTo;

	std::tie(rowToMoveFrom, colToMoveFrom) = positionStringToInt(this->_currentPosition);
	std::tie(rowToMoveTo, colToMoveTo) = positionStringToInt(positionToMoveTo);\
	
	// King can move only 1 tile.
	const unsigned int colDistance = std::abs((int)(colToMoveFrom - colToMoveTo));
	const unsigned int rowDistance = std::abs((int)(rowToMoveFrom - rowToMoveTo));

	if (colDistance != 1 && rowDistance != 1)
	{
		return false;
	}

	return true;
}

bool ChessPieces::King::isMovingAcrossPieces(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const unsigned int& rowToMoveFrom, const unsigned int& columnToMoveFrom, const unsigned int& rowToMoveTo, const unsigned int& columnToMoveTo)
{
	return false;
}
