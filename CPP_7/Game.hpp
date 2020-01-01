#pragma once
#include "MoveManager.hpp"
#include "ChessBoard.hpp"
#include "Pipe.h"

class Game
{
	public:
		// C'TOR
		Game(const Pipe& mainPipe, const Pipe& changePipe, const bool& isBotPlaying);

		// function that calls function to check if move capable and makes a move
		MoveCode move(const std::string& msgFromGraphics);
		bool isBotPlaying() const;
		std::string getMoveFromBot() const;
		
		Player _players[NUM_OF_PLAYERS];
	private:
		void tryToPromote(const std::string& posToMoveTo);

		std::string getBoardForBot() const;
		Pipe _mainPipe;
		Pipe _changePipe; // can change the board.
		MoveManager _moveManager;
		ChessBoard _board;
		bool _isBotPlaying;
};