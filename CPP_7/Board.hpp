#pragma once
#include "Player.hpp"

#define NUM_OF_PLAYER 2
#define NUM_OF_TILES 8

class Board
{
public:
	Board(const std::string& startingBoard);


	Player _players[NUM_OF_PLAYER];
	char _board[NUM_OF_TILES][NUM_OF_TILES];
};