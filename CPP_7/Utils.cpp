#include "Utils.hpp"
#include <tuple>
#include <cctype>

/*
function converts from position string(ex: e2)
to array index(ex: <1,4>)
*/
std::tuple<unsigned int, unsigned int> Utils::positionStringToIndex(const std::string& position)
{
	// conversion from e2 to <1, 4>
	return std::make_tuple(position[1] - ASCII_NUMBER_CONVERT - 1, position[0] - ASCII_LETTER_CONVERT - 1);
}

/*
function converts from array index(ex: <1,4>)
to position string(ex: ew)
*/
std::string Utils::positionIndexToString(const std::tuple <unsigned int, unsigned int>& positionInt)
{
	// conversion from <1, 4> to e2
	std::string position;
	position += static_cast<char>(std::get<1>(positionInt) + ASCII_LETTER_CONVERT + 1); // ex: e
	position += static_cast<char>(std::get<0>(positionInt) + ASCII_NUMBER_CONVERT + 1); // ex: 2

	return position;
}

/*
function returns color of a piece by its position
*/
PieceColor Utils::getColorOfPieceByPosition(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& position)
{
	auto [row, col] = positionStringToIndex(position);
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

/*
function returns type of a piece by its position
*/
PieceType Utils::getTypeOfPieceByPosition(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& position)
{
	auto [row, col] = positionStringToIndex(position);
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

/*
function returns the index of the player whose turn is
*/
unsigned int Utils::WhoseTurnIsIt(const Player(&players)[NUM_OF_PLAYERS])
{
	for (unsigned int i = 0; i < NUM_OF_PLAYERS; i++)
	{
		if (players[i].isPlayerTurn())
		{
			return i;
		}
	}
}

/*
function inserts a piece into a board array
*/
void Utils::insertPieceIntoBoard(char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const char& piece, const std::string& position)
{
	auto [row, col] = positionStringToIndex(position);
	board[row][col] = piece;
}
