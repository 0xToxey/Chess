#include "Pieces.hpp"
#include "Utils.hpp"
#include <tuple>

ChessPieces::Rook::Rook() :
	Piece(PieceType::rook)
{
}

bool ChessPieces::Rook::isCapableOfMoving(
	const ChessBoard& board,
	const std::string& posToMoveFrom,
	const std::string& posToMoveTo) const
{
	const auto [rowToMoveFrom, colToMoveFrom] = Utils::positionStringToIndex(posToMoveFrom);
	const auto [rowToMoveTo, colToMoveTo]     = Utils::positionStringToIndex(posToMoveTo);

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
	const ChessBoard& board,
	const unsigned int& rowToMoveFrom, const unsigned int& colToMoveFrom,
	const unsigned int& rowToMoveTo, const unsigned int& colToMoveTo) const
{
	if (rowToMoveFrom == rowToMoveTo)
	{
		// checking for lower and higher part of the move in the board
		const unsigned int startingColumn = ((colToMoveFrom < colToMoveTo) ? colToMoveFrom : colToMoveTo) + 1;
		const unsigned int endingColumn = ((colToMoveFrom > colToMoveTo) ? colToMoveFrom : colToMoveTo);

		for (unsigned int i = startingColumn; i < endingColumn; i++)
		{ 
			if (board.getPieceByIndex(rowToMoveFrom, i) != EMPTY_TILE)  // if there is a piece in the way
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
			if (board.getPieceByIndex(i, colToMoveFrom) != EMPTY_TILE) // if there is a piece in the way
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
	const ChessBoard& board,
	const std::string& posToMoveFrom,
	const std::string& posToMoveTo) const
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
	const ChessBoard& board,
	const unsigned int& rowToMoveFrom, const unsigned int& colToMoveFrom,
	const unsigned int& rowToMoveTo, const unsigned int& colToMoveTo) const
{
	return false; // will never move across pieces
}

ChessPieces::Knight::Knight() :
	Piece(PieceType::knight)
{
}

bool ChessPieces::Knight::isCapableOfMoving(
	const ChessBoard& board,
	const std::string& posToMoveFrom,
	const std::string& posToMoveTo) const
{
	// Move variables
	const auto [rowToMoveFrom, colToMoveFrom] = Utils::positionStringToIndex(posToMoveFrom);
	const auto [rowToMoveTo, colToMoveTo]     = Utils::positionStringToIndex(posToMoveTo);

	const unsigned int colDistance = std::abs(static_cast<int>(colToMoveFrom - colToMoveTo));
	const unsigned int rowDistance = std::abs(static_cast<int>(rowToMoveFrom - rowToMoveTo));

	if ((colDistance != 1 || rowDistance != 2) &&
		(colDistance != 2 || rowDistance != 1))
	{
		return false;
	}

	return true;
}

bool ChessPieces::Knight::isMovingAcrossPieces(
	const ChessBoard& board,
	const unsigned int& rowToMoveFrom, const unsigned int& colToMoveFrom,
	const unsigned int& rowToMoveTo, const unsigned int& colToMoveTo) const
{
	return false; // knight is allowed to move across other pieces
}

ChessPieces::Bishop::Bishop() :
	Piece(PieceType::bishop)
{
}

bool ChessPieces::Bishop::isCapableOfMoving(
	const ChessBoard& board,
	const std::string& posToMoveFrom,
	const std::string& posToMoveTo) const
{
	// Move variables
	const auto [rowToMoveFrom, colToMoveFrom] = Utils::positionStringToIndex(posToMoveFrom);
	const auto [rowToMoveTo, colToMoveTo]     = Utils::positionStringToIndex(posToMoveTo);

	const unsigned int colDistance = std::abs(static_cast<int>(colToMoveFrom - colToMoveTo));
	const unsigned int rowDistance = std::abs(static_cast<int>(rowToMoveFrom - rowToMoveTo));

	// The row and column in bishop movment need's to be equal
	if (colDistance != rowDistance)
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

bool ChessPieces::Bishop::isMovingAcrossPieces(
	const ChessBoard& board,
	const unsigned int& rowToMoveFrom, const unsigned int& colToMoveFrom,
	const unsigned int& rowToMoveTo, const unsigned int& colToMoveTo) const
{
	// checking for lower and higher part of the move in the board
	const unsigned int startingRow = ((rowToMoveFrom < rowToMoveTo) ? rowToMoveFrom : rowToMoveTo) + 1;
	const unsigned int endingRow   = ((rowToMoveFrom > rowToMoveTo) ? rowToMoveFrom : rowToMoveTo);	

	// if moving up , starting from current col, if moving down starting from dest col
	unsigned int startingCol = ((rowToMoveFrom > rowToMoveTo) ? colToMoveTo: colToMoveFrom);

	// THE CHECK WORKS FROM DOWN TO UP
	for (unsigned int i = startingRow, j = startingCol; i < endingRow; i++)
	{
		if (rowToMoveFrom < rowToMoveTo)
		{
			// if moving up
			// when moving left  - moving a tile left(col left)
			// when moving right - moving a tile right(col right)
			(colToMoveFrom > colToMoveTo) ? j-- : j++;
		}
		else
		{
			// if moving down
			// when moving left  - moving a tile right(col right)
			// when moving right - moving a tile left(col left)
			(colToMoveFrom > colToMoveTo) ? j++ : j--;
		}

		if (board.getPieceByIndex(i,j) != EMPTY_TILE)  // if there is a piece in the way
		{
			return true;
		}
	}
	
	return false;
}

ChessPieces::Queen::Queen() :
	Piece(PieceType::queen)
{
}

bool ChessPieces::Queen::isCapableOfMoving(const ChessBoard& board,
	const std::string& posToMoveFrom,
	const std::string& posToMoveTo) const
{

	bool diagonalMove = this->_bishop.isCapableOfMoving(board, posToMoveFrom, posToMoveTo);
	bool straightMove = this->_rook.isCapableOfMoving(board, posToMoveFrom, posToMoveTo);

	// if the diagonal move or the straight move is possible it means that the queen can move.
	if (!(diagonalMove || straightMove))
	{
		return false;
	}

	return true;
}

bool ChessPieces::Queen::isMovingAcrossPieces(const ChessBoard& board,
	const unsigned int& rowToMoveFrom, const unsigned int& colToMoveFrom,
	const unsigned int& rowToMoveTo, const unsigned int& colToMoveTo) const
{
	return false;
}

ChessPieces::Pawn::Pawn() :
	Piece(PieceType::pawn)
{
}

bool ChessPieces::Pawn::isCapableOfMoving(
	const ChessBoard& board,
	const std::string& posToMoveFrom,
	const std::string& posToMoveTo) const
{
	PieceColor pawnColor =board.getColorOfPieceByPosition(posToMoveFrom);

	// Move variables
	const auto [rowToMoveFrom, colToMoveFrom] = Utils::positionStringToIndex(posToMoveFrom);
	const auto [rowToMoveTo, colToMoveTo]     = Utils::positionStringToIndex(posToMoveTo);

	const unsigned int colDistance = std::abs(static_cast<int>(colToMoveFrom - colToMoveTo));
	const unsigned int rowDistance = std::abs(static_cast<int>(rowToMoveFrom - rowToMoveTo));


	// checking if pawn is moving in the wrong way
	if ((pawnColor == PieceColor::white && rowToMoveFrom > rowToMoveTo) || // white should moving forward
		(pawnColor == PieceColor::black && rowToMoveFrom < rowToMoveTo))   // black should move backwards
	{
		return false;
	}


	// checking if pawn trying to eat, and if so should eat other player pieces
	if (colDistance == 1 && rowDistance == 1)
	{
		if ((board.getColorOfPieceByPosition(posToMoveTo) == PieceColor::empty))
		{
			return false;
		}
	}
	else // if pawn is trying to move regularly
	{
		// if the pawn is in the starting point , it can move 2 tiles
		if ((pawnColor == PieceColor::white && rowToMoveFrom == WHITE_PAWN_START_ROW) ||
			(pawnColor == PieceColor::black && rowToMoveFrom == BLACK_PAWN_START_ROW))
		{
			if (colDistance != 0 || rowDistance > 2)
			{
				return false;
			}
		}
		// checking if the pawn is trying to move to the sides or more than 1 tile
		else if (colDistance != 0 || rowDistance != 1)
		{
			return false;
		}
		// if pawn is trying to eat in a straight line
		if (board.getTypeOfPieceByPosition(posToMoveTo) != PieceType::empty)
		{
			return false;
		}
	}
	
	return true;
}

bool ChessPieces::Pawn::isMovingAcrossPieces(
	const ChessBoard& board,
	const unsigned int& rowToMoveFrom, const unsigned int& colToMoveFrom,
	const unsigned int& rowToMoveTo, const unsigned int& colToMoveTo) const
{
	return false;
}
