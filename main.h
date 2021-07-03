#pragma once

#include <iostream>
#include <map>
#include <random>
#include "Drawer.h"

Complex offset(0, 20);

str path = "C:\\Users\\Gebruiker\\source\\repos\\FractalDrawer\\FractalDrawer\\data\\";
//str path = "C:\\Users\\lauwe\\source\\repos\\FractalDrawer\\FractalDrawer\\data\\";

str GetPathCoeff(int i)
{
	return path + "coeff\\segment_" + to_string(i) + ".txt";
}

str GetPathLeja(int i)
{
	return path + "leja\\segment_" + to_string(i) + ".txt";
}

std::vector<Complex> GetLejaPoints(str file);

std::vector<Complex> GetCoefficients(str file);

void LoadLejaPoints(int i);

void LoadCoefficients(int i);

void LoadLejaWithBoundary(int i);


/* COMMANDS */
str CMD_Draw(deq arg);

str CMD_Print(deq arg);

str CMD_SetN(deq arg);

str CMD_SetS(deq arg);

str CMD_Random(deq arg);

str CMD_Save(deq arg);

str CMD_Load(deq arg);

