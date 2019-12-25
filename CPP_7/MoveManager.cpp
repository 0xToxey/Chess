#include "MoveManager.hpp"
#include "constants.hpp"
#include "Utils.hpp"
#include <tuple>

MoveManager::MoveManager() :
	_rook(PieceType::rook, "00", false),
	_king(PieceType::king, "00", false)
{
};

MoveCode MoveManager::checkMove(
	char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
	Player(&players)[NUM_OF_PLAYERS],
	const std::string& posToMoveFrom,
	const std::string& posToMoveTo)
{
	const unsigned int playerTurn = checkPlayerTurn(players);
	const bool isWhite = players[playerTurn].isWhite();
	std::string otherPlayerKingPos = players[(playerTurn == 1) ? 0 : 1].getKingPosition();
	std::string currPlayerKingPos = players[playerTurn].getKingPosition();

	// checking if the move is valid
	if (isMovingOtherPlayerPieces(board, posToMoveFrom, players[playerTurn].isWhite()))
	{
		return MoveCode::NotPlayerPiece;
	}
	if (isEatingSelf(board, posToMoveFrom, posToMoveTo))
	{
		return MoveCode::EatingSelf;
	}
	if (isntMoving(posToMoveFrom, posToMoveTo))
	{
		return MoveCode::NotMoving;
	}
	if (isntCapableMove(board, posToMoveFrom, posToMoveTo))
	{
		return MoveCode::NotCapableMove;
	}

	if (isSelfCheck(board, posToMoveFrom, posToMoveTo, currPlayerKingPos, isWhite))
	{
		return MoveCode::SelfCheck;
	}

	// in case the move is valid checking for check
	if (didMakeCheck(board, posToMoveFrom, posToMoveTo, otherPlayerKingPos, isWhite))
	{
		if (didMakeCheckmate(board, posToMoveFrom, posToMoveTo, otherPlayerKingPos, isWhite))
		{
			return MoveCode::CheckMate;
		}
		else
		{
			return MoveCode::MadeCheck;
		}
	}
	return MoveCode::ValidMove;
}

void MoveManager::makeMove(char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& posToMoveFrom, const std::string& posToMoveTo)
{
	unsigned int rowToMoveFrom, colToMoveFrom, rowToMoveTo, colToMoveTo;
	std::tie(rowToMoveTo, colToMoveTo) = positionStringToInt(posToMoveTo);
	std::tie(rowToMoveFrom, colToMoveFrom) = positionStringToInt(posToMoveFrom);

	board[rowToMoveTo][colToMoveTo] = board[rowToMoveFrom][colToMoveFrom];
	board[rowToMoveFrom][colToMoveFrom] = EMPTY_TILE;
}

bool MoveManager::isMovingOtherPlayerPieces(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& posToMoveFrom, const bool& isWhite)
{
	// checking if the player is trying to move pieces that aren't his
	switch (getColorOfPieceByPosition(board, posToMoveFrom))
	{
	case PieceColor::white:
		return ((isWhite) ? false : true);
	case PieceColor::black:
		return ((isWhite) ? true : false);
	case PieceColor::empty:
		return true;
	}
}

bool MoveManager::isEatingSelf(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& posToMoveFrom, const std::string& posToMoveTo)
{
	// checking if player is trying to take over his own pieces
	if (getColorOfPieceByPosition(board, posToMoveFrom) == getColorOfPieceByPosition(board, posToMoveTo))
	{
		return true;
	}
	return false;
}

bool MoveManager::isntCapableMove(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& posToMoveFrom, const std::string& posToMoveTo)
{
	const PieceType currentPieceType = getTypeOfPieceByPosition(board, posToMoveFrom);
	bool capableOfMoving = true;

	// checking if the pieces can actually move that way
	switch (currentPieceType)
	{
	case PieceType::king:
		this->_king.setCurrentPosition(posToMoveFrom);
		capableOfMoving = this->_king.isCapableOfMoving(board, posToMoveTo);
		break;

	case PieceType::queen:
		break;

	case PieceType::pawn:
		break;

	case PieceType::rook:
		this->_rook.setCurrentPosition(posToMoveFrom);
		capableOfMoving = this->_rook.isCapableOfMoving(board, posToMoveTo);
		break;

	case PieceType::knight:
		break;

	case PieceType::bishop:
		break;
	}

	return (capableOfMoving == false) ? true : false;
}

bool MoveManager::isntMoving(const std::string& posToMoveFrom, const std::string& posToMoveTo)
{
	// checking if player trying to not move
	if (posToMoveFrom == posToMoveTo)
	{
		return true;
	}
	return false;
}

bool MoveManager::didMakeCheck(char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
	const std::string& posToMoveFrom, const std::string& posToMoveTo,
	std::string& kingPosition, const bool& isWhite)
{
	// in case trying to protect the king by moving it
	if (kingPosition == posToMoveFrom)
	{
		kingPosition = posToMoveTo;
	}

	unsigned int kingRow, kingCol;
	std::tie(kingRow, kingCol) = positionStringToInt(kingPosition);
	const PieceColor currentPlayerColor = (isWhite) ? PieceColor::white : PieceColor::black;

	// faking a move
	makeMove(board, posToMoveFrom, posToMoveTo);

	for (unsigned int i = 0; i < TILES_PER_SIDE; i++)
	{
		for (unsigned int j = 0; j < TILES_PER_SIDE; j++)
		{
			if (board[i][j] == EMPTY_TILE)
			{
				continue; // move to next piece
			}

			std::string piecePosition = positionIntToString(std::make_tuple(i, j));

			// if any piece of current player will cause a check
			if (getColorOfPieceByPosition(board, piecePosition) == currentPlayerColor)
			{
				if (isntCapableMove(board, piecePosition, kingPosition) == false)
				{
					// reverting the move
					makeMove(board, posToMoveTo, posToMoveFrom);
					return true;
				}
			}
		}
	}

	// reverting the move
	makeMove(board, posToMoveTo, posToMoveFrom);
	return false;
}

bool MoveManager::didMakeCheckmate(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
	const std::string& posToMoveFrom, const std::string& posToMoveTo,
	const std::string& kingPosition, const bool& isWhite)
{
	return false;
}

bool MoveManager::isSelfCheck(char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
	const std::string& posToMoveFrom, const std::string& posToMoveTo,
	std::string& kingPosition, const bool& isWhite)
{
	if (didMakeCheck(board, posToMoveFrom, posToMoveTo, kingPosition, !isWhite) == true)
	{
		return true;
	}

	return false;
}


