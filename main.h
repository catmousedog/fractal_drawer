#pragma once

#include <iostream>
#include <map>
#include <random>
#include "Drawer.h"

bool Console = true;

double shift = 1;

std::vector<Complex> GetLejaPoints(str file);

std::vector<Complex> GetCoefficients(str file);

void LoadLejaPoints(int i, bool origin);

void LoadCoefficients(int i, bool origin);

void LoadLejaWithBoundary(int i, bool origin);


/* COMMANDS */
str CMD_Draw(deq arg);

str CMD_Print(deq arg);

str CMD_SetN(deq arg);

str CMD_SetS(deq arg);

str CMD_DrawPoints(deq arg);

str CMD_Random(deq arg);

str CMD_Save(deq arg);

str CMD_Load(deq arg);

str CMD_CalculateLeja(deq arg);

str CMD_Benchmark(deq arg);

str CMD_Console(deq arg);

