#pragma once
#include <string>

class Player
{
public:
	Player(const bool& white);

	void setTurn(const bool& playerTurn);

	bool isWhite() const;
	bool isPlayerTurn() const;
	std::string getKingPosition() const;
	void setKingPosition(const std::string& position);

protected:
	bool _playerTurn;
	bool _white;  // which means if he's starting and what side his pawns move
	std::string _kingPosition;
};
