#include "Player.hpp"

Player::Player(const bool& white) :
	_playerTurn(white),
	_white(white)
{
};

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
