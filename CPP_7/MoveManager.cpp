#include "MoveManager.hpp"
#include "constants.hpp"
#include "Utils.hpp"
#include <tuple>

MoveManager::MoveManager() :
	_rook(),
	_king()
{
};

MoveCode MoveManager::checkMove(
	char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
	Player(&players)[NUM_OF_PLAYERS],
	const std::string& posToMoveFrom,
	const std::string& posToMoveTo)
{
	const unsigned int currPlayerTurn = Utils::WhoseTurnIsIt(players);
	const bool isCurrPlayerWhite = players[currPlayerTurn].isWhite();
	std::string otherPlayerKingPos = players[(currPlayerTurn == 1) ? 0 : 1].getKingPosition();
	std::string currPlayerKingPos = players[currPlayerTurn].getKingPosition();

	// checking if the move is valid
	if (isMovingOtherPlayerPieces(board, posToMoveFrom, isCurrPlayerWhite))
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
	if (isCapableMove(board, posToMoveFrom, posToMoveTo) == false)
	{
		return MoveCode::NotCapableMove;
	}
	if (isSelfCheck(board, posToMoveFrom, posToMoveTo, currPlayerKingPos, isCurrPlayerWhite))
	{
		return MoveCode::SelfCheck;
	}

	// in case the move is valid checking for check
	if (didMakeCheck(board, posToMoveFrom, posToMoveTo, otherPlayerKingPos, isCurrPlayerWhite))
	{
		if (didMakeCheckmate(board, posToMoveFrom, posToMoveTo, otherPlayerKingPos, isCurrPlayerWhite))
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

void MoveManager::makeMove(
	char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
	const std::string& posToMoveFrom,
	const std::string& posToMoveTo)
{
	auto [rowToMoveFrom, colToMoveFrom] = Utils::positionStringToIndex(posToMoveFrom);
	auto [rowToMoveTo, colToMoveTo] = Utils::positionStringToIndex(posToMoveTo);

	board[rowToMoveTo][colToMoveTo] = board[rowToMoveFrom][colToMoveFrom];
	board[rowToMoveFrom][colToMoveFrom] = EMPTY_TILE;
}

void MoveManager::makeMove(
	Player(&players)[NUM_OF_PLAYERS],
	char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
	const std::string& posToMoveFrom,
	const std::string& posToMoveTo)
{
	makeMove(board, posToMoveFrom, posToMoveTo);

	// changing the players turn
	const unsigned int currPlayerTurn = Utils::WhoseTurnIsIt(players);
	players[currPlayerTurn].setTurn(false);
	players[(currPlayerTurn == 1) ? 0 : 1].setTurn(true);

	// if player moved king, moving king in the player setter
	if (posToMoveFrom == players[currPlayerTurn].getKingPosition())
	{
		players[currPlayerTurn].setKingPosition(posToMoveTo);
	}
}

bool MoveManager::isMovingOtherPlayerPieces(
	const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
	const std::string& posToMoveFrom,
	const bool& isWhite)
{
	// checking if the player is trying to move pieces that aren't his
	switch (Utils::getColorOfPieceByPosition(board, posToMoveFrom))
	{
	case PieceColor::white:
		return ((isWhite) ? false : true);
	case PieceColor::black:
		return ((isWhite) ? true : false);
	case PieceColor::empty:
		return true;
	}
}

bool MoveManager::isEatingSelf(
	const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
	const std::string& posToMoveFrom,
	const std::string& posToMoveTo)
{
	// checking if player is trying to take over his own pieces
	if (Utils::getColorOfPieceByPosition(board, posToMoveFrom) == Utils::getColorOfPieceByPosition(board, posToMoveTo))
	{
		return true;
	}
	return false;
}

bool MoveManager::isCapableMove(
	const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
	const std::string& posToMoveFrom,
	const std::string& posToMoveTo)
{
	const PieceType currentPieceType = Utils::getTypeOfPieceByPosition(board, posToMoveFrom);
	bool capableOfMoving = true;

	// checking if the pieces can actually move that way
	switch (currentPieceType)
	{
	case PieceType::king:
		capableOfMoving = this->_king.isCapableOfMoving(board, posToMoveFrom, posToMoveTo);
		break;

	case PieceType::queen:
		break;

	case PieceType::pawn:
		break;

	case PieceType::rook:
		capableOfMoving = this->_rook.isCapableOfMoving(board, posToMoveFrom, posToMoveTo);
		break;

	case PieceType::knight:
		break;

	case PieceType::bishop:
		break;
	}

	return capableOfMoving;
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

bool MoveManager::isSelfCheck(
	char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
	const std::string& posToMoveFrom,
	const std::string& posToMoveTo,
	std::string& currPlayerkingPos,
	const bool& isWhite)
{
	// checking if black player can check
	return didMakeCheck(board, posToMoveFrom, posToMoveTo, currPlayerkingPos, !isWhite);
}

bool MoveManager::didMakeCheck(
	char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
	const std::string& posToMoveFrom,
	const std::string& posToMoveTo,
	std::string otherPlayerKingPos, // not a reference cause maybe changing it
	const bool& isWhite)
{

	const PieceColor currentPlayerColor = (isWhite) ? PieceColor::white : PieceColor::black;
	// saving a piece in case eating one when faking a move
	auto [pieceToSaveRow, pieceToSaveCol] = Utils::positionStringToIndex(posToMoveTo);
	const char pieceToSave = board[pieceToSaveRow][pieceToSaveCol];
	bool isCheck = false;

	// in case trying to protect the king by moving it
	if (otherPlayerKingPos == posToMoveFrom)
	{
		otherPlayerKingPos = posToMoveTo;
	}

	// faking a move
	makeMove(board, posToMoveFrom, posToMoveTo);

	// going over the board
	for (unsigned int i = 0; i < TILES_PER_SIDE && !isCheck; i++)
	{
		for (unsigned int j = 0; j < TILES_PER_SIDE && !isCheck; j++)
		{
			if (board[i][j] == EMPTY_TILE)
			{
				continue; // move to next piece
			}

			std::string currPiecePosition = Utils::positionIndexToString(std::make_tuple(i, j));

			// if any piece of current player will cause a check
			if (Utils::getColorOfPieceByPosition(board, currPiecePosition) == currentPlayerColor)
			{
				if (isCapableMove(board, currPiecePosition, otherPlayerKingPos)) // checking if can eat the king
				{
					isCheck = true;
					break;
				}
			}
		}
	}

	// reverting the move
	makeMove(board, posToMoveTo, posToMoveFrom);
	Utils::insertPieceIntoBoard(board, pieceToSave, posToMoveTo);
	return isCheck;
}

bool MoveManager::didMakeCheckmate(
	char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
	const std::string& posToMoveFrom,
	const std::string& posToMoveTo,
	std::string& currPlayerKingPos,
	const bool& isWhite)
{
	bool isCheckmate = true;
	const PieceColor otherPlayerColor = (isWhite) ? PieceColor::black : PieceColor::white;

	// saving a piece in case eating one when faking a move
	auto [pieceToSaveRow, pieceToSaveCol] = Utils::positionStringToIndex(posToMoveTo);
	const char pieceToSave = board[pieceToSaveRow][pieceToSaveCol];
	// faking a move
	makeMove(board, posToMoveFrom, posToMoveTo);

	// going over all the pieces in the board
	for (unsigned int i = 0; i < TILES_PER_SIDE && isCheckmate; i++)
	{
		for (unsigned int j = 0; j < TILES_PER_SIDE && isCheckmate; j++)
		{
			// if isn't a piece
			if (board[i][j] == EMPTY_TILE)
			{
				continue; // move to next piece
			}

			std::string piecePosition = Utils::positionIndexToString(std::make_tuple(i, j));
			
			// if any piece of current player may save the king
			if (Utils::getColorOfPieceByPosition(board, piecePosition) == otherPlayerColor)
			{
				// going over every place in the board to check if can save the king
				for (unsigned int k = 0; k < TILES_PER_SIDE && isCheckmate; k++)
				{
					for (unsigned int l = 0; l < TILES_PER_SIDE && isCheckmate; l++)
					{
						std::string positionToTest = Utils::positionIndexToString(std::make_tuple(k, l));
						
						if (isCapableMove(board, piecePosition, positionToTest))
						{
							// checking if the king won't be in check after moving
							if (didMakeCheck(board, piecePosition, positionToTest, currPlayerKingPos, isWhite) == false)
							{
								isCheckmate = false;
							}
						}
					}
				}
			}
		}
	}
	// reverting the move
	makeMove(board, posToMoveTo, posToMoveFrom);
	Utils::insertPieceIntoBoard(board, pieceToSave, posToMoveTo);
	return isCheckmate;
}

