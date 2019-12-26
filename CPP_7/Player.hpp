#pragma once
#include <string>

class Player
{
public:
	Player(const bool& white);

	// GETTERS
	bool isPlayerTurn() const;
	bool isWhite() const;
	std::string getKingPosition() const;

	// SETTRS
	void setTurn(const bool& playerTurn);
	void setKingPosition(const std::string& position);

protected:
	bool _playerTurn;
	bool _white;  // which means if he's starting and what side his pawns move
	std::string _kingPosition;
};
