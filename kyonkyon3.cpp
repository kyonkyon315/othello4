#include "kyonkyon3.h"
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

/*
class kyonkyon3
{
	bitboard board;
	int Maxnode;
	int edge;//0-edge-1:used,edge-Maxnode:unused

	void setfirstnode(int board_in[], int junban);
	void generatechild(int parent);

};*/

void kyonkyon3::setmaxnode(int maxnode) {
    Maxnode = maxnode;
}

void kyonkyon3::init() {
    edge = 1;
	player = new U64[Maxnode];
	opponent = new U64[Maxnode];
	//parent = new int[Maxnode];
	child = new int[Maxnode];
	childnum = new int[Maxnode];//if childnum[id]==0{it is edge node}
	value = new int[Maxnode];
    //bestchild = new int[Maxnode];

    for (int i = 0; i < Maxnode; i++) {
        childnum[i] = 0;
    }
    DEPTHDECISION = new depthDecision;
    DEPTHDECISION->setMaxValue(maxValue);
    DEPTHDECISION->init();
}

void kyonkyon3::clearchildnum() {
    for (int i = 0; i < Maxnode; i++) {
        childnum[i] = 0;
    }
}

void kyonkyon3::clearvalue() {
    for (int i = 0; i < Maxnode; i++) {
        value[i] = -maxValue;
    }
}

void kyonkyon3::Delete() {
	delete[] player;
	delete[] opponent;
	//delete[] parent;
	delete[] child;
	delete[] childnum;
    delete[] value;
    delete DEPTHDECISION;
}

void kyonkyon3::print(int id) {
    for (int i = 0; i < 8; i++) {
        for (int v = 0; v < 8; v++) {
            cout << (player[id] & (1ULL << (8 * i + v)) ? 1 : (opponent[id] & (1ULL << (8 * i + v)) ? 2 : 0)) << ",";
        }
        cout << "\n";
    }
    cout << "\n";
}

void kyonkyon3::setfirstnode(int board_in[], int junban) {
    player[0] = 0;
    opponent[0] = 0;
    for (int i = 0; i < 64; i++) {
        if (board_in[i] == junban) {
            player  [0] = player  [0] | (1ULL << i);
        }
        else if (board_in[i] == 3 - junban) {
            opponent[0] = opponent[0] | (1ULL << i);
        }
    }
}

void kyonkyon3::setfirstnode_byU64(U64 player_in, U64 opponent_in) {
    player[0] = player_in;
    opponent[0] = opponent_in;
}


