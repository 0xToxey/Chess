#include "MoveManager.hpp"
#include "constants.hpp"
#include "Utils.hpp"
#include <tuple>

/*
function calls all necessary functions to check if a move is valid
output:
	move code
*/
MoveCode MoveManager::checkMove(
	ChessBoard& board,
	Player(&players)[NUM_OF_PLAYERS],
	const std::string& posToMoveFrom,
	const std::string& posToMoveTo) const
{
	const unsigned int currPlayerTurn = Utils::WhoseTurnIsIt(players);
	const bool isCurrPlayerWhite = players[currPlayerTurn].isWhite();
	std::string otherPlayerKingPos = players[(currPlayerTurn == 1) ? 0 : 1].getKingPosition();
	std::string currPlayerKingPos = players[currPlayerTurn].getKingPosition();
	MoveCode moveCode = MoveCode::ValidMove;

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
		moveCode = MoveCode::MadeCheck;

		if (didMakeCheckmate(board, posToMoveFrom, posToMoveTo, otherPlayerKingPos, isCurrPlayerWhite))
		{
			moveCode = MoveCode::CheckMate;
		}
	}

	return moveCode;
}

/*
function makes a move without changing the turn (fake move)
		** help to check if the move make checkmate.
*/
void MoveManager::makeMove(
	ChessBoard& board,
	const std::string& posToMoveFrom,
	const std::string& posToMoveTo) const
{
	const int rowToMoveFrom = posToMoveFrom[1] - '0' - 1; // converting from "1" to 0, "2" to 1
	const int rowToMoveTo =	  posToMoveTo[1]   - '0' - 1; // converting from "1" to 0, "2" to 1

	if (board.getTypeOfPieceByPosition(posToMoveFrom) == PieceType::pawn && // checking for promotion
		(rowToMoveTo == WHITE_START_ROW || rowToMoveTo == BLACK_START_ROW))
	{
		switch (rowToMoveTo)
		{
		case WHITE_START_ROW:
			board[posToMoveFrom] = 'q';
			break;
		case BLACK_START_ROW:
			board[posToMoveFrom] = 'Q';
			break;
		}
	}

	board[posToMoveTo] = board[posToMoveFrom];
	board[posToMoveFrom] = EMPTY_TILE;
}

