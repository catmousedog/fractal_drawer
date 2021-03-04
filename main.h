#pragma once

#include "Drawer.h"
#include "Randomizer.h"
#include <iostream>
#include <map>
#include <deque>

double Emin = 1.0;

/* COMMANDS */
typedef std::deque<std::string> deq;
typedef std::string str, (*fp)(deq);

str CMD_Step(deq arg);

str CMD_Pole(deq arg);

str CMD_Random(deq arg);

str CMD_Iterate(deq arg);

str CMD_Descend(deq arg);

str CMD_DescendM(deq arg);

str CMD_Train(deq arg);

str CMD_Print(deq arg);

str CMD_Draw(deq arg);

/* FUNCTIONS */

//gradient descent
//A different random initial points
//initial points are chosen out of R random points each time
//maximum of M descends for each chosen point before termination
void Train(int A, int R, int M);

//descend M times
//returns false if nothing changed
bool DescendM(int M);

//descend once
//returns false if nothing changed
int Descend(int terminate);

void Print(double E);

void Benchmark();