U64 kyonkyon3::canput(int id) {
    player_for_canput = player[id];
    opponent_for_canput = opponent[id];
    blank = ~(player_for_canput | opponent_for_canput);
    opponent_l =opponent_for_canput& 0x7e7e7e7e7e7e7e7e;
    opponent_in_a_row_l = blank & (opponent_l >> 1);
    ans11 = opponent_in_a_row_l & (player_for_canput >> 2);
    opponent_in_a_row_l &= (opponent_l >> 2);
    ans12 = opponent_in_a_row_l & (player_for_canput >> 3);
    opponent_in_a_row_l &= (opponent_l >> 3);
    ans13 = opponent_in_a_row_l & (player_for_canput >> 4);
    opponent_in_a_row_l &= (opponent_l >> 4);
    ans14 = opponent_in_a_row_l & (player_for_canput >> 5);
    opponent_in_a_row_l &= (opponent_l >> 5);
    ans15 = opponent_in_a_row_l & (player_for_canput >> 6);
    opponent_in_a_row_l &= (opponent_l >> 6);
    ans16 = opponent_in_a_row_l & (player_for_canput >> 7);

    opponent_r =opponent_for_canput& 0x7e7e7e7e7e7e7e7e;
    opponent_in_a_row_r = blank & (opponent_r << 1);
    ans21 = opponent_in_a_row_r & (player_for_canput << 2);
    opponent_in_a_row_r &= (opponent_r << 2);
    ans22 = opponent_in_a_row_r & (player_for_canput << 3);
    opponent_in_a_row_r &= (opponent_r << 3);
    ans23 = opponent_in_a_row_r & (player_for_canput << 4);
    opponent_in_a_row_r &= (opponent_r << 4);
    ans24 = opponent_in_a_row_r & (player_for_canput << 5);
    opponent_in_a_row_r &= (opponent_r << 5);
    ans25 = opponent_in_a_row_r & (player_for_canput << 6);
    opponent_in_a_row_r &= (opponent_r << 6);
    ans26 = opponent_in_a_row_r & (player_for_canput << 7);

    opponent_u =opponent_for_canput& 0x00ffffffffffff00;
    opponent_in_a_row_u = blank & (opponent_u >> 8);
    ans31 = opponent_in_a_row_u & (player_for_canput >> 16);
    opponent_in_a_row_u &= (opponent_u >> 16);
    ans32 = opponent_in_a_row_u & (player_for_canput >> 24);
    opponent_in_a_row_u &= (opponent_u >> 24);
    ans33 = opponent_in_a_row_u & (player_for_canput >> 32);
    opponent_in_a_row_u &= (opponent_u >> 32);
    ans34 = opponent_in_a_row_u & (player_for_canput >> 40);
    opponent_in_a_row_u &= (opponent_u >> 40);
    ans35 = opponent_in_a_row_u & (player_for_canput >> 48);
    opponent_in_a_row_u &= (opponent_u >> 48);
    ans36 = opponent_in_a_row_u & (player_for_canput >> 56);

    opponent_d =opponent_for_canput& 0x00ffffffffffff00;
    opponent_in_a_row_d = blank & (opponent_d << 8);
    ans41 = opponent_in_a_row_d & (player_for_canput << 16);
    opponent_in_a_row_d &= (opponent_d << 16);
    ans42 = opponent_in_a_row_d & (player_for_canput << 24);
    opponent_in_a_row_d &= (opponent_d << 24);
    ans43 = opponent_in_a_row_d & (player_for_canput << 32);
    opponent_in_a_row_d &= (opponent_d << 32);
    ans44 = opponent_in_a_row_d & (player_for_canput << 40);
    opponent_in_a_row_d &= (opponent_d << 40);
    ans45 = opponent_in_a_row_d & (player_for_canput << 48);
    opponent_in_a_row_d &= (opponent_d << 48);
    ans46 = opponent_in_a_row_d & (player_for_canput << 56);

    opponent_ul =opponent_for_canput& 0x007e7e7e7e7e7e00;
    opponent_in_a_row_ul = blank & (opponent_ul >> 9);
    ans51 = opponent_in_a_row_ul & (player_for_canput >> 18);
    opponent_in_a_row_ul &= (opponent_ul >> 18);
    ans52 = opponent_in_a_row_ul & (player_for_canput >> 27);
    opponent_in_a_row_ul &= (opponent_ul >> 27);
    ans53 = opponent_in_a_row_ul & (player_for_canput >> 36);
    opponent_in_a_row_ul &= (opponent_ul >> 36);
    ans54 = opponent_in_a_row_ul & (player_for_canput >> 45);
    opponent_in_a_row_ul &= (opponent_ul >> 45);
    ans55 = opponent_in_a_row_ul & (player_for_canput >> 54);
    opponent_in_a_row_ul &= (opponent_ul >> 54);
    ans56 = opponent_in_a_row_ul & (player_for_canput >> 63);

    opponent_dl =opponent_for_canput& 0x007e7e7e7e7e7e00;
    opponent_in_a_row_dl = blank & (opponent_dl << 7);
    ans61 = opponent_in_a_row_dl & (player_for_canput << 14);
    opponent_in_a_row_dl &= (opponent_dl << 14);
    ans62 = opponent_in_a_row_dl & (player_for_canput << 21);
    opponent_in_a_row_dl &= (opponent_dl << 21);
    ans63 = opponent_in_a_row_dl & (player_for_canput << 28);
    opponent_in_a_row_dl &= (opponent_dl << 28);
    ans64 = opponent_in_a_row_dl & (player_for_canput << 35);
    opponent_in_a_row_dl &= (opponent_dl << 35);
    ans65 = opponent_in_a_row_dl & (player_for_canput << 42);
    opponent_in_a_row_dl &= (opponent_dl << 42);
    ans66 = opponent_in_a_row_dl & (player_for_canput << 49);

    opponent_dr =opponent_for_canput& 0x007e7e7e7e7e7e00;
    opponent_in_a_row_dr = blank & (opponent_dr << 9);
    ans71 = opponent_in_a_row_dr & (player_for_canput << 18);
    opponent_in_a_row_dr &= (opponent_dr << 18);
    ans72 = opponent_in_a_row_dr & (player_for_canput << 27);
    opponent_in_a_row_dr &= (opponent_dr << 27);
    ans73 = opponent_in_a_row_dr & (player_for_canput << 36);
    opponent_in_a_row_dr &= (opponent_dr << 36);
    ans74 = opponent_in_a_row_dr & (player_for_canput << 45);
    opponent_in_a_row_dr &= (opponent_dr << 45);
    ans75 = opponent_in_a_row_dr & (player_for_canput << 54);
    opponent_in_a_row_dr &= (opponent_dr << 54);
    ans76 = opponent_in_a_row_dr & (player_for_canput << 63);


    opponent_ur =opponent_for_canput& 0x007e7e7e7e7e7e00;
    opponent_in_a_row_ur = blank & (opponent_ur >> 7);
    ans81 = opponent_in_a_row_ur & (player_for_canput >> 14);
    opponent_in_a_row_ur &= (opponent_ur >> 14);
    ans82 = opponent_in_a_row_ur & (player_for_canput >> 21);
    opponent_in_a_row_ur &= (opponent_ur >> 21);
    ans83 = opponent_in_a_row_ur & (player_for_canput >> 28);
    opponent_in_a_row_ur &= (opponent_ur >> 28);
    ans84 = opponent_in_a_row_ur & (player_for_canput >> 35);
    opponent_in_a_row_ur &= (opponent_ur >> 35);
    ans85 = opponent_in_a_row_ur & (player_for_canput >> 42);
    opponent_in_a_row_ur &= (opponent_ur >> 42);
    ans86 = opponent_in_a_row_ur & (player_for_canput >> 49);
    return ans11 | ans12 | ans13 | ans14 | ans15 | ans16 |
        ans21 | ans22 | ans23 | ans24 | ans25 | ans26 |
        ans31 | ans32 | ans33 | ans34 | ans35 | ans36 |
        ans41 | ans42 | ans43 | ans44 | ans45 | ans46 |
        ans51 | ans52 | ans53 | ans54 | ans55 | ans56 |
        ans61 | ans62 | ans63 | ans64 | ans65 | ans66 |
        ans71 | ans72 | ans73 | ans74 | ans75 | ans76 |
        ans81 | ans82 | ans83 | ans84 | ans85 | ans86;
}

