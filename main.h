#pragma once

#include "Drawer.h"
#include <iostream>
#include <map>
#include <deque>

double Emin = 1.0;

/* COMMANDS */
typedef std::deque<std::string> deq;
typedef std::string str, (*fp)(deq);

str CMD_Print(deq arg);

str CMD_Draw(deq arg);

