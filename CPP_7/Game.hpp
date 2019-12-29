#pragma once
#include "MoveManager.hpp"
#include "ChessBoard.hpp"

class Game
{
	public:
		// C'TOR
		Game();

		// function that calls function to check if move capable and makes a move
		MoveCode move(const std::string& msgFromGraphics);

	private:
		MoveManager _moveManager;
		Player _players[NUM_OF_PLAYERS];
		ChessBoard _board;
};