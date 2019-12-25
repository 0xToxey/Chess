#pragma once

class Player
{
public:
	Player(const bool& white);

	void setTurn(const bool& playerTurn);

	bool isWhite() const;
	bool isPlayerTurn() const;

protected:
	bool _playerTurn;
	bool _white;  // which means if he's starting and what side his pawns move
};