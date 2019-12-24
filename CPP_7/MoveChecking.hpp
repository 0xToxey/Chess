#pragma once
#include "Player.hpp"
#include "Utils.hpp"

#define NUM_OF_PLAYERS 2
#define VALID_CHECK 0
#define CASE_2_INVALID 2
#define CASE_3_INVALID 3
#define CASE_6_INVALID 6


#define NUM_OF_PLAYERS 2
#define NUM_OF_TILES 8

/*
0 – מהלך תקין
1 – מהלך תקין, התבצעה תזוזה שגרמה שח על היריב
2 – מהלך לא תקין, במשבצת המקור אין כלי של השחקן הנוכחי
3 – מהלך לא תקין, במשבצת היעד קיים כלי של השחקן הנוכחי
4 – מהלך לא תקין, בעקבות התזוזה יגרם שח על השחקן הנוכחי
5 – מהלך לא תקין, אינדקסים של המשבצות אינם חוקיים*
6 – מהלך לא תקין, תזוזה לא חוקית של כלי7 – מהלך לא תקין, משבצת המקור ומשבצת היעד זהות
8 – מהלך תקין, התבצע שחמט!
*/

class MoveChecker
{
public:
	int checkMove(
		const Player(&players)[NUM_OF_PLAYERS],
		const std::string& positionToMoveFrom,
		const std::string& positionToMoveTo,
		const char(&board)[NUM_OF_TILES][NUM_OF_TILES]);
private:

	int case3(const char(&board)[NUM_OF_TILES][NUM_OF_TILES], const std::string& positionToMoveFrom, const std::string& positionToMoveTo);
	int case2(const char(&board)[NUM_OF_TILES][NUM_OF_TILES], const std::string& positionToMoveFrom);
	int case6(const std::string& positionToMoveFrom, const std::string& positionToMoveTo);

};
