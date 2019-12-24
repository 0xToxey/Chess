#include "MoveChecking.hpp"

MoveChecker::MoveChecker() :
	_rook(PieceType::rook, "00", false)
{
};

int MoveChecker::checkMove(
	const Player (&players)[NUM_OF_PLAYERS],
	const std::string& positionToMoveFrom,
	const std::string& positionToMoveTo,
	const char (&board)[NUM_OF_TILES][NUM_OF_TILES])
{
	unsigned int IndexOfPlayerTurn = checkPlayerTurn(players);
	

	if (case2(board, positionToMoveFrom, players[IndexOfPlayerTurn].isWhite()) == CASE_2_INVALID)
	{
		return CASE_2_INVALID;
	}
	else if (case3(board, positionToMoveFrom, positionToMoveTo) == CASE_3_INVALID)
	{
		return CASE_3_INVALID;
	}
	else if (case7(positionToMoveFrom, positionToMoveTo) == CASE_7_INVALID)
	{
		return CASE_7_INVALID;
	}
	else if (case6(board, positionToMoveFrom, positionToMoveTo) == CASE_6_INVALID)
	{
		return CASE_6_INVALID;
	}

	return VALID_CHECK;
}

int MoveChecker::case2(const char(&board)[NUM_OF_TILES][NUM_OF_TILES], const std::string& positionToMoveFrom, const bool& isWhite)
{
	if (getColorOfPieceByPosition(board, positionToMoveFrom) == PieceColor::empty)
	{
		return CASE_2_INVALID;
	}

	switch (getColorOfPieceByPosition(board, positionToMoveFrom))
	{
		case PieceColor::white:
			return ((isWhite) ? VALID_CHECK : CASE_2_INVALID);
		case PieceColor::black:
			return ((isWhite) ? CASE_2_INVALID : VALID_CHECK);
	}
}

int MoveChecker::case3(const char(&board)[NUM_OF_TILES][NUM_OF_TILES], const std::string& positionToMoveFrom, const std::string& positionToMoveTo)
{
	if (getColorOfPieceByPosition(board, positionToMoveFrom) == getColorOfPieceByPosition(board, positionToMoveTo))
	{
		return CASE_3_INVALID;
	}
	return VALID_CHECK;
}

int MoveChecker::case6(const char(&board)[NUM_OF_TILES][NUM_OF_TILES], const std::string& positionToMoveFrom, const std::string& positionToMoveTo)
{
	PieceType currentPieceType = getTypeOfPieceByPostion(board, positionToMoveFrom);
	bool capableOfMoving;
	switch (currentPieceType)
	{
		case PieceType::king:
			break;
		case PieceType::queen:
			break;
		case PieceType::pawn:
			break;
		case PieceType::rook:
			this->_rook.setCurrentPosition(positionToMoveFrom);
			capableOfMoving = this->_rook.checkIfCapableMove(positionToMoveTo);
			break;
		case PieceType::knight:
			break;
		case PieceType::bishop:
			break;
		case PieceType::empty:
			break;
	}

	if (capableOfMoving == false)
	{
		return CASE_6_INVALID;
	}
	return VALID_CHECK;

}

int MoveChecker::case7(const std::string& positionToMoveFrom, const std::string& positionToMoveTo)
{
	if (positionToMoveFrom == positionToMoveTo)
	{
		return CASE_7_INVALID;
	}
	return VALID_CHECK;
}


