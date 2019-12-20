#include "Board.hpp"

Board::Board(const std::string& startingBoard):
	_players(Player[2])
	_players[0](true),
	_players[1](false)
{

}