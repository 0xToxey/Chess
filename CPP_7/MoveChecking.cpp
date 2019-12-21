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
	else if (case3(getPieceByPosition(players, positionToMoveTo), getPieceByPosition(players, positionToMoveFrom)) == CASE_3_INVALID)
	{
		return CASE_3_INVALID;
	}

	return VALID_CHECK;
}

int MoveChecker::case2(const char(&board)[NUM_OF_TILES][NUM_OF_TILES], const std::string& positionToMoveFrom)
{
	if (board[(int)(positionToMoveFrom[0]) - 48 - 48][(int)positionToMoveFrom[1] - 48] == '#')
	{
		return CASE_2_INVALID;
	}
	return VALID_CHECK;
}

int MoveChecker::case3(const Piece* piece1, const Piece* piece2)
{
	if (piece1->isWhite() == piece2->isWhite())
	{
		return CASE_3_INVALID;
	}
	return VALID_CHECK;
}


Piece* MoveChecker::getPieceByPosition(const Player (&players)[NUM_OF_PLAYERS], const std::string& position)
{

	for (auto const& player : players)
	{
		for (auto const& piece : player._pieces)
		{
			if (piece == nullptr)
			{
				break;
			}
			else if(piece->getCurrentPosition() == position)
			{
				return piece;
			}
		}
	}

	/*for (int i = 0; i < NUM_OF_PLAYERS; i++)
	{
		for (int j = 0; j < PIECES_PER_PLAYER; j++)
		{
			if (players[i]._pieces[j] == nullptr)
			{
				break;
			}
			else if (players[i]._pieces[j]->getCurrentPosition() == position)
			{
				return players[i]._pieces[j];
			}
		}
	}*/
}
