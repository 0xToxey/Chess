#include "Player.hpp"

#include "Pieces.hpp"

using namespace ChessPieces;

Player::Player(const bool& white) :
	_white(white),
	_playerTurn(white)
	//_pieces{nullptr}
{
	//switch (this->_white)
	//{
	//	case true:
	//		this->_pieces[0] = new Rook(PieceType::rook, "a1", true);
	//		this->_pieces[1] = new Rook(PieceType::rook, "h1", true);
	//		break;
	//	case false:
	//		this->_pieces[0] = new Rook(PieceType::rook, "a8", false);
	//		this->_pieces[1] = new Rook(PieceType::rook, "h8", false);
	//		break;
	//}
};

Player::~Player()
{
	/*for (auto& piece : this->_pieces)
	{
		if (piece != nullptr)
		{
			delete piece;
		}
	}*/
}

void Player::setTurn(const bool& playerTurn)
{
	this->_playerTurn = playerTurn;
}

bool Player::isWhite() const
{
	return this->_white;
}

bool Player::isPlayerTurn() const
{
	return this->_playerTurn;
}
