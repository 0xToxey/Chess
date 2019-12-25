#include "MoveChecking.hpp"
#include "constants.hpp"
#include "Utils.hpp"

MoveChecker::MoveChecker() :
	_rook(PieceType::rook, "00", false),
	_king(PieceType::king, "00", false )
{
};

MoveCode MoveChecker::checkMove(
	const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
	const Player (&players)[NUM_OF_PLAYERS],
	const std::string& posToMoveFrom,
	const std::string& posToMoveTo)
{
	const unsigned int IndexOfPlayerTurn = checkPlayerTurn(players);
	MoveCode moveCode;

	if (isMovingOtherPlayerPieces(board, posToMoveFrom, players[IndexOfPlayerTurn].isWhite()) == MoveCode::NotPlayerPiece)
	{
		return MoveCode::NotPlayerPiece;
	}
	else if (IsEatingSelf(board, posToMoveFrom, posToMoveTo) == MoveCode::EatingSelf)
	{
		return MoveCode::EatingSelf;
	}
	else if (isMoving(posToMoveFrom, posToMoveTo) == MoveCode::NotMoving)
	{
		return MoveCode::NotMoving;
	}
	else if (isCapableMove(board, posToMoveFrom, posToMoveTo) == MoveCode::NotCapableMove)
	{
		return MoveCode::NotCapableMove;
	}

	return MoveCode::ValidMove;
}

MoveCode MoveChecker::isMovingOtherPlayerPieces(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& posToMoveFrom, const bool& isWhite)
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

MoveCode MoveChecker::IsEatingSelf(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& posToMoveFrom, const std::string& posToMoveTo)
{
	// checking if player is trying to take over his own pieces
	if (getColorOfPieceByPosition(board, posToMoveFrom) == getColorOfPieceByPosition(board, posToMoveTo))
	{
		return MoveCode::EatingSelf;
	}
	return MoveCode::ValidMove;
}

MoveCode MoveChecker::isCapableMove(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& posToMoveFrom, const std::string& posToMoveTo)
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

MoveCode MoveChecker::isMoving(const std::string& posToMoveFrom, const std::string& posToMoveTo)
{
	// checking if player trying to not move
	if (posToMoveFrom == posToMoveTo)
	{
		return MoveCode::NotMoving;
	}
	return MoveCode::ValidMove;
}


