#include "Utils.hpp"

//Piece* getPieceByPosition(const Player(&players)[NUM_OF_PLAYERS], const std::string& position)
//{
//
//	for (auto const& player : players)
//	{
//		for (auto const& piece : player._pieces)
//		{
//			if (piece == nullptr)
//			{
//				break;
//			}
//			else if (piece->getCurrentPosition() == position)
//			{
//				return piece;
//			}
//		}
//	}
//}

std::tuple<int, int> positionStringToInt(const std::string& position)
{
	return std::make_tuple(position[1] - ASCII_NUMBER_CONVERT - 1, position[0] - ASCII_LETTER_CONVERT - 1);
}

PieceColor getColorOfPieceByPosition(const char(&board)[NUM_OF_TILES][NUM_OF_TILES], const std::string& position)
{
	int position0, position1;
	std::tie(position0, position1) = positionStringToInt(position);
	if (std::isupper(board[position0][position1]))
	{
		return PieceColor::white;
	}
	else if (std::islower(board[position0][position1]))
	{
		return PieceColor::black;
	}
	else
	{
		return PieceColor::empty;
	}
}

unsigned int checkPlayerTurn(const Player(&players)[NUM_OF_PLAYERS])
{
	for (unsigned int i = 0; i < NUM_OF_PLAYERS; i++)
	{
		if (players[i].isPlayerTurn())
		{
			return i;
		}
	}
}
