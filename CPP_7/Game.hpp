#pragma once
#include "MoveChecking.hpp"

class Game
{
public:
	// C'TOR
	Game(const std::string& startingBoard);

	int move(const std::string& msgFromGraphics);

protected:
	MoveChecker _moveChecker;
	Player _players[NUM_OF_PLAYERS];
	char _board[TILES_PER_SIDE][TILES_PER_SIDE];
};