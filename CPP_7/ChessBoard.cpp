#include "ChessBoard.hpp"
#include "Utils.hpp"

ChessBoard::ChessBoard(const char* arrayBoard)
{
	//copying the game board into the board array.
	memcpy(this->_board, arrayBoard, TILES_PER_SIDE * TILES_PER_SIDE);
}

/*
function returns a piece from a specific position by reference
*/
char& ChessBoard::operator[](const std::string& position)
{
	const auto [row, col] = Utils::positionStringToIndex(position);
	return this->_board[row][col]; // by reference
}

/*
function returns a piece from a specific position by value
*/
char ChessBoard::operator[](const std::string& position) const
{
	const auto [row, col] = Utils::positionStringToIndex(position);
	return this->_board[row][col]; // by value
}

char ChessBoard::getPieceByIndex(const unsigned int& row, const unsigned int& col) const
{
	return this->_board[row][col];
}


/*
function returns color of a piece by its position
*/
PieceColor ChessBoard::getColorOfPieceByPosition(const std::string& position) const
{
	const auto [row, col] = Utils::positionStringToIndex(position);
	const char& piece = this->_board[row][col];

	if (std::isupper(piece))      // is white piece
	{
		return PieceColor::white;
	}
	else if (std::islower(piece)) // is black piece
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
PieceType ChessBoard::getTypeOfPieceByPosition(const std::string& position) const
{
	const auto [row, col] = Utils::positionStringToIndex(position);
	const char& piece = this->_board[row][col];

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