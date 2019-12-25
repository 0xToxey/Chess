#pragma once

#include "constants.hpp"
#include "Player.hpp"
#include <iostream>

std::tuple<unsigned int, unsigned int> positionStringToInt(const std::string& position);
PieceColor getColorOfPieceByPosition(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& position);
unsigned int checkPlayerTurn(const Player(&players)[NUM_OF_PLAYERS]);
PieceType getTypeOfPieceByPosition(const char(&board)[TILES_PER_SIDE][TILES_PER_SIDE], const std::string& position);
