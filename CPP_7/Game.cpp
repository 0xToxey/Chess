#include "Game.hpp"

Game::Game(const std::string& startingBoard) :
	_players{ Player(true), Player(false) },
	_board{ NULL },
	_moveChecker()

{
	strcpy((char*)this->_board, startingBoard.c_str());
}

Game::~Game()
{
}

int Game::move(const std::string& msgFromGraphics)
{
	int result = this->_moveChecker.checkMove(this->_players, msgFromGraphics.substr(0, 2), msgFromGraphics.substr(2, 4), this->_board);
	{
		if (result == VALID_CHECK)
		{
			this->_board[(int)msgFromGraphics[2] - 48 - 48][(int)msgFromGraphics[3] - 48] = this->_board[msgFromGraphics[0]][msgFromGraphics[1]];
			this->_board[(int)msgFromGraphics[0] - 48 - 48][(int)msgFromGraphics[1] - 48] = '#';
		}
	}
	return result;
}
