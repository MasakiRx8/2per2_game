#ifndef STRATEGY_UPDATE_H
#define STRATEGY_UPDATE_H
#include <vector>
#include <iostream>
#include "random.h"
#include "game_class.h"

void initial_strategy_setting(int N, AI* ai);
void strategy_updating_GC(int N, AI* ai);

void initial_strategy_setting(int N, AI* ai) {
// This function initialize parameters and ratio of strategy.
	// **** initial setting parameters ****
	ai->agent.strategy = std::vector<int>(N, D);	// all agent's strategy is D
	ai->agent.gain = std::vector<double>(N, 0);		// all agent's gain is 0
	ai->information.numberC = 0;					// C strategy agent is nothing, therefore number of C agent is 0
	ai->information.numberD = N;					// all agent's strategy is D, therefore number of D agent is N
	ai->information.all_gain = 0;					// all agent's gain is 0, therefore all gain is 0
	// ------------------------------------

	// **** initial setting agent's strategy ****
	// ratio of strategy is half and half. C:D = 50% : 50%
	std::vector<int> remainig_people(N);
	for (int i = 0; i < N; i++) remainig_people[i] = i;
	while (ai->information.numberC != ai->information.numberD) {
		// **** choose a agent who will change strategy D to C ****
		int rem_size = remainig_people.size();
		int xrem = random(rem_size - 1);
		int number = remainig_people[xrem];						// choosen agent's number ( This agnet strategy is changed D to C ) 
		remainig_people.erase(remainig_people.begin() + xrem);	// We can be avoided to choose the same agent twice, because choosen agent's number is daleated from "remaining_people".
		// --------------------------------------------------------

		// **** chnage the strategy D to C ****
		ai->agent.strategy[number] = C;
		ai->information.numberC++;
		ai->information.numberD--;
		// ------------------------------------
	}
	// -------------------------------------------
}

void strategy_updating_GC(int N, AI* ai) {
// This function update agent's strategy with GC.
	std::vector<int> next_strategy(N);
	ai->information.numberC = 0;
	ai->information.numberD = 0;
	for (int number = 0; number < N; number++) {	// number means focal agnet's number
		double x = random(1.0);
		double probability = 0;
		// **** start the roulette ****
		for (int i = 0; i < N; i++) {
			probability += ai->agent.gain[i] / ai->information.all_gain;
			if (x <= probability) {
				if (ai->agent.strategy[i] == C) {
					next_strategy[number] = C;
					ai->information.numberC++;
				}
				else {
					next_strategy[number] = D;
					ai->information.numberD++;
				}
				break;
			}
		}
		// ----------------------------
	}
	ai->agent.strategy = next_strategy;
}

#endif // !STRATEGY_UPDATE_H

