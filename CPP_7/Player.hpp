#pragma once
#include "Piece.hpp"
#define PIECES_PER_PLAYER 16

class Player
{
public:
	Player(const bool& white);
	~Player();

	bool isWhite() const;
	Piece* _pieces[PIECES_PER_PLAYER];

protected:
	bool _white;  // whice means if he's starting and what side his pawns move
};