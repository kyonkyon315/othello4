#include "machinelearning.h"
#include "kyonkyon3.h"
#include "params.h"
#include <iomanip>
void machinelearning::init() {
	cout << "machinelearning->init\n";
	TRAINDATA = new traindata;
	PARAMS = new params;
	for (int i = 0; i < (int)kifufiles.size(); i++) {
		TRAINDATA->loadkifu(kifufiles[i]);
	}
	PARAMS->init();
	PARAMS->get(params_data);
	cout << "                     ->end\n";
}

void machinelearning::make_leaf() {
	cout << "machinelearning->making leaf\n";

	//思考エンジンの起動　最善応手列の末端を求める。
	kyonkyon3 engine;
	engine.setmaxnode(1000);
	engine.init();
	engine.PARAMS = PARAMS;//パラメーターを教える
	//train_equal_leaf=vector<vector<bool>>(TRAINDATA->kifu_player.size(),vector<bool>(0));
	LEAFVALUES= vector<vector<int>>(TRAINDATA->kifu_player.size(), vector<int>(0));
	for (int i = 0; i < TRAINDATA->kifu_player.size(); i++) {
		if (TRAINDATA->kifu_player[i].size() < 2)cout << "error: there is only one or zero board \n";
		for (int j = 0; j < TRAINDATA->kifu_player[i].size(); j++) {
			//cout << i << " ";
			engine.edge = 1;
			engine.clearchildnum();
			engine.setfirstnode_byU64(TRAINDATA->kifu_player[i][j], TRAINDATA->kifu_opponent[i][j]);
			engine.search();
			//train_equal_leaf[i].push_back(engine.train_equal_leaf());
			TRAINDATA->minimax_player[i][j] = engine.lastplayer_leaf;
			TRAINDATA->minimax_opponent[i][j] = engine.lastopponent_leaf;

			LEAFVALUES[i].push_back(engine.getleafvalue());
		}
	}
	engine.Delete();
	cout << "                  ->end\n";
}



void machinelearning::showaccuracy() {
	int numofcorrectans = 0;
	for (int i = 0; i < TRAINDATA->kifu_player.size(); i++) {
		int king = 0;
		for (int j = 0; j < TRAINDATA->kifu_player[i].size(); j++) {
			if (LEAFVALUES[i][j] <= LEAFVALUES[i][king])king = j;
		}
		if (king == 0)numofcorrectans++;
	}
	cout << "number of data:" << right << setw(10) << TRAINDATA->kifu_player.size() << "\n";
	cout << "correct       :" << right << setw(10) << numofcorrectans << "\n";
	cout << "accuracy      :" << right << setw(10) <<( 100*numofcorrectans/ (int)TRAINDATA->kifu_player.size()) <<"%\n";
}
double loss;
void machinelearning::learn_oneepock() {
	cout << "machinelearning->learn_oneepock\n";
	loss = 0.;

	//直す
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < PARAMS->NUMOFPATTERN; j++) {
				PARAMS->dM[i][j] =2.*BETA*PARAMS->M[i][j];
		}
	}

	for (int i = 0; i < TRAINDATA->minimax_player.size(); i++) {

		USEDPARAMS=PARAMS->usedparams(TRAINDATA->minimax_player[i][0], TRAINDATA->minimax_opponent[i][0]);
		

		calc_dJ_dv(i,0);

		for (int j = 1; j < TRAINDATA->minimax_player[i].size(); j++) {

			USEDPARAMS=PARAMS->usedparams(TRAINDATA->minimax_player[i][j], TRAINDATA->minimax_opponent[i][j]);
			calc_dJ_dv(i, j);
		}
	}
	//直す
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < PARAMS->NUMOFPATTERN; j++) {
			if (i == 0 && j == 0)continue;
			//if (abs(PARAMS->dM[i][j]) > 100000.) {
			//  continue;
			//}
			//else if (PARAMS->dM[i][j] < -0.00000000001) {
			if (PARAMS->dM[i][j] < -0.00000000001) {
				PARAMS->M[i][j] += dh;
			}
			else if (PARAMS->dM[i][j] > 0.00000000001) {
				PARAMS->M[i][j] -= dh;
			}
			else {
				continue;
			}
		}
	}
	//直す
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < PARAMS->NUMOFPATTERN; j++) {
			loss += BETA * (double)(PARAMS->M[i][j] * PARAMS->M[i][j]);
		}
	}

	cout << "                      ->end\n";
	cout << "loss:" <<setprecision(12)<< loss << "\n";
}
double ALPHA = 0.01;
double T(double x) {
	return 1. / (1 + exp(-x));
}

double dT_dx(double x) {
	double T_ = T(ALPHA*x);
	return ALPHA*T_ * (1 - T_);
}



double bool_to_sign(bool x) {
	if (x)return 1.;
	else return -1.;
}

void machinelearning::calc_dJ_dv(int i,int j) {
	if (j == 0) {
		for (int h = 1; h < TRAINDATA->minimax_player[i].size(); h++) {
			//直す
			for (int k = 0; k < 6; k++) {
				for (int l = 0; l < USEDPARAMS[k].size(); l++) {
					PARAMS->dM[k][USEDPARAMS[k][l]] +=
						//-dT_dx((LEAFVALUES[i][h] - LEAFVALUES[i][0]) * bool_to_sign(train_equal_leaf[i][j])) * bool_to_sign(train_equal_leaf[i][j]);
					      dT_dx(-LEAFVALUES[i][h] + LEAFVALUES[i][0]);
				}
			}
		}

	}
	else {
		loss += T(-LEAFVALUES[i][j] + LEAFVALUES[i][0]);
		//直す
		for (int k = 0; k < 6; k++) {
			for (int l = 0; l < USEDPARAMS[k].size(); l++) {
				PARAMS->dM[k][USEDPARAMS[k][l]] -=
					//dT_dx((LEAFVALUES[i][j] - LEAFVALUES[i][0]) * bool_to_sign(train_equal_leaf[i][j])) * bool_to_sign(train_equal_leaf[i][j]);
					dT_dx(-LEAFVALUES[i][j] + LEAFVALUES[i][0]);
				
			}
		}
	}
}

void machinelearning::learn() {
	string outputfile = "parameters";

	for (int i = 0; i < 10000; i++) {
		make_leaf();
		showaccuracy();
		learn_oneepock();
		PARAMS->save(outputfile);

	}
	
	PARAMS->save(outputfile);
}