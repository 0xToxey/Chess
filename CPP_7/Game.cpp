#include "Game.hpp"
#include "Utils.hpp"
#include <tuple>

// C'TOR
Game::Game(const std::string& startingBoard) :
	_players{ Player(true), Player(false) },
	_board{ NULL },
	_moveChecker()
{
	std::string arrayBoard = startingBoard;
	std::reverse(arrayBoard.begin(), arrayBoard.end());

	strcpy((char*)this->_board, arrayBoard.c_str());
}

/*
function calls function to check if move is capbale, if is capabel - doing the move
input:
	msgFromGraphics - message containing where player is , and where to move
output:
	MoveErrorCode - a code accourding to the pptx
*/
int Game::move(const std::string& msgFromGraphics)
{
	// unpacking msg from graphics from 'e2f4' format to 'e2', 'f4'
	std::string positionToMoveFrom = msgFromGraphics.substr(0, 2);
	std::string positionToMoveTo = msgFromGraphics.substr(2, 4);

	int moveErrorCode = this->_moveChecker.checkMove(this->_board, this->_players, positionToMoveFrom, positionToMoveTo);
	if (moveErrorCode != VALID_CHECK)
	{
		return moveErrorCode;
	}

	// changing the pieces on the actual board
	int rowToMoveFrom, colToMoveFrom, rowToMoveTo, colToMoveTo;
	std::tie(rowToMoveTo, colToMoveTo) = positionStringToInt(positionToMoveTo);
	std::tie(rowToMoveFrom, colToMoveFrom) = positionStringToInt(positionToMoveFrom);

	this->_board[rowToMoveTo][colToMoveTo] = this->_board[rowToMoveFrom][colToMoveFrom];
	this->_board[rowToMoveFrom][colToMoveFrom] = EMPTY_TILE;

	// changing the players turn
	unsigned int IndexOfPlayerTurn = checkPlayerTurn(this->_players);
	this->_players[IndexOfPlayerTurn].setTurn(false);
	this->_players[(IndexOfPlayerTurn == 1) ? 0 : 1].setTurn(true);
	return VALID_CHECK;
}
