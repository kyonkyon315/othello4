#include <iostream>
#include <fstream>
#include <sstream>
#include "kyonkyon3.h"
#include "params.h"
#include "machinelearning.h"
#include <time.h>
#include <thread>
#include <chrono>
#include <vector>
using namespace std;
#define U64 unsigned long long

void printboard(int board[]) {
	cout << " ";
	for (int i = 0; i < 8; i++)cout << " " << i + 1 << " ";
	cout << "\n";
	for (int i = 10; i < 90; i++) {
		cout << "|";
		if (board[i] == 1)cout << "o";
		else if (board[i] == 0)cout << " ";
		else if (board[i] == 2)cout << "x";
		if ((i + 1) % 10 == 0)cout << "|\n";
	}
}

vector<U64> nb_to_bb(int* board, int junban) {
	vector<U64>ans(2);
	U64 player = 0;
	U64 opponent = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[10 * i + j + 11] == junban) {
				player = player | (1ULL << (8 * i + j));
			}
			else if (board[10 * i + j + 11] == 3 - junban) {
				opponent = opponent | (1ULL << (8 * i + j));
			}
		}
	}
	ans[0] = player;
	ans[1] = opponent;
	return ans;
}


int main() {

	/*
	machinelearning ML;
	string kifu="C://Users//sugin//source//repos//make_traindata//x64//Debug//kifu0//traindata";
	for (int i = 0; i < 100; i++) {
		ML.kifufiles.push_back(kifu + to_string(i+1) + ".txt");
	}
	//
	ML.init();
	ML.learn();
	*/
	int board[64] =
	{
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		0,0,0,1,2,0,0,0,
		0,0,0,2,1,0,0,0,
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
	};
	int junban = 1;
	
	string initationfile = "C:\\Users\\sugin\\source\\repos\\OthelloGUI\\x64\\Debug\\initation.txt";
	bool gotten = false;
	//int junban;
	while (!gotten) {
		ifstream file(initationfile);
		string line;
		getline(file, line);
		if (line.compare("junban")==0) {
			gotten = true;
			getline(file, line);
			junban = stoi(line);
		}
	}
	cout << "junban:" << junban << "\n";
	kyonkyon3 engine;
	engine.setmaxnode(1000000);
	engine.init();
	params* PARAMS = new params;
	PARAMS->init();
	std::cout << "bonanza3.1\n" << flush;
	string params_data = "C://Users//sugin//source//repos//othello_bonanza_2//x64//Debug//parameters_bonanza3.1_1127.1";
	PARAMS->get(params_data);
	engine.PARAMS = PARAMS;
	string communicatefile_in = "C:\\Users\\sugin\\source\\repos\\OthelloGUI\\x64\\Debug\\initation" + to_string(junban) + "out.txt";
	string communicatefile_out = "C:\\Users\\sugin\\source\\repos\\OthelloGUI\\x64\\Debug\\initation"+to_string(junban) + "in.txt";

	bool roop = true;
	while (roop) {
		bool gotten2 = false;
		while (!gotten2) {
			this_thread::sleep_for(std::chrono::milliseconds(5));
			ifstream file2(communicatefile_in);
			string line2;
			getline(file2, line2);
			if (line2.compare("ok") == 0) {
				gotten2 = true;
			}
		}
		ifstream file2(communicatefile_in);
		string line2;
		getline(file2, line2);
		getline(file2, line2);
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (line2[8 * i + j] == '0') {
					board[8 * i + j] = 0;
				}
				else if (line2[8 * i + j] == '1') {
					board[8 * i + j] = 1;
				}
				else {
					board[8 * i + j] = 2;
				}
			}
		}
		ofstream file3(communicatefile_in);
		file3 << "still";
		file3.close();
		engine.edge = 1;
		engine.clearchildnum();
		engine.clearvalue();
		engine.setfirstnode(board, junban);
		cout << "bonanza3.1\n";
		engine.search();
		
		int move88 = engine.lastans;
		//int move88 = engine.ans;
		int move100 = 10 * (move88 / 8) + move88 % 8 + 11;
		ofstream file4(communicatefile_out);
		file4 << "ok\n";
		file4 << move100;
		cout << move100;
	}
	/*
	clock_t start = clock();
	engine.setfirstnode(board, 2);
	engine.print(0);
	//engine.alphabeta(11);
	engine.search(80000000);
	clock_t end = clock();
	double time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
	cout << "NPS:" << engine.edge / time * 1000 << "[node/s]\n";
	*/
	return 0;
}