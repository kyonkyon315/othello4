#pragma once
#ifndef kyonkyon3_h_
#define kyonkyon3_h_
#include "params.h"
#include "depthDecision.h"
#define U64 unsigned long long
class kyonkyon3
{
public:
	int Maxnode=10000000;
	int edge=0;//0~edge-1:used, edge~Maxnode:unused

	U64* player;
	U64* opponent;
	//int* parent;
	int* child;
	int* childnum;
	int* value;

	int lastans;
	int ans = 0;

	const int maxValue = 1000000;
	

	U64 ans_turn = 0;
	U64 H = 0;

	U64 player_for_canput;
	U64 opponent_for_canput;

	U64 blank, opponent_l, opponent_in_a_row_l;
	U64 opponent_r, opponent_in_a_row_r;
	U64 opponent_d, opponent_in_a_row_d;
	U64 opponent_u, opponent_in_a_row_u;
	U64 opponent_ur, opponent_in_a_row_ur;
	U64 opponent_dr, opponent_in_a_row_dr;
	U64 opponent_ul, opponent_in_a_row_ul;
	U64 opponent_dl, opponent_in_a_row_dl;


	U64 ans11, ans12, ans13, ans14, ans15, ans16;//anspq:derection=p,depth=q
	U64 ans21, ans22, ans23, ans24, ans25, ans26;
	U64 ans31, ans32, ans33, ans34, ans35, ans36;
	U64 ans41, ans42, ans43, ans44, ans45, ans46;
	U64 ans51, ans52, ans53, ans54, ans55, ans56;
	U64 ans61, ans62, ans63, ans64, ans65, ans66;
	U64 ans71, ans72, ans73, ans74, ans75, ans76;
	U64 ans81, ans82, ans83, ans84, ans85, ans86;

	U64 edge_mask = 0x8100000000000081;
	U64 evaluate1;
	U64 evaluate2;
	U64 evaluate3;
	U64 evaluate4;
	U64 evaluate_unite;

	params* PARAMS;

	U64 player_leaf;
	U64 opponent_leaf;
	U64 lastplayer_leaf;
	U64 lastopponent_leaf;
	bool junban_leaf;
	bool lastjunban_leaf;//traindata‚Æ“¯‚¶Žè”Ô‚È‚çtrue otherwise false
	int value_leaf;
	int lastvalue_leaf;

	int canput_player;
	int canput_opponent;

	void init();
	void setmaxnode(int maxnode);
	void Delete();
	void setfirstnode(int board_in[], int junban);
	void setfirstnode_byU64(U64 player_in,U64 opponent_in);
	U64 canput(int id);
    U64 canput_enemy(int id);
	void generatechild(int parent);
	U64 places_player_turn(U64 move);
	void print(int id);
	void getvalue(int id);
	U64 bits_count(U64 value);
	void alphabeta(int depth);
	void search();
	void clearchildnum();
	void clearvalue();
	bool train_equal_leaf();
	int getleafvalue();
	void printTree(int id, int space, int depth);

	depthDecision* DEPTHDECISION;
};

#endif
