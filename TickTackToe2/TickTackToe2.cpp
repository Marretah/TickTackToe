// TickTackToe2.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "Game.h"
#include <stdlib.h>
int main()
{
    GameMap gm;
    std::cout << "Tick Tack Toe game\n\t1- PVP\n\t2-PV Easy\n\t3- PV Hard\n\t4- Exit";
    std::string s;
    std::cin >> s;
    switch (stoi(s))
    {
    case 1:
        playVSPlayer(&gm);
        break;
    case 2:
        playVSEasyBot(&gm);
        break;
    case 3:
        playVSHardBot(&gm);
        break;
    case 4:
        return -1;
    default:
        return -1;
    }
    system("pause");
}
