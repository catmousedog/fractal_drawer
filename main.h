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

str Step(deq arg);

str Random(deq arg);

str Iterate(deq arg);

str Descend(deq arg);

str DescendM(deq arg);

str Train(deq arg);

str Print(deq arg);

str Draw(deq arg);

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
bool Descend();

//descend a single pole once
//calls Iterate() and Energy()
//returns false if nothing changed
bool Descend(int i);

void Print(double E);