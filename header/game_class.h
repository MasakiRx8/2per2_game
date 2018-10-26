#ifndef GAME_CLASS_H
#define GAME_CLASS_H
#include <vector>

#define C 0
#define D 1

class Agent {
public:
	std::vector<int> strategy;
	std::vector<double> gain;
};

class Information {
public:
	int numberC;
	int numberD;
	double all_gain;
};

class AI {
public:
	Agent agent;
	Information information;
};

#endif // !GAME_CLASS_H
