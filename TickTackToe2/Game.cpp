#include <random>
#include <iostream>
#include "Game.h"
#include "color.hpp"
int renderAux(std::string s, GameMap* gm)
{
	if (s.compare(gm->Player1) == 0)
		return 1;
	else if (s.compare(gm->Player2) == 0)
		return 2;
	else
		return 0;
}
void renderGameMap(GameMap* gm)
{
	std::cout << "\n";
	for (int i = 0; i < 3; i++)
	{
		std::cout << "\n\t";
		for (int j = 0; j < 3; j++)
		{
			std::string s = gm->GM[i][j];
			switch (renderAux(s, gm))
			{
			case 1:
				std::cout << dye::yellow("  ") << dye::green(s) << dye::yellow("  ");
				continue;
			case 2:
				std::cout << dye::yellow("  ") << dye::red(s) << dye::yellow("  ");
				continue;
			case 0:
				std::cout << dye::yellow("  ") << dye::yellow(s) << dye::yellow("  ");
				continue;
			default:
				std::cout << dye::yellow("  ") << dye::black_on_white(s) << dye::yellow("  ");
				continue;
			}
		}
	}
	std::cout << "\n";
}
int randomNumberGenerator(std::vector<int> possibleMovesList, int min, int max)
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(min, max); // define the range
	return distr(gen);

}
std::string swapPlayers(std::string  currentPlayer, GameMap* gm)
{
	if (currentPlayer.compare(gm->Player1) == 0)
	{
		return gm->Player2;
	}
	else
	{
		return gm->Player1;
	}
}
bool isPlayerWon(GameMap* gm)
{
	if (isWinCondition(gm) && gm->CurrentPlayer.compare(gm->Player1) == 0)
	{
		system("CLS");
		std::cout << "\n\tPlayer " << dye::green(gm->Player1) << " won!!!";
		renderGameMap(gm);
		return true;
	}
	else if (isWinCondition(gm) && gm->CurrentPlayer.compare(gm->Player2) == 0)
	{
		system("CLS");
		std::cout << "\n\tPlayer " << dye::red(gm->Player2) << " won!!!";
		renderGameMap(gm);
		return true;
	}
	else if (gm->maxPossibleMoves < 1)
	{
		system("CLS");
		std::cout << dye::yellow("\n\tDraw\n");
		return true;
	}
	return false;
}
int heuristicFunction(int move, GameMap gm,std::string player)
{
	makeMove(move, &gm, player);
	if (isWinCondition(&gm))
	{
		return 1;
	}
	return 0;
}

int minimax(int node, int depth, bool maximizingPlayer, GameMap gm)
{
	std::vector<int> possibleMoves = returnPossibleMove(&gm);
	if (depth == 0 || possibleMoves.size() <= 1)
	{
		//return possibleMoves[0]; // heuristic fuction goes here
		return heuristicFunction(node, gm,gm.CurrentPlayer);
	}
	if (maximizingPlayer)
	{
		int value = INT_MIN;
		for (int i : possibleMoves)
		{
			value = max(value, minimax(i, depth - 1, false, gm));
			return value;
		}
	}

	int value = INT_MAX;
	for (int i : possibleMoves)
	{
		value = min(value, minimax(i, depth - 1, true, gm));
		return value;
	}

	return -1;

}
void playVSPlayer(GameMap* gm)
{
	gm->CurrentPlayer = gm->Player2;
	std::string s;
	bool ReadyForNextPlayer;

	do
	{
		gm->CurrentPlayer = swapPlayers(gm->CurrentPlayer, gm);

		do
		{
			system("CLS");
			std::cout << "\n\tPlayer " << gm->CurrentPlayer << " to move";
			renderGameMap(gm);
			std::cout << "\n\tSelect a position to move\n";
			std::cin >> s;
			ReadyForNextPlayer = makeMove(std::stoi(s), gm, gm->CurrentPlayer);

		} while (!ReadyForNextPlayer);

		if (isPlayerWon(gm))
		{
			break;
		}

	} while (true);
}
void playVSEasyBot(GameMap* gm)
{
	gm->CurrentPlayer = gm->Player2;
	std::string s;
	bool ReadyForNextPlayer;

	do
	{
		gm->CurrentPlayer = swapPlayers(gm->CurrentPlayer, gm);
		do
		{
			system("CLS");
			std::cout << "\n\tPlayer " << gm->CurrentPlayer << " to move";
			renderGameMap(gm);
			std::cout << "\n\tSelect a position to move\n";
			std::cin >> s;
			ReadyForNextPlayer = makeMove(std::stoi(s), gm, gm->CurrentPlayer);

		} while (!ReadyForNextPlayer);

		if (isPlayerWon(gm))
		{
			break;
		}

		if (gm->maxPossibleMoves > 0)
		{
			gm->CurrentPlayer = swapPlayers(gm->CurrentPlayer, gm);
			int indexOfNextMove = randomNumberGenerator(returnPossibleMove(gm), 0, (int)returnPossibleMove(gm).size() - 1);
			std::vector<int> nextMoveList = returnPossibleMove(gm);
			makeMove(nextMoveList[indexOfNextMove], gm, gm->CurrentPlayer);
		}

		if (isPlayerWon(gm))
		{
			break;
		}

	} while (true);
}
void playVSHardBot(GameMap* gm)
{
	gm->CurrentPlayer = gm->Player2;
	std::string s;
	bool ReadyForNextPlayer;

	do
	{
		gm->CurrentPlayer = swapPlayers(gm->CurrentPlayer, gm);
		do
		{ // Begining player movement
			system("CLS");
			std::cout << "\n\tPlayer " << gm->CurrentPlayer << " to move";
			renderGameMap(gm);
			std::cout << "\n\tSelect a position to move\n";
			std::cin >> s;
			ReadyForNextPlayer = makeMove(std::stoi(s), gm, gm->CurrentPlayer);

		} while (!ReadyForNextPlayer); // Ending player movement

		if (isPlayerWon(gm))
		{
			break;
		}

		if (gm->maxPossibleMoves > 0) // Begining CPU movement
		{
			gm->CurrentPlayer = swapPlayers(gm->CurrentPlayer, gm);
			//int indexOfNextMove = minimax(std::stoi(s), 9, false, *gm);
			std::vector<int> nextMoveList = returnPossibleMove(gm);
			int indexOfNextMove = -1;
			for (int i : nextMoveList)
			{
				int aux = minimax(i, gm->maxPossibleMoves, true, *gm);
				indexOfNextMove = max(aux, indexOfNextMove);
			}
			makeMove(nextMoveList[indexOfNextMove], gm, gm->CurrentPlayer);
		} // Ending CPU movement

		if (isPlayerWon(gm))
		{
			break;
		}

	} while (true);
}