#include "params.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <direct.h>
#include <stdlib.h>
#include <stdio.h>
#define U64 unsigned long long
using namespace std;

int M2toM3_unit(bool a, bool b) {
	if (a && b) {
		cout << "bad";
	}
	if (a)return 1;
	if (b)return 2;
	return 0;
}

void params::makemod4tomod3table() {
	num_of_param = 1;
	for (int i = 0; i < MAXSQUAREINPATTERN; i++)num_of_param *= 4;
	mod4_to_mod3_table = vector<int>(num_of_param, -1);//間違えてアクセスしたときエラーになる。
	vector<int> mod3table(MAXSQUAREINPATTERN, 1);
	U64 maxmod2 = 2;
	for (int i = 0; i < MAXSQUAREINPATTERN-1; i++) {
		mod3table[i + 1] = mod3table[i] * 3;
		maxmod2 *= 2;
	}
	for (U64 p = 0; p < maxmod2; p++) {
		for (U64 o = 0; o < maxmod2; o++) {
			if ((o & p)>0)continue;
			int MOD2 = (int)((p << MAXSQUAREINPATTERN) | o);
			int MOD3 = 0;
			for (int i = 0; i < MAXSQUAREINPATTERN; i++) {
				MOD3 += M2toM3_unit((p & (1ULL << i))>0, (o & (1ULL << i))>0)*mod3table[i];
			}
			mod4_to_mod3_table[MOD2] = MOD3;
		}
	}
	
}

int  params::M4toM3(int x) {
	return mod4_to_mod3_table[x];
}

void params::init() {

	makemod4tomod3table();
	NUMOFPATTERN = 1;
	for (int i = 0; i < MAXSQUAREINPATTERN; i++)NUMOFPATTERN *= 3;

	M = new int* [NUMOFSQUARE];
	dM = new double* [NUMOFSQUARE];

	for (int i = 0; i < NUMOFSQUARE; i++) {
		M[i] = new int[NUMOFPATTERN];
		dM[i] = new double[NUMOFPATTERN];
	}

	for (int i = 0; i < NUMOFSQUARE; i++) {
		for (int j = 0; j < NUMOFPATTERN; j++) {
			M[i][j] = 0;
		}
	}

	r_player = new U64[8];
	r_opponent = new U64[8];

	SQUARE = new square;

}

void params::Delete() {
	for (int i = 0; i < NUMOFSQUARE; i++) {
		delete[] M[i];
		delete[] dM[i];
	}
	delete[] M;
	delete[] dM;

	delete[] r_player;
	delete[] r_opponent;
	delete SQUARE;
}



static void CreateFolder(string FolderName)
{
	const char* foldername = FolderName.c_str();
	if (_mkdir(foldername) == 0) {
		cout << "Directory '" << FolderName << "' was successfully created\n";
	}
	else {
		cout << "Problem creating directory '" << FolderName << "' .\n";
	}
}

static void savearray(string filename, int* array, int length) {
	ofstream ofs(filename);
	for (int i = 0; i < length; i++)ofs << array[i] << ",";
}

void params::save(string foldername) {
	CreateFolder(foldername);
	for (int i = 0; i < NUMOFSQUARE; i++) {
		savearray(foldername + "/P" + to_string(i) + ".csv", M[i], NUMOFPATTERN);
	}
}

static void getarray(string filename, int* array, int length) {
	string str_buf;
	string str_conma_buf;
	ifstream ifs(filename);
	getline(ifs, str_buf);
	istringstream i_stream(str_buf);
	for (int i = 0; i < length; i++) {
		getline(i_stream, str_conma_buf, ',');
		array[i] = stoi(str_conma_buf);
	}
	ifs.close();
}

void params::get(string foldername) {
	for (int i = 0; i < NUMOFSQUARE; i++) {
		getarray(foldername + "/P" + to_string(i) + ".csv", M[i], NUMOFPATTERN);
	}
}






void params::mirror_horizontal(U64& board_in, U64& board_out) {
	t4 = ((board_in & mask4d) << 8) | ((board_in & mask4u) >> 8);
	t5 = ((t4 & mask5d) << 16) | ((t4 & mask5u) >> 16);
	board_out = ((t5 & mask6d) << 32) | ((t5 & mask6u) >> 32);
}

