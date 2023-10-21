#include "GameMap.h"
//#include "color.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <stdlib.h>

bool isWinConditionHorizontal(std::string matrix[][3])
{
	for (int i = 0; i < 3; i++)
	{
		if (matrix[i][0].compare(matrix[i][1]) == 0 && matrix[i][0].compare(matrix[i][2]) == 0)
		{
			return true;
		}
	}
	return false;
}
bool isWinConditionVertical(std::string matrix[][3])
{
	for (int i = 0; i < 3; i++)
	{
		if (matrix[0][i].compare(matrix[1][i]) == 0 && matrix[0][i].compare(matrix[2][i]) == 0)
		{
			return true;
		}
	}
	return false;
}
bool isWinConditionDiagonal(std::string matrix[][3])
{
	if (matrix[0][0].compare(matrix[1][1]) == 0 && matrix[0][0].compare(matrix[2][2]) == 0)
	{
		return true;
	}
	if (matrix[2][0].compare(matrix[1][1]) == 0 && matrix[2][0].compare(matrix[0][2]) == 0)
	{
		return true;
	}
	return false;
}
bool isWinCondition(std::string matrix[][3])
{
	return (isWinConditionHorizontal(matrix) || isWinConditionVertical(matrix) || isWinConditionDiagonal(matrix));
}
bool isWinCondition(GameMap * gm)
{
	return isWinCondition(gm->GM);
}
bool isPositionAlreadyPlayed(int pos, GameMap * gm)
{
	switch (pos)
	{
	case 0:
	case 1:
	case 2:
		return (gm->GM[0][pos%3].compare(gm->Player1) == 0 || gm->GM[0][pos%3].compare(gm->Player2) == 0);
	case 3:
	case 4:
	case 5:
		pos -= 3;
		return (gm->GM[1][pos%3].compare(gm->Player1) == 0 || gm->GM[1][pos%3].compare(gm->Player2) == 0);
	case 6:
	case 7:
	case 8:
		
		return (gm->GM[2][pos%3].compare(gm->Player1) == 0 || gm->GM[2][pos%3].compare(gm->Player2) == 0);
	default:
		return false;
	}
}
bool makeMove(int pos, GameMap * gm, std::string player)
{
	if (!isPositionAlreadyPlayed(pos, gm))
	{
		switch (pos)
		{
		case 0:
		case 1:
		case 2:
			gm->GM[0][pos%3] = player;
			gm->maxPossibleMoves--;
			return true;
		case 3:
		case 4:
		case 5:
			gm->GM[1][pos%3] = player;
			gm->maxPossibleMoves--;
			return true;
		case 6:
		case 7:
		case 8:
			gm->GM[2][pos%3] = player;
			gm->maxPossibleMoves--;
			return true;
		default:
			return false;
		}
	}
	return false;
}
void resetGameMap(GameMap * gm)
{
	std::string newGM[3][3] =
	{
		{"0","1","2"},{"3","4","5"},{"6","7","8"}
	};

	for (int i = 0; i < 3; i++)
	{
		gm->GM[i][0] = newGM[i][0];
		gm->GM[i][1] = newGM[i][1];
		gm->GM[i][2] = newGM[i][2];
	}

	gm->maxPossibleMoves = 9;
}
std::vector<int> returnPossibleMove(GameMap * gm)
{
	std::vector<int> possibleMoves;
	for (int i = 0; i < 9; i++)
	{
		if (!isPositionAlreadyPlayed(i, gm))
		{
			possibleMoves.push_back(i);
		}
	}
	return possibleMoves;
}
