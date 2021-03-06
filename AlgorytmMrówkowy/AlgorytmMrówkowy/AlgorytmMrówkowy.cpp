// AlgorytmMrówkowy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <array>

#include "AntColony.h"

#define NODES	(int) 8

#define ANTS	(int) 2
#define ITERATIONS		(int) 4

#define ALPHA (double) 0.5	// =0 - przeszukiwanie stochastyczne + droga nieoptymalna
#define BETA (double) 0.8	// =0 - droga nieoptymalna
#define Q (double) 80		// Do szacowania podejrzewanej najlepszej trasy
#define OF (double) 0.2		// szybkość wyparowywania feromonów

using namespace std;

int main()
{
	int network [][NODES] = {{0,15,18,10,0,0,0,5}, {15,0,0,3,0,20,0,9},
							{18,0,0,0,11,9,13,0}, {10,3,0,0,3,0,0,0},
							{0,0,11,3,0,17,0,19}, {0,20,9,0,17,0,0,0},
							{0,0,13,0,0,0,0,20}, {5,9,0,0,19,0,20,0}};

	AntColony *ANT = new AntColony((int *)network, NODES, ANTS, ALPHA, BETA, Q, OF);
	
	ANT->getInformation();
	ANT->printInformation();

	ANT->initialize();
	ANT->drawGRAPH();
	
	ANT->setPheromones();
	ANT->printPheromones();

	ANT->antRelease(ITERATIONS);

	ANT->prtResults();
	ANT->prtLength();

	system("PAUSE");
	return 0;
}