#pragma once
#include "Piece.hpp"
#include "Utils.hpp"

namespace ChessPieces
{
	class Rook : public Piece
	{
	public:
		// C'TOR
		Rook();

		virtual bool isCapableOfMoving(
			const ChessBoard& board, 
			const std::string& posToMoveFrom,
			const std::string& posToMoveTo) const;
	
	private:
		virtual bool isMovingAcrossPieces(
			const ChessBoard& board,
			const unsigned int& rowToMoveFrom, const unsigned int& colToMoveFrom,
			const unsigned int& rowToMoveTo, const unsigned int& colToMoveTo) const;

	};

	class King : public Piece
	{
	public:
		// C'TOR
		King();

		virtual bool isCapableOfMoving(
			const ChessBoard& board,
			const std::string& posToMoveFrom,
			const std::string& posToMoveTo) const;

	private:
		// King always will be able to move without moving across other piece.
		virtual bool isMovingAcrossPieces(
			const ChessBoard& board,
			const unsigned int& rowToMoveFrom, const unsigned int& colToMoveFrom,
			const unsigned int& rowToMoveTo, const unsigned int& colToMoveTo) const;
	};

	class Knight : public Piece
	{
	public:
		// C'TOR
		Knight();

		virtual bool isCapableOfMoving(
			const ChessBoard& board,
			const std::string& posToMoveFrom,
			const std::string& posToMoveTo) const;

	private:
		// kinght can jump acroos other picese 
		virtual bool isMovingAcrossPieces(
			const ChessBoard& board,
			const unsigned int& rowToMoveFrom, const unsigned int& colToMoveFrom,
			const unsigned int& rowToMoveTo, const unsigned int& colToMoveTo) const;
	};

	class Bishop : public Piece
	{
	public:
		// C'TOR
		Bishop();

		virtual bool isCapableOfMoving(
			const ChessBoard& board,
			const std::string& posToMoveFrom,
			const std::string& posToMoveTo) const;

	private:
		virtual bool isMovingAcrossPieces(
			const ChessBoard& board,
			const unsigned int& rowToMoveFrom, const unsigned int& colToMoveFrom,
			const unsigned int& rowToMoveTo, const unsigned int& colToMoveTo) const;
	};

	class Queen : public Piece
	{
	public:
		// C'TOR
		Queen();

		virtual bool isCapableOfMoving(
			const ChessBoard& board,
			const std::string& posToMoveFrom,
			const std::string& posToMoveTo) const;

	private:
		// queen movment is part of bishop & rook momvent
		ChessPieces::Bishop _bishop;
		ChessPieces::Rook _rook;

		// The queen use this function throw the bishop or rook piece.
		virtual bool isMovingAcrossPieces(
			const ChessBoard& board,
			const unsigned int& rowToMoveFrom, const unsigned int& colToMoveFrom,
			const unsigned int& rowToMoveTo, const unsigned int& colToMoveTo) const;

	};

	class Pawn : public Piece
	{
	public:
		Pawn();

		virtual bool isCapableOfMoving(
			const ChessBoard& board,
			const std::string& posToMoveFrom,
			const std::string& posToMoveTo) const;

	private:

		// The pawn can move only one tile each time. (cannot move accros pieces)
		virtual bool isMovingAcrossPieces(
			const ChessBoard& board,
			const unsigned int& rowToMoveFrom, const unsigned int& colToMoveFrom,
			const unsigned int& rowToMoveTo, const unsigned int& colToMoveTo) const;
	};
}