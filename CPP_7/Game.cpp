#include "Game.hpp"
#include <tuple>
#include "Utils.hpp"

// C'TOR
Game::Game() :
	_players{ Player(true), Player(false) },
	_board{ NULL }
{
	//copying the game board into the board array.
	const char* arrayBoard = "R##K###R################################################r##k###r";
	memcpy(this->_board, arrayBoard, TILES_PER_SIDE* TILES_PER_SIDE);
}

/*
function calls function to check if move is capable, if is capable - doing the move
input:
	msgFromGraphics - message containing where player is , and where to move
output:
	MoveErrorCode - a code according to the pptx
*/
MoveCode Game::move(const std::string& msgFromGraphics)
{
	// unpacking msg from graphics from 'e2f4' format to 'e2', 'f4'
	const std::string posToMoveFrom = msgFromGraphics.substr(0, 2);
	const std::string posToMoveTo = msgFromGraphics.substr(2, 4);

	const MoveCode moveCode = this->_moveManager.checkMove(this->_board, this->_players, posToMoveFrom, posToMoveTo);

	if (moveCode != MoveCode::ValidMove &&
		moveCode != MoveCode::MadeCheck &&
		moveCode != MoveCode::CheckMate)
	{
		return moveCode;
	}

	this->_moveManager.makeMove(this->_players, this->_board, posToMoveFrom, posToMoveTo);
	return moveCode;
}
