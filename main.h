#pragma once

#include <iostream>
#include <map>
#include "Drawer.h"

void LoadLejaPoints(str file);

void LoadCoefficients(str file);

/* COMMANDS */
str CMD_Print(deq arg);

str CMD_SetN(deq arg);

str CMD_setS(deq arg);
