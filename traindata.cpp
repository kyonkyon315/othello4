#include "traindata.h"
#include <fstream>
#include <sstream>

void traindata::loadkifu(string kifufile) {
	ifstream ifs(kifufile);
	string str_buf;
	while (true) {
		
		getline(ifs, str_buf);
		if (str_buf.compare("end")==0)break;

		kifu_player.push_back(vector<U64>(0, 0));
		kifu_opponent.push_back(vector<U64>(0, 0));
		minimax_player.push_back(vector<U64>(0, 0));
		minimax_opponent.push_back(vector<U64>(0, 0));

		for (int i = 0; i < (int)str_buf.size() / 101; i++) {
			string board = str_buf.substr(i * 101, 100);
			vector<int> input_part(100, 0);
			for (int j = 0; j < 100; j++)input_part[j] = stoi(board.substr(j, 1));
			U64 player = 0;
			U64 opponent = 0;
			for (int j = 0; j < 8; j++) {
				for (int k = 0; k < 8; k++) {
					if (input_part[10 * j + k + 11] == 2) {
						player = player | (1ULL << (8 * j + k));
					}
					if (input_part[10 * j + k + 11] == 1) {
						opponent = opponent | (1ULL << (8 * j + k));
					}

				}
			}
			kifu_player[kifu_player.size() - 1].push_back(player);
			kifu_opponent[kifu_opponent.size()-1].push_back(opponent);
			minimax_player[minimax_player.size() - 1].push_back(player);
			minimax_opponent[minimax_opponent.size() - 1].push_back(opponent);
		}
		if (kifu_player[kifu_player.size() - 1].size() < 2)cout << "error: there is only one or zero board \n";

	}
	cout << "kifu_player.size()=" << kifu_player.size() << "\n";
}

