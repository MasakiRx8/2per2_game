// This header file define the using classes.

#ifndef GAME_CLASS_H
#define GAME_CLASS_H
#include <vector>

#define C 0
#define D 1

class Agent {
public:
	std::vector<int> strategy;	// store each agent strategy
	std::vector<double> gain;	// store each agent gain (payoff)
};

class Information {
public:
	int numberC;			// number of C agent
	int numberD;			// number of D agent
	double all_gain;		// total gain of all agents
};

class AI {
public:
	Agent agent;
	Information information;
};

#endif // !GAME_CLASS_H
