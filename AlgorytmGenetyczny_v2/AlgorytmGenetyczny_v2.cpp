// AlgorytmGenetyczny_v2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "components.h"
#include "Gens.h"
#include "customFunctions.h"

#define NODES		(int) 4			//Ilość miast/węzłów
#define ITERATIONS	(int) 3			//Ilość iteracji(czyli procesów powstawania nowych dzieci)
#define CHILDS		(int) 10		//Ilość dzieci(niekoniecznie poprawnych) w danej iteracji

#define MUT			(int) 2			//Możliwość mutacji danego genu w procentach
#define DIMENSION	(int) 6			//DIMENSION = (NODES*(NODES - 1)) / 2
#define PROTECTION	(bool) false	//jeśli jest jakakolwiek protekcja to true, inaczej false

int main()
{
	int cost = 0;
	int risk = 0;	
	int toReproduction[ITERATIONS][DIMENSION][DIMENSION][NODES];
	
	double parentsToReproduce[DIMENSION][2];
	double resultArr[DIMENSION];
	double sum = 0.0;
	double riskInOneYear[10000];
	double tmax = 12 * 30 * 24 * 3600;
	double thr = 1 / ((2.3 * 60) / (2.3 - 1));

	int network[][NODES] = { { 0,1,1,0 },{ 1,0,1,1 },{ 1,1,0,1 },{ 0,1,1,0 } };
	int backupNetwork[][NODES] = { { 0,1,1,0 },{ 1,0,1,1 },{ 1,1,0,1 },{ 0,1,1,0 } };
	int alwaysNew[][NODES] = { { 0,1,1,0 },{ 1,0,1,1 },{ 1,1,0,1 },{ 0,1,1,0 } };
	int demands[DIMENSION][3] = { { 0,1,60 },{ 0,2,128 },{ 0,3,30 },
								{ 1,2,103 },{ 1,3,195 },
								{ 2,3,150 } };
								
	//int demands[DIMENSION][3] = { { 0,3,60 } };

	/*int network[][NODES] = { { 0,1,0,1,0,1,0,1 },{ 1,0,1,0,1,0,1,0 },{ 0,1,0,1,0,1,0,1 },{ 1,0,1,0,1,0,1,0 },
	{ 0,1,0,1,0,1,0,1 },{ 1,0,1,0,1,0,1,0 },{ 0,1,0,1,0,1,0,1 },{ 1,0,1,0,1,0,1,0 } };
	int backupNetwork[][NODES] = { { 0,1,0,1,0,1,0,1 },{ 1,0,1,0,1,0,1,0 },	{ 0,1,0,1,0,1,0,1 },{ 1,0,1,0,1,0,1,0 },
	{ 0,1,0,1,0,1,0,1 },{ 1,0,1,0,1,0,1,0 },{ 0,1,0,1,0,1,0,1 },{ 1,0,1,0,1,0,1,0 } };
	int alwaysNew[][NODES] = { { 0,1,0,1,0,1,0,1 },{ 1,0,1,0,1,0,1,0 },	{ 0,1,0,1,0,1,0,1 },{ 1,0,1,0,1,0,1,0 },
	{ 0,1,0,1,0,1,0,1 },{ 1,0,1,0,1,0,1,0 },{ 0,1,0,1,0,1,0,1 },{ 1,0,1,0,1,0,1,0 } };
	int demands[DIMENSION][3] = { { 0,1,118 },{ 0,2,124 },{ 0,3,70 },{ 0,4,178 },{ 0,5,101 },{ 0,6,113 },{ 0,7,65 },
	{ 1,2,186 },{ 1,3,146 },{ 1,4,136 },{ 1,5,56 },{ 1,6,113 },{ 1,7,156 },
	{ 2,3,137 },{ 2,4,195 },{ 2,5,156 },{ 2,6,145 },{ 2,7,185 },
	{ 3,4,141 },{ 3,5,197 },{ 3,6,166 },{ 3,7,61 },
	{ 4,5,186 },{ 4,6,97 },{ 4,7,129 },
	{ 5,6,68 },{ 5,7,143 },
	{ 6,7,76 } };
	*/
	/*	int network[][NODES] = { { 0,0,1,0,0,1,0,0,0,0,1,0 },{ 0,0,1,0,0,0,0,1,0,0,1,0 },{ 1,1,0,0,0,0,0,0,0,1,0,0 },{ 0,0,0,0,1,0,1,0,0,0,0,1 },
	{ 0,0,0,1,0,0,0,0,1,0,1,0 },{ 1,0,0,0,0,0,0,0,1,0,1,0 },{ 0,0,0,1,0,0,0,0,0,0,1,1 },{ 0,1,0,0,0,0,0,0,0,1,0,1 },
	{ 0,0,0,0,1,1,0,0,0,0,0,0 },{ 0,0,1,0,0,0,0,1,0,0,0,0 },{ 1,1,0,0,1,1,1,0,0,0,0,0 },{ 0,0,0,1,0,0,1,1,0,0,0,0 } };
	int backupNetwork[][NODES] = { { 0,0,1,0,0,1,0,0,0,0,1,0 },{ 0,0,1,0,0,0,0,1,0,0,1,0 },{ 1,1,0,0,0,0,0,0,0,1,0,0 },{ 0,0,0,0,1,0,1,0,0,0,0,1 },
	{ 0,0,0,1,0,0,0,0,1,0,1,0 },{ 1,0,0,0,0,0,0,0,1,0,1,0 },{ 0,0,0,1,0,0,0,0,0,0,1,1 },{ 0,1,0,0,0,0,0,0,0,1,0,1 },
	{ 0,0,0,0,1,1,0,0,0,0,0,0 },{ 0,0,1,0,0,0,0,1,0,0,0,0 },{ 1,1,0,0,1,1,1,0,0,0,0,0 },{ 0,0,0,1,0,0,1,1,0,0,0,0 } };
	int alwaysNew[][NODES] = { { 0,0,1,0,0,1,0,0,0,0,1,0 },{ 0,0,1,0,0,0,0,1,0,0,1,0 },{ 1,1,0,0,0,0,0,0,0,1,0,0 },{ 0,0,0,0,1,0,1,0,0,0,0,1 },
	{ 0,0,0,1,0,0,0,0,1,0,1,0 },{ 1,0,0,0,0,0,0,0,1,0,1,0 },{ 0,0,0,1,0,0,0,0,0,0,1,1 },{ 0,1,0,0,0,0,0,0,0,1,0,1 },
	{ 0,0,0,0,1,1,0,0,0,0,0,0 },{ 0,0,1,0,0,0,0,1,0,0,0,0 },{ 1,1,0,0,1,1,1,0,0,0,0,0 },{ 0,0,0,1,0,0,1,1,0,0,0,0 } };
	int demands[DIMENSION][3] = {{0,1,195}, {0,2,158}, {0,3,174}, {0,4,101}, {0,5,198}, {0,6,158}, {0,7,182}, {0,8,154}, {0,9,175}, {0,10,122}, {0,11,114},
	{1,2,179}, {1,3,117}, {1,4,105}, {1,5,159}, {1,6,198}, {1,7,189}, {1,8,166}, {1,9,142}, {1,10,137}, {1,11,163},
	{2,3,131}, {2,4,159}, {2,5,164}, {2,6,128}, {2,7,195}, {2,8,130}, {2,9,105}, {2,10,173}, {2,11,157},
	{3,4,194}, {3,5,125}, {3,6,110}, {3,7,132}, {3,8,159}, {3,9,109}, {3,10,126}, {3,11,100},
	{4,5,124}, {4,6,106}, {4,7,136}, {4,8,144}, {4,9,168}, {4,10,119}, {4,11,127},
	{5,6,105}, {5,7,147}, {5,8,140}, {5,9,198}, {5,10,104}, {5,11,113},
	{6,7,169}, {6,8,187}, {6,9,196}, {6,10,193}, {6,11,151},
	{7,8,106}, {7,9,125}, {7,10,194}, {7,11,194},
	{8,9,123}, {8,10,181}, {8,11,193},
	{9,10,181}, {9,11,195},
	{10,11,141}};
	*/

	vector<shared_ptr<Component>> net;
	random_device rd;
	mt19937 psuedoGen(rd());
	exponential_distribution<double> exp_d(0.000000318);	//intensywność awarii, trzeba sobie odpowiednio dobrać
	pareto_distribution pareto_d = pareto_distribution(2.3, 60);

	for (int i = 0; i < NODES; i++) {
		for (int j = i; j < NODES; j++) {
			if (network[i][j] > 0) {
				net.push_back(make_component(psuedoGen, exp_d, pareto_d));
			}
		}
	}

	for (int l = 0; l < ITERATIONS; l++) {
		for (int i = 0; i < DIMENSION; i++) {
			for (int j = 0; j < DIMENSION; j++) {
				for (int k = 0; k < NODES; k++) {
					toReproduction[l][i][j][k] = -1;
				}
			}
		}
	}

	for (int parent = 0; parent < DIMENSION; parent++) {

		vector<Sla> slas;
		auto postEvent = [&](double tt) {
			for_each(slas.begin(), slas.end(),
				[&](Sla& rsla) {
				rsla.onEvent(tt);
			});
		};

		cost = 0;

		vector<shared_ptr<StatsColector>> stats;
		//slas.useSBPP = 1;

		for (int i = 0; i < DIMENSION; i++) {
			Sla ret;

			Gens *gen = new Gens((int *)network, NODES, CHILDS, MUT, demands[i][0], demands[i][1]);
			gen->initialize();
			gen->setParents();
			gen->makeNewPaths(ITERATIONS);
			gen->abcd((int *)backupNetwork);

			for (int k = 0; k < NODES; k++) {
				toReproduction[0][parent][i][k] = gen->bestRoute[k];
				if (gen->bestRoute[k] == demands[i][1]) break;
				else {
					cost += (demands[i][2] * network[gen->bestRoute[k]][gen->bestRoute[k + 1]]);
					//network[gen->bestRoute[k]][gen->bestRoute[k + 1]] = 0;
					//[gen->bestRoute[k + 1]][gen->bestRoute[k]] = 0;
				}
				if (gen->PATH[k] != -1) {
					ret.path.push_back(net[k]);
				}
			}

			for (int i = 0; i < NODES; i++) {
				for (int j = 0; j < NODES; j++) {
					network[i][j] = alwaysNew[i][j];
					backupNetwork[i][j] = alwaysNew[i][j];
				}
			}

			int ii = 0;
			int ii2 = 0;
			shared_ptr<StatsColector> tmptr;
			auto p = make_policy(Avail(), "Avail");
			//auto p = make_policy(NonLinear(demands[i][2]/thr, 0.0, 0.0), "Snowball");
			createColectors(ret, p, tmptr, ii, ii2, 0, 0, stats);
			slas.push_back(ret);
		
		}

		cout << "Koszt sieci:: " << cost << endl;

		double t = 0.0;
		string strParent = to_string(parent);
		string fileName = "AlgGenAvail_par" + strParent + '.' + "txt";
		std::map<std::string, std::string> argsmap;  
		std::ofstream file(fileName, std::ios::out | std::ios::trunc);
		{
			std::stringstream ss;
			ss << fileName << ".lbl";
			std::ofstream lblfile(ss.str(), std::ios::out | std::ios::trunc);

			auto iter = stats.begin();
			for (;;)
			{
				(*iter)->writeName(lblfile);
				if (++iter == stats.end())
				{
					lblfile << endl;
					break;
				}
				lblfile << endl;
			}
		}

		double var;
		int year, nn;
		int N = 10000;
		for (int year = 0; year < N; year++) {
			riskInOneYear[year] = 0;
		}
		year = 0;
		nn = 0;

		for (int iteration = 0; iteration < N; ++iteration) {
			t = 0.0;
			for_each(stats.begin(), stats.end(), [](shared_ptr<StatsColector>& a) {a->reset(); });
			for_each(net.begin(), net.end(), [&](shared_ptr<Component>& a) {a->reset(psuedoGen);  });

			while (t < tmax) {
				postEvent(t);
				auto it = min_element(net.begin(), net.end(), [&](const shared_ptr<Component>& a, const shared_ptr<Component>& b)-> bool {return a->time2switch < b->time2switch; });
				auto t2s = (*it)->time2switch;
				t += t2s;
				for (auto i = net.begin(); i != net.end(); ++i) {
					if (i == it)
						(*i)->change(psuedoGen);
					else
						(*i)->time2switch -= t2s;
				}
			}
			t = tmax;

			postEvent(t);

			auto iter = stats.begin();
			for (;;) {
				(*iter)->writeStats(&var);
				file << var;
				riskInOneYear[year] += var;
				if (PROTECTION) {
					if (nn % 2 == 0) riskInOneYear[year] -= var;
					nn++;
				}
				if (++iter == stats.end()) {
					file << endl;
					year++;
					nn = 0;
					break;
				}
				file << ",";
			}
		}

		double result95th = 0.0;
		result95th = percentile95th(riskInOneYear, N);

		//cout << "95th per::" << result95th << endl;
		//cout << "Cost::" << cost << endl;
		//cout << "Aaa:::" << cost * 10 / (cost * 10 + result95th) << endl << endl;
		sum = 10 * cost + result95th;
		cout << sum << endl;

		parentsToReproduce[parent][0] = parent;
		parentsToReproduce[parent][1] = sum;
		resultArr[parent] = sum;
	}

	*resultArr = *getBestNParents(resultArr, DIMENSION);

	for (int i = 0; i < DIMENSION; i++) cout << "Wynik numer " << i+1 << ":" << resultArr[i] << endl;
	cout << endl << endl;
	for (int i = 0; i < DIMENSION; i++) {
		cout << parentsToReproduce[i][0] << ": " << parentsToReproduce[i][1] << endl;
	}

	/******POCZĄTEK TWORZENIA POTOMSTWA********/
	for (int i = 1; i < ITERATIONS; i++) {
		int parent = 0;
		for (int p1 = 0; p1 < NODES - 1; p1++) {
			for (int p2 = p1 + 1; p2 < NODES; p2++) {
				
				int firstParentPosition, secondParentPosition;
				double firstParent = resultArr[p1];
				double secondParent = resultArr[p2];

				for (int w = 0; w < DIMENSION; w++) {
					if (parentsToReproduce[w][1] == firstParent) {
						firstParentPosition = parentsToReproduce[w][0];
						break;
					}
				}

				for (int w = 0; w < DIMENSION; w++) {
					if (parentsToReproduce[w][1] == secondParent) {
						secondParentPosition = parentsToReproduce[w][0];
						break;
					}
				}

				vector<Sla> slas;
				auto postEvent = [&](double tt) {
					for_each(slas.begin(), slas.end(),
						[&](Sla& rsla) {
						rsla.onEvent(tt);
					});
				};

				cost = 0;
				vector<shared_ptr<StatsColector>> stats;


				for (int d = 0; d < DIMENSION; d++) {
					Sla ret;

					Gens *gen = new Gens((int *)network, NODES, CHILDS, MUT, demands[d][0], demands[d][1]);
					gen->initialize();
					gen->parentsFromPreviousIteration(toReproduction[i-1][firstParentPosition][d], toReproduction[i - 1][secondParentPosition][d]);
					gen->makeNewPaths(ITERATIONS);
					gen->abcd((int *)backupNetwork);

					for (int k = 0; k < NODES; k++) {
						toReproduction[i][parent][d][k] = gen->bestRoute[k];
						if (gen->bestRoute[k] == demands[d][1]) break;
						else {
							cost += (demands[d][2] * network[gen->bestRoute[k]][gen->bestRoute[k + 1]]);
							//network[gen->bestRoute[k]][gen->bestRoute[k + 1]] = 0;
							//[gen->bestRoute[k + 1]][gen->bestRoute[k]] = 0;
						}
						if (gen->PATH[k] != -1) {
							ret.path.push_back(net[k]);
						}
					}

					for (int n = 0; n < NODES; n++) {
						for (int j = 0; j < NODES; j++) {
							network[n][j] = alwaysNew[n][j];
							backupNetwork[n][j] = alwaysNew[n][j];
						}
					}

					int ii = 0;
					int ii2 = 0;
					shared_ptr<StatsColector> tmptr;
					auto p = make_policy(Avail(), "Avail");
					//auto p = make_policy(NonLinear(demands[i][2]/thr, 0.0, 0.0), "Snowball");
					createColectors(ret, p, tmptr, ii, ii2, 0, 0, stats);
					slas.push_back(ret);
				}
				cout << "Koszt sieci:: " << cost << endl;

				double t = 0.0;
				string strParent = to_string(parent);
				string iterNum = to_string(i);
				string fileName = "AlgGenAvail_par" + strParent + "Iter_" + iterNum + '.' + "txt";
				std::map<std::string, std::string> argsmap;
				std::ofstream file(fileName, std::ios::out | std::ios::trunc);
				{
					std::stringstream ss;
					ss << fileName << ".lbl";
					std::ofstream lblfile(ss.str(), std::ios::out | std::ios::trunc);

					auto iter = stats.begin();
					for (;;)
					{
						(*iter)->writeName(lblfile);
						if (++iter == stats.end())
						{
							lblfile << endl;
							break;
						}
						lblfile << endl;
					}
				}

				double var;
				int year, nn;
				int N = 10000;
				for (int year = 0; year < N; year++) {
					riskInOneYear[year] = 0;
				}
				year = 0;
				nn = 0;

				for (int iteration = 0; iteration < N; ++iteration) {
					t = 0.0;
					for_each(stats.begin(), stats.end(), [](shared_ptr<StatsColector>& a) {a->reset(); });
					for_each(net.begin(), net.end(), [&](shared_ptr<Component>& a) {a->reset(psuedoGen);  });

					while (t < tmax) {
						postEvent(t);
						auto it = min_element(net.begin(), net.end(), [&](const shared_ptr<Component>& a, const shared_ptr<Component>& b)-> bool {return a->time2switch < b->time2switch; });
						auto t2s = (*it)->time2switch;
						t += t2s;
						for (auto i = net.begin(); i != net.end(); ++i) {
							if (i == it)
								(*i)->change(psuedoGen);
							else
								(*i)->time2switch -= t2s;
						}
					}
					t = tmax;

					postEvent(t);

					auto iter = stats.begin();
					for (;;) {
						(*iter)->writeStats(&var);
						file << var;
						riskInOneYear[year] += var;
						if (PROTECTION) {
							if (nn % 2 == 0) riskInOneYear[year] -= var;
							nn++;
						}
						if (++iter == stats.end()) {
							file << endl;
							year++;
							nn = 0;
							break;
						}
						file << ",";
					}
				}

				double result95th = 0.0;
				result95th = percentile95th(riskInOneYear, N);

				//cout << "95th per::" << result95th << endl;
				//cout << "Cost::" << cost << endl;
				//cout << "Aaa:::" << cost * 10 / (cost * 10 + result95th) << endl << endl;
				sum = 10 * cost + result95th;
				cout << sum << endl;

				parentsToReproduce[parent][0] = parent;
				parentsToReproduce[parent][1] = sum;
				resultArr[parent] = sum;
				parent++;
			}
		}
		*resultArr = *getBestNParents(resultArr, DIMENSION);

		for (int i = 0; i < DIMENSION; i++) cout << "Wynik numer " << i + 1 << ":" << resultArr[i] << endl;
		cout << endl << endl;
		for (int i = 0; i < DIMENSION; i++) {
			cout << parentsToReproduce[i][0] << ": " << parentsToReproduce[i][1] << endl;
		}
	}

	system("PAUSE");
    return 0;
}

