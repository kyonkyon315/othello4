#include "kyonkyon3.h"
#include <iostream>

using namespace std;

void kyonkyon3::getvalue(int id){
	canput_player = (int)bits_count(canput(id));
	canput_opponent = (int)bits_count(canput_enemy(id));
	if (canput_player!=0 || canput_opponent!=0) {
		value[id] = PARAMS->value(player[id], opponent[id]);
		//+ (int)(canput_player << 5)
		//- (int)(canput_opponent << 5);
		/*
		if ((player[id] | opponent[id]) & edge_mask) {
			evaluate1 = (player[id] | opponent[id]) & 0x8000000000000000;
			evaluate2 = (player[id] | opponent[id]) & 0x0100000000000000;
			evaluate3 = (player[id] | opponent[id]) & 0x0000000000000080;
			evaluate4 = (player[id] | opponent[id]) & 0x0000000000000001;
			evaluate_unite = (evaluate1 >> 1) | (evaluate1 >> 8) | (evaluate1 >> 9) |
				(evaluate2 << 1) | (evaluate2 >> 8) | (evaluate2 >> 7) |
				(evaluate3 << 8) | (evaluate3 << 7) | (evaluate3 >> 1) |
				(evaluate4 << 1) | (evaluate4 << 8) | (evaluate4 << 9);
			value[id] =
				(int)(
					(bits_count(canput(id)) << 2) +
					(bits_count(0x8100000000000081 & player[id]) << 6) +
					(bits_count(evaluate_unite & player[id]) << 5) +
					(bits_count(0x3c0081818181003c & player[id]) << 2) +
					(bits_count(0x00003c3c3c3c0000 & player[id]) << 1) +
					(bits_count((0x4281000000008142 & opponent[id]) & (~evaluate_unite)) << 3) +
					(bits_count(0x003b424242423b00 & opponent[id]) << 1) +
					(bits_count((0x0042000000004200 & opponent[id]) & (~evaluate_unite)) << 4) +
					(bits_count(evaluate_unite & player[id]) << 2)
					)
				-
				(int)(
					(bits_count(canput_enemy(id)) << 2) +
					(bits_count(0x8100000000000081 & opponent[id]) << 6) +
					(bits_count(evaluate_unite & opponent[id]) << 5) +
					(bits_count(0x3c0081818181003c & opponent[id]) << 2) +
					(bits_count(0x00003c3c3c3c0000 & opponent[id]) << 1) +
					(bits_count((0x4281000000008142 & player[id]) & (~evaluate_unite)) << 3) +
					(bits_count(0x003b424242423b00 & player[id]) << 1) +
					(bits_count((0x0042000000004200 & player[id]) & (~evaluate_unite)) << 4) +
					(bits_count(evaluate_unite & opponent[id]) << 2)
					);
		}
		else {
			value[id] =
				(int)(
					(bits_count(canput(id)) << 2) +
					(bits_count(0x8100000000000081 & player[id]) << 6) +
					(bits_count(0x3c0081818181003c & player[id]) << 1) +
					(bits_count(0x00003c3c3c3c0000 & player[id]) << 1) +
					(bits_count(0x4281000000008142 & opponent[id]) << 3) +
					(bits_count(0x003b424242423b00 & opponent[id]) << 1) +
					(bits_count(0x0042000000004200 & opponent[id]) << 4)
					)

				-
				(int)(
					(bits_count(canput_enemy(id)) << 2) +
					(bits_count(0x8100000000000081 & opponent[id]) << 6) +
					(bits_count(0x3c0081818181003c & opponent[id]) << 1) +
					(bits_count(0x00003c3c3c3c0000 & opponent[id]) << 1) +
					(bits_count(0x4281000000008142 & player[id]) << 3) +
					(bits_count(0x003b424242423b00 & player[id]) << 1) +
					(bits_count(0x0042000000004200 & player[id]) << 4)
					)
				;
		}
		*/
	}
	else {
		value[id] =
			(int)(bits_count(player[id]) - bits_count(opponent[id])) << 6;//8*–‡”·
	}
}