void params::mirror_parpendicular(U64& board_in, U64& board_out) {
	t7 = ((board_in & mask7l) >> 1) | ((board_in & mask7r) << 1);
	t8 = ((t7 & mask8l) >> 2) | ((t7 & mask8r) << 2);
	board_out = ((t8 & mask9l) >> 4) | ((t8 & mask9r) << 4);
}


void params::rotation(U64& board_in, U64& board_out) {

	t1 = (board_in & mask1e) | ((board_in & mask1ld) << 7) | ((board_in & mask1ru) >> 7);
	t2 = (t1 & mask2e) | ((t1 & mask2ld) << 14) | ((t1 & mask2ru) >> 14);
	t3 = (t2 & mask3e) | ((t2 & mask3ld) << 28) | ((t2 & mask3ru) >> 28);
	t4 = ((t3 & mask4d) << 8) | ((t3 & mask4u) >> 8);
	t5 = ((t4 & mask5d) << 16) | ((t4 & mask5u) >> 16);
	board_out = ((t5 & mask6d) << 32) | ((t5 & mask6u) >> 32);
}

int params::value(U64& player, U64& opponent) {
	//---------------------------------------------------
	//    _____________
	//    |     7|0    |
	//    |            |
	//    |_6        1_|
	//    | 5        2 |
	//    |            |
	//    |     4|3    |
	//    ^^^^^^^^^^^^^^
	//---------------------------------------------------

	r_player[0] = player; r_opponent[0] = opponent;
	rotation(player, r_player[2]); rotation(opponent, r_opponent[2]);
	mirror_horizontal(player, r_player[3]); mirror_horizontal(opponent, r_opponent[3]);
	mirror_parpendicular(player, r_player[7]); mirror_parpendicular(opponent, r_opponent[7]);
	mirror_horizontal(r_player[7], r_player[4]); mirror_horizontal(r_opponent[7], r_opponent[4]);
	mirror_horizontal(r_player[2], r_player[1]);	mirror_horizontal(r_opponent[2], r_opponent[1]);
	mirror_parpendicular(r_player[1], r_player[6]); mirror_parpendicular(r_opponent[1], r_opponent[6]);
	mirror_parpendicular(r_player[2], r_player[5]); mirror_parpendicular(r_opponent[2], r_opponent[5]);


	//----------------------------------------------------------------------------------------------

	int value_out = 0;

	for (int i = 0; i < NUMOFSQUARE; i++) {
		for (int j = 0; j < 8; j++) {
			value_out += M[i][M4toM3(((SQUARE->translate(i, r_player[j]) << MAXSQUAREINPATTERN) | SQUARE->translate(i, r_opponent[j])))];
			if (abs(value_out) > 10000) {
				cout << "error:value_out is too big.\n";
				cout << "square;" << i << "\n";
				int a;
				cin >> a;
			}
		}
	}

	return value_out;
}

vector<vector<int>> params::usedparams(U64 player, U64 opponent) {

	r_player[0] = player; r_opponent[0] = opponent;
	rotation(player, r_player[2]); rotation(opponent, r_opponent[2]);
	mirror_horizontal(player, r_player[3]); mirror_horizontal(opponent, r_opponent[3]);
	mirror_parpendicular(player, r_player[7]); mirror_parpendicular(opponent, r_opponent[7]);
	mirror_horizontal(r_player[7], r_player[4]); mirror_horizontal(r_opponent[7], r_opponent[4]);
	mirror_horizontal(r_player[2], r_player[1]);	mirror_horizontal(r_opponent[2], r_opponent[1]);
	mirror_parpendicular(r_player[1], r_player[6]); mirror_parpendicular(r_opponent[1], r_opponent[6]);
	mirror_parpendicular(r_player[2], r_player[5]); mirror_parpendicular(r_opponent[2], r_opponent[5]);

	vector<vector<int>> output(NUMOFSQUARE);
	for (int i = 0; i < NUMOFSQUARE; i++) {
		for (int j = 0; j < 8; j++) {
			output[i].push_back(M4toM3((SQUARE->translate(i, r_player[j]) << MAXSQUAREINPATTERN) | SQUARE->translate(i, r_opponent[j])));
		}
	}
	return output;
}

void params::copy(params* parent) {
	for (int i = 0; i < NUMOFSQUARE; i++) {
		delete[]  M[i];
		delete[] dM[i];
		M[i] = parent->M[i];
		dM[i] = parent->dM[i];
	}
}
