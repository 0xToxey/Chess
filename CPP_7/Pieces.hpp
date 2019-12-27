#pragma once
#include "Piece.hpp"

namespace ChessPieces
{
	class Rook : public Piece
	{
	public:
		// C'TOR
		Rook();

		virtual bool isCapableOfMoving(
			const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], 
			const std::string& posToMoveFrom,
			const std::string& posToMoveTo);
	
	protected:
		virtual bool isMovingAcrossPieces(
			const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
			const unsigned int& rowToMoveFrom, const unsigned int& colToMoveFrom,
			const unsigned int& rowToMoveTo, const unsigned int& colToMoveTo);

	};

	class King : public Piece
	{
	public:
		// C'TOR
		King();

		virtual bool isCapableOfMoving(
			const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
			const std::string& posToMoveFrom,
			const std::string& posToMoveTo);

	protected:
		// King always will be able to move without moving across other piece.
		virtual bool isMovingAcrossPieces(
			const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
			const unsigned int& rowToMoveFrom, const unsigned int& colToMoveFrom,
			const unsigned int& rowToMoveTo, const unsigned int& colToMoveTo);
	};

	class Knight : public Piece
	{
	public:
		// C'TOR
		Knight();

		virtual bool isCapableOfMoving(
			const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
			const std::string& posToMoveFrom,
			const std::string& posToMoveTo);

	protected:
		// kinght can jump acroos other picese 
		virtual bool isMovingAcrossPieces(
			const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
			const unsigned int& rowToMoveFrom, const unsigned int& colToMoveFrom,
			const unsigned int& rowToMoveTo, const unsigned int& colToMoveTo);
	};

	class Bishop : public Piece
	{
	public:
		// C'TOR
		Bishop();

		virtual bool isCapableOfMoving(
			const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
			const std::string& posToMoveFrom,
			const std::string& posToMoveTo);

	protected:

		virtual bool isMovingAcrossPieces(
			const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
			const unsigned int& rowToMoveFrom, const unsigned int& colToMoveFrom,
			const unsigned int& rowToMoveTo, const unsigned int& colToMoveTo);
	};
}