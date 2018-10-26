#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "./header/random.h"
#include "./header/sort.h"
#include "./header/game_class.h"
#include "./header/game.h"
#include "./header/strategy_update.h"

using namespace std;

#define ensemble 100
#define measurement_cycle 100

// Convergence condition: When the average cooperation rate is calculated every 100 seasons,
// when the value does not change from the average value in the previous 100 seasons.

double game_function(int N, double Dg, double Dr) {
	AI ai;
	double Fc = 0;
	for (int n = 1; n <= ensemble; n++) {
		double current_fc = 0;
		double last_fc = 0;
		initial_strategy_setting(N, &ai);
		bool fg = false;
		int year = 1;
		while (fg == false) {
			two_per_two_game(N, Dg, Dr, &ai);
			strategy_updating_GC(N, &ai);
			double fc = double(ai.information.numberC) / double(N);
			cout << year << " " << Dg << " " << Dr << " " << fc << endl;
			current_fc += fc;
			if (year%measurement_cycle == 0) {
				current_fc /= double(measurement_cycle);
				if (abs(current_fc - last_fc) < 0.01) {
					cout << n << " : Dg = " << Dg << " Dr = " << Dr << " Fc = " << current_fc << endl;
					Fc += current_fc;
					fg = true;
					break;
				}
				else {
					last_fc = current_fc;
					current_fc = 0;
				}
			}
			year++;
		}
	}
	Fc /= ensemble;
	return Fc;
}

int main() {
	int N = 10000;
	string F_out = "result.csv";	// output file name
	ofstream ofs(F_out);
	ofs << "Dg,Dr,Fc" << endl;	// Dg: y axis, Dr: x axis, Fc: flaction of Cooperator
	for (int q = -10; q <= 10; q++) {
		double Dg = q * 0.1;
		for (int w = -10; w <= 10; w++) {
			double Dr = w * 0.1;
			double Fc = game_function(N, Dg, Dr);
			cout << endl << Dg << " " << Dr << " " << Fc << endl << endl;
			ofs << Dg << ',' << Dr << ',' << Fc << endl;
		}
	}
	ofs.close();
}
