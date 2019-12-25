#include "Player.hpp"

Player::Player(const bool& white) :
	_playerTurn(white),
	_white(white)
{
	this->_kingPosition = (this->_white) ? "d0" : "d8";
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

std::string Player::getKingPosition() const
{
	return this->_kingPosition;
}

void Player::setKingPosition(const std::string& position)
{
	this->_kingPosition = position;
}
