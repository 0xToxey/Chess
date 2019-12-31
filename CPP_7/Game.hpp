#pragma once
#include "MoveManager.hpp"
#include "ChessBoard.hpp"
#include "Pipe.h"

class Game
{
	public:
		// C'TOR
		Game(Pipe mainPipe, Pipe changePipe);

		// function that calls function to check if move capable and makes a move
		MoveCode move(const std::string& msgFromGraphics);

	private:
		Pipe _mainPipe;
		Pipe _changePipe; // can change the board.

		MoveManager _moveManager;
		Player _players[NUM_OF_PLAYERS];
		ChessBoard _board;
};