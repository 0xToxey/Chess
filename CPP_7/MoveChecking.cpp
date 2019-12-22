#include "MoveChecking.hpp"
#include "Pieces.hpp"

int MoveChecker::checkMove(
	const Player (&players)[NUM_OF_PLAYERS],
	const std::string& positionToMoveFrom,
	const std::string& positionToMoveTo,
	const char (&board)[NUM_OF_TILES][NUM_OF_TILES])
{
	if (case2(board, positionToMoveFrom) == CASE_2_INVALID)
	{
		return CASE_2_INVALID;
	}
	else if (case3(board, positionToMoveFrom, positionToMoveTo) == CASE_3_INVALID)
	{
		return CASE_3_INVALID;
	}

	return VALID_CHECK;
}

int MoveChecker::case2(const char(&board)[NUM_OF_TILES][NUM_OF_TILES], const std::string& positionToMoveFrom)
{
	if (getColorOfPieceByPosition(board, positionToMoveFrom) == PieceColor::empty)
	{
		return CASE_2_INVALID;
	}
	return VALID_CHECK;
}

int MoveChecker::case3(const char(&board)[NUM_OF_TILES][NUM_OF_TILES], const std::string& positionToMoveFrom, const std::string& positionToMoveTo)
{
	if (getColorOfPieceByPosition(board, positionToMoveFrom) == getColorOfPieceByPosition(board, positionToMoveTo))
	{
		return CASE_3_INVALID;
	}
	return VALID_CHECK;
}


