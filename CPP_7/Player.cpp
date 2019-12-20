#include "Player.hpp"

#include "Pieces.hpp"

using namespace ChessPieces;

Player::Player(const bool white) :
	_white(white),
	_pieces()
{
	switch (this->_white)
	{
		case true:
			this->_pieces[0] = new Rook(PieceType::rook, "a1");
			this->_pieces[0] = new Rook(PieceType::rook, "h1");
		case false:
			this->_pieces[0] = new Rook(PieceType::rook, "a8");
			this->_pieces[0] = new Rook(PieceType::rook, "h8");
	}
};

Player::~Player()
{
	for (auto& piece : this->_pieces)
	{
		if (piece != nullptr)
		{
			delete piece;
		}
	}
}

bool Player::isWhite() const
{
	return this->_white;
}
