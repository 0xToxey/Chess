#include <cpr/cpr.h>
#include "Game.hpp"
#include <tuple>
#include "Utils.hpp"

// C'TOR
Game::Game(const Pipe& mainPipe, const Pipe& changePipe, const bool& isBotPlaying) :
	_players{ Player(true), Player(false) },
	_board{ "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr" },
	_mainPipe(mainPipe),
	_changePipe(changePipe),
	_isBotPlaying(isBotPlaying)
{
}

/*
function calls function to check if move is capable, if is capable - doing the move
input:
	msgFromGraphics - message containing where is the player and the dest tail to move
output:
	MoveErrorCode - a code according to the pptx
*/
MoveCode Game::move(const std::string& msgFromPlayer)
{
	// unpacking msg from graphics from 'e2f4' format to 'e2', 'f4'
	const std::string posToMoveFrom = msgFromPlayer.substr(0, 2);
	const std::string posToMoveTo = msgFromPlayer.substr(2, 4);
	MoveCode moveCode = MoveCode::ValidMove;

	// if it's the bot's turn not checking the move
	if (this->_isBotPlaying && Utils::WhoseTurnIsIt(this->_players) == BOT_TURN)
	{	
		if (msgFromPlayer == "stalemate" || msgFromPlayer == "checkmate" || msgFromPlayer.find("invalid") != std::string::npos)
		{
			moveCode = MoveCode::CheckMate;
		}
		this->_changePipe.sendMessageToGraphics(("Botmove " + msgFromPlayer).c_str());
		this->tryToPromote(posToMoveTo);

	}
	else
	{
		moveCode = this->_moveManager.checkMove(this->_board, this->_players, posToMoveFrom, posToMoveTo);

		if (moveCode != MoveCode::ValidMove &&
			moveCode != MoveCode::MadeCheck &&
			moveCode != MoveCode::CheckMate)
		{
			return moveCode;
		}
	}

	this->_moveManager.makeMove(this->_players, this->_board, posToMoveFrom, posToMoveTo);
	this->tryToPromote(posToMoveTo);

	return moveCode;
}

bool Game::isBotPlaying() const
{
	return this->_isBotPlaying;
}


/*
function tries to promote a pawn if he's in the starting opposite starting position
*/
void Game::tryToPromote(const std::string& posToMoveTo)
{
	// checking if trying to move a pawn and do a promotion
	if (this->_board.getTypeOfPieceByPosition(posToMoveTo) == PieceType::pawn)
	{
		const int rowToMoveTo = posToMoveTo[1] - '0' - 1; // converting from "1" to 0, "2" to 1
		if (rowToMoveTo == WHITE_START_ROW ||
			rowToMoveTo == BLACK_START_ROW)
		{
			this->_changePipe.sendMessageToGraphics(("Promote " + posToMoveTo).c_str());

			switch (rowToMoveTo)
			{
				case WHITE_START_ROW:
					this->_board[posToMoveTo] = 'q';
					break;
				case BLACK_START_ROW:
					this->_board[posToMoveTo] = 'Q';
					break;
			}
		}
	}
	
}

/*
function talks to the bot api and gets a move
*/
std::string Game::getMoveFromBot() const
{
	std::string request = "http://www.chessdb.cn/cdb.php?action=queryall&board=";
	const std::string board = this->getBoardForBot();
	request += board + "%20b&showall=1";
	std::cout << request << std::endl;
	auto r = cpr::Get(cpr::Url{ request });

	// if bot lost or won
	if (r.text == "stalemate" || r.text == "checkmate" || r.text.find("invalid") != std::string::npos)
	{
		return r.text;
	}
	return r.text.substr(5, 4);
}

/*
function returns a board string in the format for the bot api
*/
std::string Game::getBoardForBot() const
{
	std::string board;
	for (int i = TILES_PER_SIDE - 1; i >= 0; i--)
	{
		int emptyCount = 0;

		for (int j =  0; j < TILES_PER_SIDE; j++)
		{
			if (this->_board.getPieceByIndex(i, j) == EMPTY_TILE) // counting the empty tiles
			{
				emptyCount++;
			}

			if (this->_board.getPieceByIndex(i, j) != EMPTY_TILE)
			{
				if (emptyCount > 0)
				{
					board += std::to_string(emptyCount);
					emptyCount = 0;
				}
				board += this->_board.getPieceByIndex(i, j);
			}

			if (j == TILES_PER_SIDE - 1 && emptyCount > 0) // end of line
			{
				board += std::to_string(emptyCount);
			}
		}
		board.append("/");
	}
	return board;
}