U64 kyonkyon3::canput_enemy(int id) {
    player_for_canput = player[id];
    opponent_for_canput = opponent[id];
    blank = ~(player_for_canput| opponent_for_canput);
    opponent_l = player_for_canput& 0x7e7e7e7e7e7e7e7e;
    opponent_in_a_row_l = blank & (opponent_l >> 1);
    ans11 = opponent_in_a_row_l & (opponent_for_canput>> 2);
    opponent_in_a_row_l &= (opponent_l >> 2);
    ans12 = opponent_in_a_row_l & (opponent_for_canput>> 3);
    opponent_in_a_row_l &= (opponent_l >> 3);
    ans13 = opponent_in_a_row_l & (opponent_for_canput>> 4);
    opponent_in_a_row_l &= (opponent_l >> 4);
    ans14 = opponent_in_a_row_l & (opponent_for_canput>> 5);
    opponent_in_a_row_l &= (opponent_l >> 5);
    ans15 = opponent_in_a_row_l & (opponent_for_canput>> 6);
    opponent_in_a_row_l &= (opponent_l >> 6);
    ans16 = opponent_in_a_row_l & (opponent_for_canput>> 7);

    opponent_r = player_for_canput& 0x7e7e7e7e7e7e7e7e;
    opponent_in_a_row_r = blank & (opponent_r << 1);
    ans21 = opponent_in_a_row_r & (opponent_for_canput<< 2);
    opponent_in_a_row_r &= (opponent_r << 2);
    ans22 = opponent_in_a_row_r & (opponent_for_canput<< 3);
    opponent_in_a_row_r &= (opponent_r << 3);
    ans23 = opponent_in_a_row_r & (opponent_for_canput<< 4);
    opponent_in_a_row_r &= (opponent_r << 4);
    ans24 = opponent_in_a_row_r & (opponent_for_canput<< 5);
    opponent_in_a_row_r &= (opponent_r << 5);
    ans25 = opponent_in_a_row_r & (opponent_for_canput<< 6);
    opponent_in_a_row_r &= (opponent_r << 6);
    ans26 = opponent_in_a_row_r & (opponent_for_canput<< 7);

    opponent_u = player_for_canput& 0x00ffffffffffff00;
    opponent_in_a_row_u = blank & (opponent_u >> 8);
    ans31 = opponent_in_a_row_u & (opponent_for_canput>> 16);
    opponent_in_a_row_u &= (opponent_u >> 16);
    ans32 = opponent_in_a_row_u & (opponent_for_canput>> 24);
    opponent_in_a_row_u &= (opponent_u >> 24);
    ans33 = opponent_in_a_row_u & (opponent_for_canput>> 32);
    opponent_in_a_row_u &= (opponent_u >> 32);
    ans34 = opponent_in_a_row_u & (opponent_for_canput>> 40);
    opponent_in_a_row_u &= (opponent_u >> 40);
    ans35 = opponent_in_a_row_u & (opponent_for_canput>> 48);
    opponent_in_a_row_u &= (opponent_u >> 48);
    ans36 = opponent_in_a_row_u & (opponent_for_canput>> 56);

    opponent_d = player_for_canput& 0x00ffffffffffff00;
    opponent_in_a_row_d = blank & (opponent_d << 8);
    ans41 = opponent_in_a_row_d & (opponent_for_canput<< 16);
    opponent_in_a_row_d &= (opponent_d << 16);
    ans42 = opponent_in_a_row_d & (opponent_for_canput<< 24);
    opponent_in_a_row_d &= (opponent_d << 24);
    ans43 = opponent_in_a_row_d & (opponent_for_canput<< 32);
    opponent_in_a_row_d &= (opponent_d << 32);
    ans44 = opponent_in_a_row_d & (opponent_for_canput<< 40);
    opponent_in_a_row_d &= (opponent_d << 40);
    ans45 = opponent_in_a_row_d & (opponent_for_canput<< 48);
    opponent_in_a_row_d &= (opponent_d << 48);
    ans46 = opponent_in_a_row_d & (opponent_for_canput<< 56);

    opponent_ul = player_for_canput& 0x007e7e7e7e7e7e00;
    opponent_in_a_row_ul = blank & (opponent_ul >> 9);
    ans51 = opponent_in_a_row_ul & (opponent_for_canput>> 18);
    opponent_in_a_row_ul &= (opponent_ul >> 18);
    ans52 = opponent_in_a_row_ul & (opponent_for_canput>> 27);
    opponent_in_a_row_ul &= (opponent_ul >> 27);
    ans53 = opponent_in_a_row_ul & (opponent_for_canput>> 36);
    opponent_in_a_row_ul &= (opponent_ul >> 36);
    ans54 = opponent_in_a_row_ul & (opponent_for_canput>> 45);
    opponent_in_a_row_ul &= (opponent_ul >> 45);
    ans55 = opponent_in_a_row_ul & (opponent_for_canput>> 54);
    opponent_in_a_row_ul &= (opponent_ul >> 54);
    ans56 = opponent_in_a_row_ul & (opponent_for_canput>> 63);

    opponent_dl = player_for_canput& 0x007e7e7e7e7e7e00;
    opponent_in_a_row_dl = blank & (opponent_dl << 7);
    ans61 = opponent_in_a_row_dl & (opponent_for_canput<< 14);
    opponent_in_a_row_dl &= (opponent_dl << 14);
    ans62 = opponent_in_a_row_dl & (opponent_for_canput<< 21);
    opponent_in_a_row_dl &= (opponent_dl << 21);
    ans63 = opponent_in_a_row_dl & (opponent_for_canput<< 28);
    opponent_in_a_row_dl &= (opponent_dl << 28);
    ans64 = opponent_in_a_row_dl & (opponent_for_canput<< 35);
    opponent_in_a_row_dl &= (opponent_dl << 35);
    ans65 = opponent_in_a_row_dl & (opponent_for_canput<< 42);
    opponent_in_a_row_dl &= (opponent_dl << 42);
    ans66 = opponent_in_a_row_dl & (opponent_for_canput<< 49);

    opponent_dr = player_for_canput& 0x007e7e7e7e7e7e00;
    opponent_in_a_row_dr = blank & (opponent_dr << 9);
    ans71 = opponent_in_a_row_dr & (opponent_for_canput<< 18);
    opponent_in_a_row_dr &= (opponent_dr << 18);
    ans72 = opponent_in_a_row_dr & (opponent_for_canput<< 27);
    opponent_in_a_row_dr &= (opponent_dr << 27);
    ans73 = opponent_in_a_row_dr & (opponent_for_canput<< 36);
    opponent_in_a_row_dr &= (opponent_dr << 36);
    ans74 = opponent_in_a_row_dr & (opponent_for_canput<< 45);
    opponent_in_a_row_dr &= (opponent_dr << 45);
    ans75 = opponent_in_a_row_dr & (opponent_for_canput<< 54);
    opponent_in_a_row_dr &= (opponent_dr << 54);
    ans76 = opponent_in_a_row_dr & (opponent_for_canput<< 63);


    opponent_ur = player_for_canput& 0x007e7e7e7e7e7e00;
    opponent_in_a_row_ur = blank & (opponent_ur >> 7);
    ans81 = opponent_in_a_row_ur & (opponent_for_canput>> 14);
    opponent_in_a_row_ur &= (opponent_ur >> 14);
    ans82 = opponent_in_a_row_ur & (opponent_for_canput>> 21);
    opponent_in_a_row_ur &= (opponent_ur >> 21);
    ans83 = opponent_in_a_row_ur & (opponent_for_canput>> 28);
    opponent_in_a_row_ur &= (opponent_ur >> 28);
    ans84 = opponent_in_a_row_ur & (opponent_for_canput>> 35);
    opponent_in_a_row_ur &= (opponent_ur >> 35);
    ans85 = opponent_in_a_row_ur & (opponent_for_canput>> 42);
    opponent_in_a_row_ur &= (opponent_ur >> 42);
    ans86 = opponent_in_a_row_ur & (opponent_for_canput>> 49);
    return ans11 | ans12 | ans13 | ans14 | ans15 | ans16 |
        ans21 | ans22 | ans23 | ans24 | ans25 | ans26 |
        ans31 | ans32 | ans33 | ans34 | ans35 | ans36 |
        ans41 | ans42 | ans43 | ans44 | ans45 | ans46 |
        ans51 | ans52 | ans53 | ans54 | ans55 | ans56 |
        ans61 | ans62 | ans63 | ans64 | ans65 | ans66 |
        ans71 | ans72 | ans73 | ans74 | ans75 | ans76 |
        ans81 | ans82 | ans83 | ans84 | ans85 | ans86;
}

