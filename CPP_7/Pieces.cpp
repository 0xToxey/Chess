#include "Pieces.hpp"
#include "Utils.hpp"
#include <tuple>

ChessPieces::Rook::Rook() : 
	Piece(PieceType::rook)
{
}

bool ChessPieces::Rook::isCapableOfMoving(
	const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
	const std::string& posToMoveFrom,
	const std::string& posToMoveTo)
{
	const auto [rowToMoveFrom, colToMoveFrom] = Utils::positionStringToIndex(posToMoveFrom);
	const auto [rowToMoveTo, colToMoveTo] = Utils::positionStringToIndex(posToMoveTo);

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

bool ChessPieces::Rook::isMovingAcrossPieces(
	const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
	const unsigned int& rowToMoveFrom, const unsigned int& colToMoveFrom,
	const unsigned int& rowToMoveTo, const unsigned int& colToMoveTo)
{
	if (rowToMoveFrom == rowToMoveTo)
	{
		// checking for lower and higher part of the move in the board
		const unsigned int startingColumn = ((colToMoveFrom < colToMoveTo) ? colToMoveFrom : colToMoveTo) + 1;
		const unsigned int endingColumn = ((colToMoveFrom > colToMoveTo) ? colToMoveFrom : colToMoveTo);

		for (unsigned int i = startingColumn; i < endingColumn; i++)
		{
			if (board[rowToMoveFrom][i] != EMPTY_TILE)  // if there is a piece in the way
			{
				return true;
			}
		}
	}
	else if (colToMoveFrom == colToMoveTo)
	{
		// checking for lower and higher part of the move in the board
		const unsigned int startingRow = ((rowToMoveFrom < rowToMoveTo) ? rowToMoveFrom : rowToMoveTo) + 1;
		const unsigned int endingRow = ((rowToMoveFrom > rowToMoveTo) ? rowToMoveFrom : rowToMoveTo);

		for (unsigned int i = startingRow; i < endingRow; i++)
		{
			if (board[i][colToMoveFrom] != EMPTY_TILE) // if there is a piece in the way
			{
				return true;
			}
		}
	}

	return false;
}

ChessPieces::King::King() :
	Piece(PieceType::king)
{
}

bool ChessPieces::King::isCapableOfMoving(
	const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
	const std::string& posToMoveFrom,
	const std::string& posToMoveTo)
{
	// Move variables
	const auto [rowToMoveFrom, colToMoveFrom] = Utils::positionStringToIndex(posToMoveFrom);
	const auto [rowToMoveTo, colToMoveTo] = Utils::positionStringToIndex(posToMoveTo);
	
	// King can move only 1 tile.
	const unsigned int colDistance = std::abs(static_cast<int>(colToMoveFrom - colToMoveTo));
	const unsigned int rowDistance = std::abs(static_cast<int>(rowToMoveFrom - rowToMoveTo));

	if ((colDistance != 1 && colDistance != 0) ||
		(rowDistance != 1 && rowDistance != 0))
	{
		return false;
	}

	return true;
}

bool ChessPieces::King::isMovingAcrossPieces(
	const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
	const unsigned int& rowToMoveFrom, const unsigned int& colToMoveFrom,
	const unsigned int& rowToMoveTo, const unsigned int& colToMoveTo)
{
	return false; // will never move across pieces
}

ChessPieces::Knight::Knight() :
	Piece(PieceType::knight)
{
}

bool ChessPieces::Knight::isCapableOfMoving(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& posToMoveFrom, const std::string& posToMoveTo)
{
	// Move variables
	const auto [rowToMoveFrom, colToMoveFrom] = Utils::positionStringToIndex(posToMoveFrom);
	const auto [rowToMoveTo, colToMoveTo] = Utils::positionStringToIndex(posToMoveTo);
	
	const unsigned int colDistance = std::abs(static_cast<int>(colToMoveFrom - colToMoveTo));
	const unsigned int rowDistance = std::abs(static_cast<int>(rowToMoveFrom - rowToMoveTo));

	if ((colDistance != 1 && colDistance != 2) ||
		(rowDistance != 1 && rowDistance != 2))
	{
		return false;
	}
		 
	return true;

}

bool ChessPieces::Knight::isMovingAcrossPieces(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const unsigned int& rowToMoveFrom, const unsigned int& colToMoveFrom, const unsigned int& rowToMoveTo, const unsigned int& colToMoveTo)
{
	return false;
}
