// This heder file caluclate payoff for each agent.
// This means that two agents who is randomly chosen are fighted and calculation the score along the payoff matrix.

//   opponent side strategy
//        C | D 
// f  ----------
// o  C | R | T |
// c  D | S | P |
// l  

#ifndef GAME_H
#define GAME_H
#include <vector>
#include "random.h"
#include "game_class.h"

struct List {
	int one;
	int two;
};

void two_per_two_game(int N, double Dg, double Dr, AI* ai) {
// This function calculates the agent's gain
	std::vector<int> remaining_people(N);
	for (int i = 0; i < N; i++) remaining_people[i] = i;
	ai->information.all_gain = 0;
	while (remaining_people.size() > 0) {
		List list;							// store selected two people
		// **** choose two people ****
		for (int i = 0; i < 2; i++) {
			int rem_size = remaining_people.size();
			int xrem = random(rem_size - 1);
			int number = remaining_people[xrem];
			remaining_people.erase(remaining_people.begin() + xrem);
			if (i == 0) list.one = number;
			else list.two = number;
		}
		// ---------------------------

		// **** make them fight with the two people chosen ****
		// R = 2.0, T = 2.0 + Dg, S = 1.0 - Dr, P = 1.0
		if (ai->agent.strategy[list.one] == C) {
			if (ai->agent.strategy[list.two] == C) {
				// in this case, both agents are R
				ai->agent.gain[list.one] = 2;
				ai->agent.gain[list.two] = 2;
			}
			else {
				// in this case, agnet one is S and agent two is T
				ai->agent.gain[list.one] = 1 - Dr;
				ai->agent.gain[list.two] = 2 + Dg;
			}
		}
		else {
			if (ai->agent.strategy[list.two] == C) {
				// in this case, agent one is T and agent two is S
				ai->agent.gain[list.one] = 2 + Dg;
				ai->agent.gain[list.two] = 1 - Dr;
			}
			else {
				// in this case, both agents are P
				ai->agent.gain[list.one] = 1;
				ai->agent.gain[list.two] = 1;
			}
		}
		// -----------------------------------------------------
		ai->information.all_gain += ai->agent.gain[list.one];
		ai->information.all_gain += ai->agent.gain[list.two];
	}
}

#endif // !GAME_H

