#include "Utils.hpp"
#include <tuple>
#include <cctype>

/*
function converts from position string(ex: e2)
to array index(ex: <1,4>)
*/
std::tuple<unsigned int, unsigned int> Utils::positionStringToIndex(const std::string& position)
{
	// conversion from e2 to <1, 4>
	return std::make_tuple(position[1] - ASCII_NUMBER_CONVERT - 1, position[0] - ASCII_LETTER_CONVERT - 1);
}

/*
function converts from array index(ex: <1,4>)
to position string(ex: ew)
*/
std::string Utils::positionIndexToString(const std::tuple <const unsigned int, const unsigned int>& positionInt)
{
	// conversion from <1, 4> to e2
	std::string position;
	position += static_cast<char>(std::get<1>(positionInt) + ASCII_LETTER_CONVERT + 1); // ex: e
	position += static_cast<char>(std::get<0>(positionInt) + ASCII_NUMBER_CONVERT + 1); // ex: 2

	return position;
}

/*
function returns the index of the player whose turn is
*/
unsigned int Utils::WhoseTurnIsIt(const Player(&players)[NUM_OF_PLAYERS])
{
	for (unsigned int i = 0; i < NUM_OF_PLAYERS; i++)
	{
		if (players[i].isPlayerTurn())
		{
			return i;
		}
	}
}
