#include "Utils.hpp"
#include <tuple>
#include <cctype>

std::tuple<unsigned int, unsigned int> positionStringToInt(const std::string& position)
{
	// conversion from e2 to <1, 4>
	return std::make_tuple(position[1] - ASCII_NUMBER_CONVERT - 1, position[0] - ASCII_LETTER_CONVERT - 1);
}

std::string positionIntToString(const std::tuple <unsigned int, unsigned int>& positionInt)
{
	// conversion from <1, 4> to e2
	std::string position;
	position += static_cast<char>(static_cast<char>(std::get<1>(positionInt) + ASCII_LETTER_CONVERT + 1));
	position += static_cast<char>(static_cast<char>(std::get<0>(positionInt) + ASCII_NUMBER_CONVERT + 1));
	
	return position;
}

PieceColor getColorOfPieceByPosition(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& position)
{
	unsigned int row, col;
	std::tie(row, col) = positionStringToInt(position);
	if (std::isupper(board[row][col])) // is white piece
	{
		return PieceColor::white;
	}
	else if (std::islower(board[row][col])) // is black piece
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

PieceType getTypeOfPieceByPosition(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& position)
{
	int row, col;
	std::tie(row, col) = positionStringToInt(position);
	const char piece = board[row][col];

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

void insertPieceIntoBoard(char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const char& piece, const std::string& position)
{
	unsigned int row, col;
	std::tie(row, col) = positionStringToInt(position);
	board[row][col] = piece;
}
