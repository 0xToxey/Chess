#pragma once
#include "MoveManager.hpp"

class Game
{
	public:
		// C'TOR
		Game();

		MoveCode move(const std::string& msgFromGraphics);

	protected:
		MoveManager _moveManager;
		Player _players[NUM_OF_PLAYERS];
		char _board[TILES_PER_SIDE][TILES_PER_SIDE];
};