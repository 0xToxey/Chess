#pragma once

//game class defines
#define NUM_OF_PLAYERS 2
#define TILES_PER_SIDE 8

//MoveChecking class defines
#define NUM_OF_PLAYERS 2
#define VALID_CHECK 0
#define CASE_2_INVALID 2
#define CASE_3_INVALID 3
#define CASE_6_INVALID 6
#define CASE_7_INVALID 7

// ?? defines
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