#ifndef GameMapGuard
#define GameMapGuard
#pragma once
#include <string>
#include <iostream>
#include <vector>

class GameMap
{
public:
	const std::string Player1 = "G", Player2 = "R";
	std::string CurrentPlayer;
	std::string GM[3][3] =
	{
		{"0","1","2"},{"3","4","5"},{"6","7","8"}
	};
	int maxPossibleMoves = 9;
};
// 0 1 2
// 3 4 5
// 6 7 8
bool isPositionAlreadyPlayed(int pos, GameMap * gm);
bool isWinCondition(GameMap * gm);
bool makeMove(int pos, GameMap * gm, std::string player);
//void renderGameMap(GameMap * gm);
void resetGameMap(GameMap* gm);
std::vector<int> returnPossibleMove(GameMap * gm);

#endif // GameMapGuard