#pragma once
#include "Player.hpp"
#include "MoveChecking.hpp"

#define NUM_OF_PLAYERS 2
#define NUM_OF_TILES 8

class Game
{
public:
	Game(const std::string& startingBoard);
	~Game();
	int move(const std::string& msgFromGraphics);

	MoveChecker _moveChecker;
	Player _players[NUM_OF_PLAYERS];
	char _board[NUM_OF_TILES][NUM_OF_TILES];
};