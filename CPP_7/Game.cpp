#include "Game.hpp"

Game::Game(const std::string& startingBoard) :
	_players{ Player(true), Player(false) },
	_board{ NULL },
	_moveChecker()

{
	int count = startingBoard.length() - 1;
	for (int i = 0; i < NUM_OF_TILES; i++)
	{
		for (int j = 0; j < NUM_OF_TILES; j++)
		{
			this->_board[i][j] = startingBoard[count];
			count--;
		}
	}
	//strcpy((char*)this->_board, startingBoard.c_str());
}

Game::~Game()
{
}

int Game::move(const std::string& msgFromGraphics)
{
	std::string positionToMoveFrom = msgFromGraphics.substr(0, 2);
	std::string positionToMoveTo = msgFromGraphics.substr(2, 4);
	int result = this->_moveChecker.checkMove(this->_players, positionToMoveFrom, positionToMoveTo, this->_board);
	{
		if (result == VALID_CHECK)
		{
			this->_board[std::get<0>(positionStringToInt(positionToMoveTo))][std::get<1>(positionStringToInt(positionToMoveTo))] =
				this->_board[std::get<0>(positionStringToInt(positionToMoveFrom))][std::get<1>(positionStringToInt(positionToMoveFrom))];

			this->_board[std::get<0>(positionStringToInt(positionToMoveFrom))][std::get<1>(positionStringToInt(positionToMoveFrom))] = EMPTY_TILE;

		}
	}
	return result;
}