/*
function makes a move and changes the turn
		** original move
*/
void MoveManager::makeMove(
	Player(&players)[NUM_OF_PLAYERS],
	ChessBoard& board,
	const std::string& posToMoveFrom,
	const std::string& posToMoveTo) const
{
	board[posToMoveTo] = board[posToMoveFrom];
	board[posToMoveFrom] = EMPTY_TILE;

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

/*
function checks if player is trying to move other player pieces or empty piece
*/
bool MoveManager::isMovingOtherPlayerPieces(
	const ChessBoard& board,
	const std::string& posToMoveFrom,
	const bool& isWhite) const
{
	// checking if the player is trying to move pieces that aren't his
	switch (board.getColorOfPieceByPosition(posToMoveFrom))
	{
	case PieceColor::white:
		return ((isWhite) ? false : true);

	case PieceColor::black:
		return ((isWhite) ? true : false);

	case PieceColor::empty:
		return true;
	}
}

/*
function checks if player is trying to eat is own piece
*/
bool MoveManager::isEatingSelf(
	const ChessBoard& board,
	const std::string& posToMoveFrom,
	const std::string& posToMoveTo) const
{
	// checking if player is trying to take over his own piece
	if (board.getColorOfPieceByPosition(posToMoveFrom) == board.getColorOfPieceByPosition(posToMoveTo))
	{
		return true;
	}
	return false;
}

/*
function checks if the move is valid
*/
bool MoveManager::isCapableMove(
	const ChessBoard& board,
	const std::string& posToMoveFrom,
	const std::string& posToMoveTo) const
{
	const PieceType currentPieceType = board.getTypeOfPieceByPosition(posToMoveFrom);
	bool capableOfMoving = true;

	// checking if the pieces can actually move that way
	switch (currentPieceType)
	{
	case PieceType::king:
		capableOfMoving = this->_king.isCapableOfMoving(board, posToMoveFrom, posToMoveTo);
		break;

	case PieceType::queen:
		capableOfMoving = this->_queen.isCapableOfMoving(board, posToMoveFrom, posToMoveTo);
		break;

	case PieceType::pawn:
		capableOfMoving = this->_pawn.isCapableOfMoving(board, posToMoveFrom, posToMoveTo);
		break;

	case PieceType::rook:
		capableOfMoving = this->_rook.isCapableOfMoving(board, posToMoveFrom, posToMoveTo);
		break;

	case PieceType::knight:
		capableOfMoving = this->_knight.isCapableOfMoving(board, posToMoveFrom, posToMoveTo);
		break;

	case PieceType::bishop:
		capableOfMoving = this->_bishop.isCapableOfMoving(board, posToMoveFrom, posToMoveTo);
		break;
	}

	return capableOfMoving;
}

/*
function checks if piece isnt moving
*/
bool MoveManager::isntMoving(const std::string& posToMoveFrom, const std::string& posToMoveTo) const
{
	// checking if player trying to not move
	if (posToMoveFrom == posToMoveTo)
	{
		return true;
	}
	return false;
}

/*
function checks if player is doing a self check
*/
bool MoveManager::isSelfCheck(
	ChessBoard& board,
	const std::string& posToMoveFrom,
	const std::string& posToMoveTo,
	std::string& currPlayerkingPos,
	const bool& isWhite) const
{
	// checking if other player can check
	return didMakeCheck(board, posToMoveFrom, posToMoveTo, currPlayerkingPos, !isWhite);
}

/*
function checks if made chess in a move
*/
bool MoveManager::didMakeCheck(
	ChessBoard& board,
	const std::string& posToMoveFrom,
	const std::string& posToMoveTo,
	std::string otherPlayerKingPos, // not a reference cause maybe changing it
	const bool& isWhite) const
{

	const PieceColor currentPlayerColor = (isWhite) ? PieceColor::white : PieceColor::black;
	// saving a piece in case eating one when faking a move
	const char pieceInCurrPos = board[posToMoveFrom];
	const char pieceInFuturePos = board[posToMoveTo];
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
			std::string currPiecePosition = Utils::positionIndexToString(std::make_tuple(i, j));

			if (board[currPiecePosition] == EMPTY_TILE)
			{
				continue; // move to next piece
			}

			// if any piece of current player will cause a check
			if (board.getColorOfPieceByPosition(currPiecePosition) == currentPlayerColor)
			{
				if (isCapableMove(board, currPiecePosition, otherPlayerKingPos)) // checking if can eat the king
				{
					isCheck = true;
					break;
				}
			}
		}
	}

	// reverting every move that we have changed(in the fake moves)
	board[posToMoveFrom] = pieceInCurrPos;
	board[posToMoveTo] = pieceInFuturePos;
	return isCheck;
}

/*
function checks if made player checkmate in a move
*/
bool MoveManager::didMakeCheckmate(
	ChessBoard& board,
	const std::string& posToMoveFrom,
	const std::string& posToMoveTo,
	std::string& currPlayerKingPos,
	const bool& isWhite) const
{
	bool isCheckmate = true;

	const PieceColor otherPlayerColor = (isWhite) ? PieceColor::black : PieceColor::white;

	// saving a piece in case eating one when faking a move
	const char pieceInCurrPos = board[posToMoveFrom];
	const char pieceInFuturePos = board[posToMoveTo];

	// faking a move
	makeMove(board, posToMoveFrom, posToMoveTo);

	// going over all the pieces in the board
	for (unsigned int i = 0; i < TILES_PER_SIDE && isCheckmate; i++)
	{
		for (unsigned int j = 0; j < TILES_PER_SIDE && isCheckmate; j++)
		{
			std::string piecePosition = Utils::positionIndexToString(std::make_tuple(i, j));

			// if isn't a piece
			if (board[piecePosition] == EMPTY_TILE)
			{
				continue; // move to next piece
			}
			
			// if any piece of current player may save the king
			if (board.getColorOfPieceByPosition(piecePosition) == otherPlayerColor)
			{
				// going over every place in the board to check if can save the king
				for (unsigned int k = 0; k < TILES_PER_SIDE && isCheckmate; k++)
				{
					for (unsigned int l = 0; l < TILES_PER_SIDE && isCheckmate; l++)
					{
						std::string positionToTest = Utils::positionIndexToString(std::make_tuple(k, l));
						
						// checking if not eating ourselfs
						if (board.getColorOfPieceByPosition(positionToTest) != otherPlayerColor)
						{
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
	}
	// reverting every move that we have changed(in the fake moves)
	board[posToMoveFrom] = pieceInCurrPos;
	board[posToMoveTo] = pieceInFuturePos;
	return isCheckmate;
}

