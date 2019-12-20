#include "Board.hpp"

Board::Board(const std::string& startingBoard):
	_players{Player(true), Player(false)},
	_board{NULL}

{
	strcpy((char*)this->_board, startingBoard.c_str());
}