U64 kyonkyon3::places_player_turn(U64 move) {
    ans_turn = move;
    H = 0;
    H = ((move & ans16) << 6); ans_turn |= H;
    H = ((move & ans15) << 5) | (H >> 1); ans_turn |= H;
    H = ((move & ans14) << 4) | (H >> 1); ans_turn |= H;
    H = ((move & ans13) << 3) | (H >> 1); ans_turn |= H;
    H = ((move & ans12) << 2) | (H >> 1); ans_turn |= H;
    H = ((move & ans11) << 1) | (H >> 1); ans_turn |= H;

    H = 0;
    H = ((move & ans26) >> 6); ans_turn |= H;
    H = ((move & ans25) >> 5) | (H << 1); ans_turn |= H;
    H = ((move & ans24) >> 4) | (H << 1); ans_turn |= H;
    H = ((move & ans23) >> 3) | (H << 1); ans_turn |= H;
    H = ((move & ans22) >> 2) | (H << 1); ans_turn |= H;
    H = ((move & ans21) >> 1) | (H << 1); ans_turn |= H;

    H = 0;
    H = ((move & ans36) << 48); ans_turn |= H;
    H = ((move & ans35) << 40) | (H >> 8); ans_turn |= H;
    H = ((move & ans34) << 32) | (H >> 8); ans_turn |= H;
    H = ((move & ans33) << 24) | (H >> 8); ans_turn |= H;
    H = ((move & ans32) << 16) | (H >> 8); ans_turn |= H;
    H = ((move & ans31) << 8) | (H >> 8); ans_turn |= H;

    H = 0;
    H = ((move & ans46) >> 48); ans_turn |= H;
    H = ((move & ans45) >> 40) | (H << 8); ans_turn |= H;
    H = ((move & ans44) >> 32) | (H << 8); ans_turn |= H;
    H = ((move & ans43) >> 24) | (H << 8); ans_turn |= H;
    H = ((move & ans42) >> 16) | (H << 8); ans_turn |= H;
    H = ((move & ans41) >> 8) | (H << 8); ans_turn |= H;

    H = 0;
    H = ((move & ans56) << 54); ans_turn |= H;
    H = ((move & ans55) << 45) | (H >> 9); ans_turn |= H;
    H = ((move & ans54) << 36) | (H >> 9); ans_turn |= H;
    H = ((move & ans53) << 27) | (H >> 9); ans_turn |= H;
    H = ((move & ans52) << 18) | (H >> 9); ans_turn |= H;
    H = ((move & ans51) << 9) | (H >> 9); ans_turn |= H;

    H = 0;
    H = ((move & ans76) >> 54); ans_turn |= H;
    H = ((move & ans75) >> 45) | (H << 9); ans_turn |= H;
    H = ((move & ans74) >> 36) | (H << 9); ans_turn |= H;
    H = ((move & ans73) >> 27) | (H << 9); ans_turn |= H;
    H = ((move & ans72) >> 18) | (H << 9); ans_turn |= H;
    H = ((move & ans71) >> 9) | (H << 9); ans_turn |= H;



    H = 0;
    H = ((move & ans66) >> 42); ans_turn |= H;
    H = ((move & ans65) >> 35) | (H << 7); ans_turn |= H;
    H = ((move & ans64) >> 28) | (H << 7); ans_turn |= H;
    H = ((move & ans63) >> 21) | (H << 7); ans_turn |= H;
    H = ((move & ans62) >> 14) | (H << 7); ans_turn |= H;
    H = ((move & ans61) >> 7) | (H << 7); ans_turn |= H;

    H = 0;
    H = ((move & ans86) << 42); ans_turn |= H;
    H = ((move & ans85) << 35) | (H >> 7); ans_turn |= H;
    H = ((move & ans84) << 28) | (H >> 7); ans_turn |= H;
    H = ((move & ans83) << 21) | (H >> 7); ans_turn |= H;
    H = ((move & ans82) << 14) | (H >> 7); ans_turn |= H;
    H = ((move & ans81) << 7) | (H >> 7); ans_turn |= H;

    return ans_turn;
}


