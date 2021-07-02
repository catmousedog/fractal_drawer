#pragma once

#include <iostream>
#include <map>
#include "Drawer.h"

Complex offset(-5, 0);

//str path = "C:\\Users\\Gebruiker\\source\\repos\\FractalDrawer\\FractalDrawer\\data\\";
str path = "C:\\Users\\lauwe\\source\\repos\\FractalDrawer\\FractalDrawer\\data\\";

void LoadLejaPoints(str file, Complex offset);

void LoadCoefficients(str file, Complex offset);

/* COMMANDS */
str CMD_Draw(deq arg);

str CMD_Print(deq arg);

str CMD_SetN(deq arg);

str CMD_SetS(deq arg);

str CMD_Save(deq arg);

str CMD_Load(deq arg);

