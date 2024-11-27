#pragma once
#include "params.h"
#include "traindata.h"
class machinelearning
{
public:
	traindata* TRAINDATA;
	params* PARAMS;
	string params_data= "C://Users//sugin//source//repos//othello_bonanza_2//x64//Debug//parameters_mayfair";
	vector<string> kifufiles;
	vector<vector<bool>>train_equal_leaf;
	vector<vector<int>> LEAFVALUES;
	vector<vector<int>> USEDPARAMS;//It is used when calculating dJ/dv. It indicate which params are used in one board status.
	void init();

	void make_leaf();
	void learn_oneepock();
	void showaccuracy();
	void calc_dJ_dv(int i, int j);
	void learn();
	double BETA = 0.000001;
	int dh=1;// amount of increase or decrease in one learn
};

