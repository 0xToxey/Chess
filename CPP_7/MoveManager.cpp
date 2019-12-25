#include "MoveManager.hpp"
#include "constants.hpp"
#include "Utils.hpp"
#include <tuple>

MoveManager::MoveManager() :
	_rook(PieceType::rook, "00", false),
	_king(PieceType::king, "00", false )
{
};

MoveCode MoveManager::checkMove(
	char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
	const Player (&players)[NUM_OF_PLAYERS],
	const std::string& posToMoveFrom,
	const std::string& posToMoveTo)
{
	const unsigned int playerTurn = checkPlayerTurn(players);
	const bool isWhite = players[playerTurn].isWhite();
	const std::string otherPlayerKingPos = players[(playerTurn == 1) ? 0 : 1].getKingPosition();
	const std::string currentPlayerKingPos = players[playerTurn].getKingPosition();
	
	if (isMovingOtherPlayerPieces(board, posToMoveFrom, players[playerTurn].isWhite()) == MoveCode::NotPlayerPiece)
	{
		return MoveCode::NotPlayerPiece;
	}
	if (IsEatingSelf(board, posToMoveFrom, posToMoveTo) == MoveCode::EatingSelf)
	{
		return MoveCode::EatingSelf;
	}
	if (isMoving(posToMoveFrom, posToMoveTo) == MoveCode::NotMoving)
	{
		return MoveCode::NotMoving;
	}
	if (isCapableMove(board, posToMoveFrom, posToMoveTo) == MoveCode::NotCapableMove)
	{
		return MoveCode::NotCapableMove;
	}

	//if(isSelfCheck(board, posToMoveFrom, posToMoveTo, ))
	// in case the move is possible checking for check
	if(didMakeCheck(board, posToMoveFrom, posToMoveTo,otherPlayerKingPos, isWhite) == MoveCode::MadeCheck)
	{
		if (didMakeCheckmate(board, posToMoveFrom, posToMoveTo, otherPlayerKingPos, isWhite) == MoveCode::CheckMate)
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

MoveCode MoveManager::isMovingOtherPlayerPieces(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& posToMoveFrom, const bool& isWhite)
{
	// checking if the player is trying to move pieces that aren't his
	switch (getColorOfPieceByPosition(board, posToMoveFrom))
	{
		case PieceColor::white:
			return ((isWhite) ? MoveCode::ValidMove : MoveCode::NotPlayerPiece);
		case PieceColor::black:
			return ((isWhite) ? MoveCode::NotPlayerPiece : MoveCode::ValidMove);
		case PieceColor::empty:
			return MoveCode::NotPlayerPiece;
	}
}

MoveCode MoveManager::IsEatingSelf(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& posToMoveFrom, const std::string& posToMoveTo)
{
	// checking if player is trying to take over his own pieces
	if (getColorOfPieceByPosition(board, posToMoveFrom) == getColorOfPieceByPosition(board, posToMoveTo))
	{
		return MoveCode::EatingSelf;
	}
	return MoveCode::ValidMove;
}

MoveCode MoveManager::isCapableMove(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& posToMoveFrom, const std::string& posToMoveTo)
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

	if (capableOfMoving == false)
	{
		return MoveCode::NotCapableMove;
	}
	return MoveCode::ValidMove;

}

MoveCode MoveManager::isMoving(const std::string& posToMoveFrom, const std::string& posToMoveTo)
{
	// checking if player trying to not move
	if (posToMoveFrom == posToMoveTo)
	{
		return MoveCode::NotMoving;
	}
	return MoveCode::ValidMove;
}

MoveCode MoveManager::didMakeCheck(char (&board)[TILES_PER_SIDE][TILES_PER_SIDE],
                                   const std::string& posToMoveFrom, const std::string& posToMoveTo,
                                   const std::string& kingPosition, const bool& isWhite)
{
	unsigned int kingRow, kingCol;
	std::tie(kingRow, kingCol) = positionStringToInt(kingPosition);
	const PieceColor currentPlayerColor = (isWhite) ? PieceColor::white : PieceColor::black;

	// faking a move
	makeMove(board, posToMoveFrom, posToMoveTo);

	for(unsigned int i = 0; i < TILES_PER_SIDE; i++)
	{
		for(unsigned int j = 0; j < TILES_PER_SIDE; j++)
		{
			if(board[i][j] == EMPTY_TILE)
			{
				continue; // move to next piece
			}
			
			std::string piecePosition = positionIntToString(std::make_tuple(i, j));

			// if any piece of current player will cause a check
			if(getColorOfPieceByPosition(board, piecePosition) == currentPlayerColor)
			{
				if(isCapableMove(board, piecePosition, kingPosition) == MoveCode::ValidMove)
				{
					// reverting the move
					makeMove(board, posToMoveTo, posToMoveFrom);
					return MoveCode::MadeCheck;
				}
			}
		}
	}
	
	// reverting the move
	makeMove(board, posToMoveTo, posToMoveFrom);
	return MoveCode::ValidMove;
}

MoveCode MoveManager::didMakeCheckmate(const char (& board)[TILES_PER_SIDE][TILES_PER_SIDE],
                                       const std::string& posToMoveFrom, const std::string& posToMoveTo,
									   const std::string& kingPosition, const bool& isWhite)
{
	return MoveCode::ValidMove;
}


