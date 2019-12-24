#include "Utils.hpp"
#include <tuple>
#include <cctype>

std::tuple<int, int> positionStringToInt(const std::string& position)
{
	return std::make_tuple(position[1] - ASCII_NUMBER_CONVERT - 1, position[0] - ASCII_LETTER_CONVERT - 1);
}

PieceColor getColorOfPieceByPosition(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& position)
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

PieceType getTypeOfPieceByPostion(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& position)
{
	int position0, position1;
	std::tie(position0, position1) = positionStringToInt(position);
	char piece = board[position0][position1];

	switch (piece)
	{
		case 'k': case 'K':
			return PieceType::king;
		case 'q': case 'Q':
			return PieceType::queen;
		case 'p': case 'P':
			return PieceType::pawn;
		case 'r': case 'R':
			return PieceType::rook;
		case 'n': case 'N':
			return PieceType::knight;
		case 'b': case 'B':
			return PieceType::bishop;
		case '#':
			return PieceType::empty;
	}
}
