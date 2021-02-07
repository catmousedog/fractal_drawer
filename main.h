#pragma once

//whether the steps should always be forced downhill or not at all
bool ForceDownhill;
//the minimum cost before the poles can be worth wile saving
float MinCost;

//train the position of one pole
void TrainPosOne(int i);
//train the position of all poles
void TrainPosAll();
//train the exponent of one pole
void TrainPowerOne();
//train the exponenet of all poles
void TrainPowerAll();
//train both the position and exponent of one pole
void TrainAllOne();
//train both the position and exponent of all poles
void TrainAllAll();


//void Train(int, bool, int, float);
//void FindMinimum(int, bool, int, float);
//void Walk(int, bool, int);
//void FindRandom(int, float);
//void Benchmark(int M);