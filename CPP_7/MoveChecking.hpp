#pragma once
#include "Player.hpp"
#include "Pieces.hpp"
#include <string>

/*
0 – מהלך תקין
1 – מהלך תקין, התבצעה תזוזה שגרמה שח על היריב
V - 2 – מהלך לא תקין, במשבצת המקור אין כלי של השחקן הנוכחי
V - 3 – מהלך לא תקין, במשבצת היעד קיים כלי של השחקן הנוכחי
4 – מהלך לא תקין, בעקבות התזוזה יגרם שח על השחקן הנוכחי
5 – מהלך לא תקין, אינדקסים של המשבצות אינם חוקיים*
6 – מהלך לא תקין, תזוזה לא חוקית של כלי7 – מהלך לא תקין, משבצת המקור ומשבצת היעד זהות
8 – מהלך תקין, התבצע שחמט!
*/

class MoveChecker
{
public:
	MoveChecker();

	int checkMove(
		const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE],
		const Player(&players)[NUM_OF_PLAYERS],
		const std::string& positionToMoveFrom,
		const std::string& positionToMoveTo);
private:

	ChessPieces::Rook _rook;

	int case2(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& positionToMoveFrom, const bool& isWhite);
	int case3(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& positionToMoveFrom, const std::string& positionToMoveTo);
	int case6(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& positionToMoveFrom, const std::string& positionToMoveTo);
	int case7(const std::string& positionToMoveFrom, const std::string& positionToMoveTo);

};