void kyonkyon3::generatechild(int id_now) {
    
    U64 wherecanput = canput(id_now);
    childnum[id_now]=(int)bits_count(wherecanput);
    child[id_now] = edge;

    if (childnum[id_now]>0) {
        for (int i = 0; i < 64; i++) {
            if (wherecanput & (1ULL << i)) {
                U64 places_player_turn_ = places_player_turn(1ULL << i);
                player[edge]   = opponent[id_now] & (~places_player_turn_);
                opponent[edge] = player  [id_now] | places_player_turn_;
                //parent[edge] = id_now;
                edge++;
            }
        }
    }
    else {
        childnum[id_now] = 1;
        player[edge] = opponent[id_now];
        opponent[edge] = player[id_now];
        //parent[edge] = id_now;
        edge++;
    }
}
U64 kyonkyon3::bits_count(U64 VALUE) {
    VALUE = (VALUE & 0x5555555555555555) + (VALUE >> 1 & 0x5555555555555555);
    VALUE = (VALUE & 0x3333333333333333) + (VALUE >> 2 & 0x3333333333333333);
    VALUE = (VALUE & 0x0f0f0f0f0f0f0f0f) + (VALUE >> 4 & 0x0f0f0f0f0f0f0f0f);
    VALUE = (VALUE & 0x00ff00ff00ff00ff) + (VALUE >> 8 & 0x00ff00ff00ff00ff);
    VALUE = (VALUE & 0x0000ffff0000ffff) + (VALUE >> 16 & 0x0000ffff0000ffff);
    VALUE = (VALUE & 0x00000000ffffffff) + (VALUE >> 32 & 0x00000000ffffffff);
    return VALUE;
}