// AlgorytmGenetyczny.cpp: definiuje punkt wejścia dla aplikacji konsolowej.
//

#include "stdafx.h"
#include <iostream>

#include "Gens.h"

#define NODES		(int) 8		//Ilość miast/węzłów
#define ITERATIONS	(int) 4		//Ilość iteracji(czyli procesów powstawania nowych dzieci)
#define CHILDS		(int) 10	//Ilość dzieci(niekoniecznie poprawnych) w danej iteracji

#define MUT			(int) 10	//Możliwość mutacji danego genu w procentach

using namespace std;

int main()
{
	int network[][NODES] = { { 0,15,18,10,0,0,0,5 },{ 15,0,0,3,0,20,0,9 },
							{ 18,0,0,0,11,9,13,0 },{ 10,3,0,0,3,0,0,0 },
							{ 0,0,11,3,0,17,0,19 },{ 0,20,9,0,17,0,0,0 },
							{ 0,0,13,0,0,0,0,20 },{ 5,9,0,0,19,0,20,0 } };

	Gens *gen = new Gens((int *)network, NODES, CHILDS, MUT);

	gen->drawGRAPH();

	gen->initialize();
	gen->setParents();

	gen->makeNewPaths(ITERATIONS);

	cout << endl << endl;

	gen->printBestRoute();

	system("PAUSE");
	return 0;
}

