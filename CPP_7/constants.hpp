#pragma once

#define NUM_OF_PLAYERS 2
#define NUM_OF_TILES 8

#define ASCII_LETTER_CONVERT 96
#define ASCII_NUMBER_CONVERT 48
#define EMPTY_TILE '#'


enum class PieceType {
	king,
	queen,
	pawn,
	rook,
	knight,
	bishop,
	empty
};