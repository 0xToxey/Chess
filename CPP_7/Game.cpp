#include "Game.hpp"
#include "Utils.hpp"
#include <tuple>

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
			// changing the pieces on the actual board
			int positionToMoveTo0, positionToMoveTo1, positionToMoveFrom0, positionToMoveFrom1;
			std::tie(positionToMoveTo0, positionToMoveTo1) = positionStringToInt(positionToMoveTo);
			std::tie(positionToMoveFrom0, positionToMoveFrom1) = positionStringToInt(positionToMoveFrom);

			this->_board[positionToMoveTo0][positionToMoveTo1] = 
				this->_board[positionToMoveFrom0][positionToMoveFrom1];

			this->_board[positionToMoveFrom0][positionToMoveFrom1] = EMPTY_TILE;


			// changing the players turn
			unsigned int IndexOfPlayerTurn = checkPlayerTurn(this->_players);
			this->_players[IndexOfPlayerTurn].setTurn(false);
			this->_players[(IndexOfPlayerTurn == 1) ? 0 : 1].setTurn(true);
		}
	}
	return result;
}
