#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define U64 unsigned long long
class traindata
{
public:
	int num;
	vector<vector<U64>> kifu_player;
	vector<vector<U64>> kifu_opponent;

	//Å‘P‰è—ñ‚Ì––’[@
	vector<vector<U64>> minimax_player;
	vector<vector<U64>> minimax_opponent;
	/**************************************************************
	* minimax_player[i][0]=move_king
	* minimax_player[i][k>0]=move_brother
	* 
	* 
	* 
	* **************************************************************/

	void loadkifu(string kifufile);
};
