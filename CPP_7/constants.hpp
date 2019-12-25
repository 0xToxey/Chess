#pragma once

//game class defines
#define NUM_OF_PLAYERS 2
#define TILES_PER_SIDE 8


#define ASCII_LETTER_CONVERT 96
#define ASCII_NUMBER_CONVERT 48
#define EMPTY_TILE '#'

enum MoveCode
{
	ValidMove = 0,
	MadeCheck = 1,
	NotPlayerPiece = 2,
	EatingSelf = 3,
	SelfCheck = 4,
	NotCapableMove = 6,
	NotMoving = 7,
	CheckMate = 8
};

enum class PieceType {
	king,
	queen,
	pawn,
	rook,
	knight,
	bishop,
	empty
};

enum class PieceColor
{
	black,
	white,
	empty
};