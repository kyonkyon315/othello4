#pragma once
#define U64 unsigned long long
#include <iostream>
#include <string>
#include <vector>
using namespace std;
/*
******************|パラメータ|*********************
* 3^10 * 6 = 59049 * 6 = 354294 params
*
*
* 1.
* o o o o o o o o
*   o         o
*
* 2.
* o o o o
* o o o
* o o
* o
*
* 3.
* o o o o o x x x
* o o o o o x x x
* x x x x x x x x
*
* 4.
* x o o o o o o x
* x x o o o o x x
*
* 5.
* x x x o x x x x
* x x o o
* x o o o
* o o o o
*
* 6.
* x x x x x x x x
* x x x x x x x x
* x x o o o o x x
* x x o o o x x x
* x x o o x x x x
* x x o x x x x x
* x x x x x x x x
* x x x x x x x x
*
***********************************************
*/
class square
{
public:

	U64 ans;
	const U64 mask11 = 0x00000000000002ff;
	const U64 mask12 = 0x0000000000004000;

	const U64 mask21 = 0x000000000000000f;
	const U64 mask22 = 0x0000000000000700;
	const U64 mask23 = 0x0000000000030000;
	const U64 mask24 = 0x0000000001000000;

	const U64 mask31 = 0x000000000000001f;
	const U64 mask32 = 0x0000000000001f00;

	const U64 mask41 = 0x000000000000007e;
	const U64 mask42 = 0x0000000000003c00;

	const U64 mask51 = 0x1000000000000000;
	const U64 mask52 = 0x0030000000000000;
	const U64 mask53 = 0x0000700000000000;
	const U64 mask54 = 0x000000f000000000;

	const U64 mask61 = 0x00003c0000000000;
	const U64 mask62 = 0x0000003800000000;
	const U64 mask63 = 0x0000000030000000;
	const U64 mask64 = 0x0000000000200000;

	const U64 mask71 = 0x0000000000000003;
	const U64 mask72 = 0x0000000000000700;
	const U64 mask73 = 0x00000000000e0000;
	const U64 mask74 = 0x000000000c000000;

	const U64 mask81 = 0x8040201008040303;
	const U64 mask82 = 0x8040201000000000;
	const U64 mask83 = 0x0000000088440000;
	const U64 mask84 = 0x000000000000a800;
	const U64 mask85 = 0x00000000000003ff;

	const U64 mask91 = 0x0000000000000207;
	const U64 mask92 = 0x0080402010080400;
	const U64 mask93 = 0x0001008000000000;
	const U64 mask94 = 0x0000000040200000;
	const U64 mask95 = 0x0000000000015000;
	const U64 mask96 = 0x00000000000003ff;

	const U64 maska1 = 0x0000000607030000;
	const U64 maska2 = 0x2010080600000000;
	const U64 maska3 = 0x0000000087430000;
	const U64 maska4 = 0x000000000000a400;
	const U64 maska5 = 0x00000000000003ff;

	const U64 maskb1 = 0x0000000003030000;
	const U64 maskb2 = 0x1008050300000000;
	const U64 maskb3 = 0x0000000083430000;
	const U64 maskb4 = 0x000000000000a000;
	const U64 maskb5 = 0x0000000000000800;
	const U64 maskb6 = 0x00000000000003ff;

	const U64 maskc1 = 0x0000000000000318;
	const U64 maskc2 = 0x0000000100000000;
	const U64 maskc3 = 0x0000000001000000;
	const U64 maskc4 = 0x0000000000010000;

	const U64 maskd1 = 0x00002b002b000000;
	const U64 maskd2 = 0x0000001400140000;
	const U64 maskd3 = 0x0000003e00000000;
	const U64 maskd4 = 0x00000000003e0000;

	const U64 maske1 = 0x000000000000030f;
	const U64 maske2 = 0x0000000009050000;
	const U64 maske3 = 0x0000000000008000;
	const U64 maske4 = 0x0000000000001000;
	const U64 maske5 = 0x00000000000003ff;

	const U64 maskf1 = 0x000000000000ff00;
	const U64 maskf2 = 0x0000000000000003;

	const U64 maskg1 = 0x0000000000000307;
	const U64 maskg2 = 0x0000000000000400;
	const U64 maskg3 = 0x0000000000070000;
	const U64 maskg4 = 0x0000000008000000;




	U64 translate(int kind, U64& input);
};

class params
{
public:

	int NUMOFSQUARE = 16;

	int num_of_param;

	int NUMOFPATTERN;
	int MAXSQUAREINPATTERN = 10;

	int** M;
	double** dM;

	square* SQUARE;

	U64* r_player;
	U64* r_opponent;

	vector<int> mod4_to_mod3_table;
	void makemod4tomod3table();
	int  M4toM3(int x);
	void init();
	void save(string foldername);
	void get(string foldername);
	void Delete();

	void copy(params* PARAMS);

	/*****************************以下bit rotationに使う*************************************/
	U64 t1, t2, t3;
	U64 mask1e = 0xaa55aa55aa55aa55, mask1ld = 0x00aa00aa00aa00aa, mask1ru = 0x5500550055005500;//e:eliminate
	U64 mask2e = 0xcccc3333cccc3333, mask2ld = 0x0000cccc0000cccc, mask2ru = 0x3333000033330000;//e:eliminate
	U64 mask3e = 0xf0f0f0f00f0f0f0f, mask3ld = 0x00000000f0f0f0f0, mask3ru = 0x0f0f0f0f00000000;//e:eliminate
	U64 t4, t5;
	U64 mask4d = 0x00ff00ff00ff00ff, mask4u = 0xff00ff00ff00ff00;
	U64 mask5d = 0x0000ffff0000ffff, mask5u = 0xffff0000ffff0000;
	U64 mask6d = 0x00000000ffffffff, mask6u = 0xffffffff00000000;
	U64 t7, t8;
	U64 mask7l = 0xaaaaaaaaaaaaaaaa, mask7r = 0x5555555555555555;
	U64 mask8l = 0xcccccccccccccccc, mask8r = 0x3333333333333333;
	U64 mask9l = 0xf0f0f0f0f0f0f0f0, mask9r = 0x0f0f0f0f0f0f0f0f;

	/*****************************以上bit rotationに使う*************************************/
	void rotation(U64& board_in, U64& board_out);
	void mirror_horizontal(U64& board_in, U64& board_out);
	void mirror_parpendicular(U64& board_in, U64& board_out);


	int value(U64& player, U64& opponent);

	vector<vector<int>> usedparams(U64 player, U64 opponent);
};

