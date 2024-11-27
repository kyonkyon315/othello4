#include "params.h"
#define U64 unsigned long long
using namespace std;
/*
******************|ƒpƒ‰ƒ[ƒ^|*********************
* 3^10 * 16 = 59049 * 16 = 944784 params
*
* x x x x 0
* x x x o 1
* x x o x 2
* x x o o 3
* x o x x 4
* x o x o 5
* x o o x 6
* x o o o 7
* o x x x 8
* o x x o 9
* o x o x a
* o x o o b
* o o x x c
* o o x o d
* o o o x e
* o o o o f
*
***********************************************
*/
U64 square::translate(int kind, U64& input) {
	
	switch (kind) {
	case 0:
		/*
		   o         o
		 o o o o o o o o
			mask11=0x00000000000002ff
			mask12=0x0000000000004000


		*/
		ans = input & mask11;
		ans |= (input & mask12) >> 6;
		               
		return ans;
	case 1:
		/*


					  o
					o o
				  o|o o
				o o o o
		 ---------------------------

			mask21=0x000000000000000f;
			mask22=0x0000000000000700;
			mask23=0x0000000000030000;
			mask24=0x0000000001000000;

		*/
		ans = (input & mask21);
		ans |= ((input & mask22) >> 4);
		ans |= ((input & mask23) >> 9);
		ans |= ((input & mask24) >> 15);
		              
		return ans;
	case 2:
		/*

		x x x o o o o o
		x x x o o o o o


					mask31=0x000000000000001f;
					mask32=0x0000000000001f00;

		*/
		ans = (input & mask31);
		ans |= ((input & mask32) >> 3);
		            
		return ans;
	case 3:
		/*

		4.
* x x o o o o x x
* x o o o o o o x
					mask41=0x000000000000007e;
					mask42=0x0000000000003c00;

		*/
		ans = ((input & mask41) >> 1);
		ans |= ((input & mask42) >> 4);
		          
		return ans;
	case 4:
		/*
		5.
		x x x o x x x x
		x x o o
		x o o o
		o o o o

			U64 mask51 = 0x1000000000000000;
			U64 mask52 = 0x0030000000000000;
			U64 mask53 = 0x0000700000000000;
			U64 mask54 = 0x000000f000000000;
	*/
		ans = (input & mask51) >> 51;
		ans |= ((input & mask52) >> 45);
		ans |= ((input & mask53) >> 40);
		ans |= ((input & mask54) >> 36);
		        
		return ans;
	case 5:
		/*

		6.
 x x x x x x x x
 x x x x x x x x
 x x o o o o x x
 x x o o o x x x
 x x o o x x x x
 x x o x x x x x
 x x x x x x x x
 x x x x x x x x

 U64 mask61=0x00003c0000000000;
 U64 mask62=0x0000003800000000;
 U64 mask63=0x0000000030000000;
 U64 mask64=0x0000000000200000;

		*/
		ans = (input & mask61) >> 36;
		ans |= ((input & mask62) >> 32);
		ans |= ((input & mask63) >> 27);
		ans |= ((input & mask64) >> 21);
		      
		return ans;
	case 6:
		/*
		7.
			x x x x o o x x
			x x x x o o o x
			x x x x x o o o
			x x x x x x o o

				*/
		ans = (input & mask71);
		ans |= ((input & mask72) >> 6);
		ans |= ((input & mask73) >> 12);
		ans |= ((input & mask74) >> 18);
		   
		return ans;
	case 7:
		/*

		8.
	o x x x x x x x   x x x x x x x x   x x x x x x x x   x x x x x x x x
	x o x x x x x x   x x x x x x x x   x x x x x x x x   x x x x x x x x
	x x o x x x x x   x x x x x x x x   x x x x x x x x   x x x x x x x x
	x x x o x x x x   x x x x x x x x   x x x x x x x x   x x x x x x x x
	x x x x o x x x   o x x x o x x x   x x x x x x x x   x x x x x x x x
	x x x x x o x x   x o x x x o x x   x x x x x x x x   x x x x x x x x
	x x x x x x o o   x x o x x x o o   o x o x o x o o   x x x x x x o o
	x x x x x x o o   x x x o x x o o   x o x o x o o o   o o o o o o o o

			 U64 mask81=0x8040201008040303
			 U64 mask82=0x8040201000000000
			 U64 mask83=0x0000000088440000
			 U64 mask84=0x000000000000a800
			 U64 mask85=0x00000000000003ff
		*/

		ans = input & mask81;
		ans |= (ans & mask82) >> 32;
		ans |= (ans & mask83) >> 16;
		ans |= (ans & mask84) >> 8;
		ans &= mask85;
		 
		return ans;
	case 8:
		/*

		9.


						x x x x x x x x | x x x x x x x x | x x x x x x x x | x x x x x x x x
			   o x x x x x x x | x x x x x x x o | x x x x x x x x | x x x x x x x x
			   x o x x x x x x | x x x x x x x x | x x x x x x x x | x x x x x x x x
			   x x o x x x x x | o x x x x x x x | x x x x x x x x | x x x x x x x x
			   x x x o x x x x | x o x x x x x x | x o x x x x x x | x x x x x x x x
			   x x x x o x x x | x x o x x x x x | x x o x x x x o | x x x x x x x o
			   x x x x x o o x | x x x o x x o x | x x x o x x o x | x o x o x x o x
			   x x x x x o o o | x x x x o o o o | o x x x o o o o | o x o x o o o o

		U64 mask91=0x0000000000000207;
		U64 mask92=0x0080402010080400;
		U64 mask93=0x0001008000000000;
		U64 mask94=0x0000000040200000;
		U64 mask95=0x0000000000015000;
		U64 mask96=0x00000000000003ff;

		*/
		ans = input & mask91;
		ans |= (input & mask92) >> 7;
		ans |= (ans & mask93) >> 32;
		ans |= (ans & mask94) >> 16;
		ans |= (ans & mask95) >> 8;
		ans &= mask96;


		return ans;


	case 9:
		/*
		10.
			 x x o x x x x x | x x x x x x x x | x x x x x x x x | x x x x x x x x
			 x x x o x x x x | x x x x x x x x | x x x x x x x x | x x x x x x x x
			 x x x x o x x x | x x x x x x x x | x x x x x x x x | x x x x x x x x
			 x x x x x o o x | x x x x x x x x | x x x x x x x x | x x x x x x x x
			 x x x x x o o o | o x x x x o o o | x x x x x x x x | x x x x x x x x
			 x x x x x x o o | x o x x x x o o | x x x x x x x x | x x x x x x x x
			 x x x x x x x x | x x o x x x x x | o x o x x o o o | x x x x x x o o
			 x x x x x x x x | x x x o o x x x | x o x o o x o o | o o o o o o o o

		maska1=0x0000000607030000;
		maska2=0x2010080600000000;
		maska3=0x0000000087430000;
		maska4=0x000000000000a400;
		maska5=0x00000000000003ff;

	*/

		ans = (input & maska1);
		ans |= ((input & maska2) >> 30);
		ans |= ((ans & maska3) >> 16);
		ans |= ((ans & maska4) >> 8);
		ans &= maska5;
		
		return ans;

	case 10:
		/*
		11.
			 x x x o x x x x | x x x x x x x x | x x x x x x x x | x x x x x x x x
			 x x x x o x x x | x x x x x x x x | x x x x x x x x | x x x x x x x x
			 x x x x x o x o | x x x x x x x x | x x x x x x x x | x x x x x x x x
			 x x x x x x o o | x x x x x x x x | x x x x x x x x | x x x x x x x x
			 x x x x x x o o | o x x x x x o o | x x x x x x x x | x x x x x x x x
			 x x x x x x o o | x o x x x x o o | x x x x x x x x | x x x x x x x x
			 x x x x x x x x | x x o x o x x x | o x o x o x o o | x x x x o x o o
			 x x x x x x x x | x x x o o x x x | x o x o o x o o | o o o o o x o o

		maskb1=0x0000000003030000;
		maskb2=0x1008050300000000;
		maskb3=0x0000000083430000;
		maskb4=0x000000000000a000;
		maskb5=0x0000000000000800;
		maskb6=0x00000000000003ff;

	*/

		ans = (input & maskb1);
		ans |= ((input & maskb2) >> 29);
		ans |= ((ans & maskb3) >> 16);
		ans |= ((ans & maskb4) >> 8);
		ans |= ((ans & maskb5) >> 9);
		ans &= maskb6;
		
		return ans;

	case 11:
		/*
		12.
			 x x x x x x x x | x x x x x x x x | x x x x x x x x | x x x x x x x x
			 x x x x x x x x | x x x x x x x x | x x x x x x x x | x x x x x x x x
			 x x x x x x x x | x x x x x x x x | x x x x x x x x | x x x x x x x x
			 x x x x x x x o | x x x x x x x x | x x x x x x x x | x x x x x x x x
			 x x x x x x x o | x x x x x x x o | x x x x x x x x | x x x x x x x x
			 x x x x x x x o | x x x x x x x o | x x x x x x x o | x x x x x x x x
			 x x x x x x o o | x x x x x x o o | x x x x x x o o | x x x x x x x x
			 x x x o o o o o | o x x o o o o o | o o x o o o o o | x x x x x x x x

		maskc1=0x0000000000000318;
		maskc2=0x0000000100000000;
		maskc3=0x0000000001000000;
		maskc4=0x0000000000010000;
	*/

		ans = (input & maskc1);
		ans |= ((input & maskc2) >> 25);
		ans |= ((input & maskc3) >> 18);
		ans |= ((input & maskc4) >> 11);
		
		return ans;

	case 12:
		/*
		13.
			 x x x x x x x x | x x x x x x x x | x x x x x x x x | x x x x x x x x
			 x x x x x x x x | x x x x x x x x | x x x x x x x x | x x x x x x x x
			 x x o x o x o x | x x x x x x x x | x x x x x x x x | x x x x x x x x
			 x x x o x o x x | x x o o o o o x | x x x x x x x x | x x x x x x x x
			 x x o x o x o x | x x x x x x x x | x x x x x x x x | x x x x x x x x
			 x x x o x o x x | x x o o o o o x | x x x x x x x x | x x x x x x x x
			 x x x x x x x x | x x x x x x x x | x x x x x x x x | x x x x x x x x
			 x x x x x x x x | x x x x x x x x | x x x x x x x x | x x x x x x x x

		maskd1=0x00002b002b000000;
		maskd2=0x0000001400140000;
		maskd3=0x0000003e00000000;
		maskd4=0x00000000003e0000;

	*/

		ans = (input & maskd1) >> 8;
		ans |= (input & maskd2);
		ans = ((ans & maskd3) >> 28) | ((ans & maskd4) >> 17);

	
		return ans;

	case 13:
		/*
		14.
			 x x x x x x x x | x x x x x x x x | x x x x x x x x | x x x x x x x x
			 x x x x x x x x | x x x x x x x x | x x x x x x x x | x x x x x x x x
			 x x x x x x x x | x x x x x x x x | x x x x x x x x | x x x x x x x x
			 x x x x x x x x | x x x x x x x x | x x x x x x x x | x x x x x x x x
			 x x x x o x x o | x x x x x x x x | x x x x x x x x | x x x x x x x x
			 x x x x x o x o | x x x x x x x x | x x x x x x x x | x x x x x x x x
			 x x x x x x o o | o x x o x x o o | x x x x x x x x | x x x x x x x x
			 x x x x o o o o | x o x o o o o o | x x x x x x x x | x x x x x x x x

		maske1=0x000000000000030f;
		maske2=0x0000000009050000;
		maske3=0x0000000000008000;
		maske4=0x0000000000001000;
		maske5=0x00000000000003ff;
	*/

		ans = (input & maske1);
		ans |= (input & maske2) >> 12;
		ans |= ((ans & maske3) >> 8);
		ans |= ((ans & maske4) >> 7);
		ans &= maske5;
		

		return ans;

	case 14:
		/*
		15.
			 x x x x x x x x | x x x x x x x x | x x x x x x x x | x x x x x x x x
			 x x x x x x x x | x x x x x x x x | x x x x x x x x | x x x x x x x x
			 x x x x x x x x | x x x x x x x x | x x x x x x x x | x x x x x x x x
			 x x x x x x x x | x x x x x x x x | x x x x x x x x | x x x x x x x x
			 x x x x x x x x | x x x x x x x x | x x x x x x x x | x x x x x x x x
			 x x x x x x x x | x x x x x x x x | x x x x x x x x | x x x x x x x x
			 o o o o o o o o | o x x o x x o o | x x x x x x x x | x x x x x x x x
			 x x x x x x o o | x o x o o o o o | x x x x x x x x | x x x x x x x x

		maskf1=0x000000000000ff00;
		maskf2=0x0000000000000003;
	*/

		ans = (input & maskf2);
		ans |= ((input & maskf1) >> 6);

		return ans;

	case 15:
		/*
		16.
			 x x x x x x x x | x x x x x x x x | x x x x x x x x | x x x x x x x x
			 x x x x x x x x | x x x x x x x x | x x x x x x x x | x x x x x x x x
			 x x x x x x x x | x x x x x x x x | x x x x x x x x | x x x x x x x x
			 x x x x x x x x | x x x x x x x x | x x x x x x x x | x x x x x x x x
			 x x x x o x x x | x x x x x x x x | x x x x x x x x | x x x x x x x x
			 x x x x x o o o | x x x x x x x x | x x x x x x x x | x x x x x x x x
			 x x x x x o o o | x o x x x o o o | x x x x x x x x | x x x x x x x x
			 x x x x x o o o | x x o o o o o o | x x x x x x x x | x x x x x x x x

		maskg1=0x0000000000000307;
		maskg2=0x0000000000000400;
		maskg3=0x0000000000070000;
		maskg4=0x0000000008000000;
	*/

		ans = (input & maskg1);
		ans |= ((input & maskg2) >> 7);
		ans |= ((input & maskg3) >> 12);
		ans |= ((input & maskg4) >> 20);
		
		return ans;
	}
	std::cerr << "In 'square::translate(int kind, U64& input)' kind is out of range.\n";
	return 0;
}
/*
  o o o o o o o o    o o o o x x x x    o o o o o x x x    x o o o o o o x
  x o x x x x o x    o o o x x x x x    o o o o o x x x    x x o o o o x x
  x x x x x x x x    o o x x x x x x    x x x x x x x x    x x x x x x x x
  x x x x x x x x    o x x x x x x x    x x x x x x x x    x x x x x x x x
  x x x x x x x x    x x x x x x x x    x x x x x x x x    x x x x x x x x
  x x x x x x x x    x x x x x x x x    x x x x x x x x    x x x x x x x x
  x x x x x x x x    x x x x x x x x    x x x x x x x x    x x x x x x x x
  x x x x x x x x    x x x x x x x x    x x x x x x x x    x x x x x x x x


  x x x o x x x x    x x x x x x x x    o o x x x x x x    o o x x x x x x
  x x o o x x x x    x x x x x x x x    o o o x x x x x    o o x x x x x x
  x o o o x x x x    x x o o o o x x    x o o o x x x x    x x o x x x x x
  o o o o x x x x    x x o o o x x x    x x o o x x x x    x x x o x x x x
  x x x x x x x x    x x o o x x x x    x x x x x x x x    x x x x o x x x
  x x x x x x x x    x x o x x x x x    x x x x x x x x    x x x x x o x x
  x x x x x x x x    x x x x x x x x    x x x x x x x x    x x x x x x o x
  x x x x x x x x    x x x x x x x x    x x x x x x x x    x x x x x x x o

  o o o x x x x x    x x o o x x x x    x x x o o o o x    o o o o o x x x
  x o o x x x x x    x x o o o x x x    x x x o o o x x    o o x x x x x x
  x x x o x x x x    x x x o o x x x    x x x x x o x x    o x x x x x x x
  x x x x o x x x    x x x x x o x x    x x x x x x o x    o x x x x x x x
  x x x x x o x x    x x x x x x o x    x x x x x x x o    o x x x x x x x
  x x x x x x o x    x x x x x x x o    x x x x x x x x    x x x x x x x x
  x x x x x x x o    x x x x x x x x    x x x x x x x x    x x x x x x x x
  x x x x x x x x    x x x x x x x x    x x x x x x x x    x x x x x x x x

  x x x x x x x x    o o o o x x x x    o o x x x x x x    o o o x x x x x
  x x x x x x x x    o o x x x x x x    o o o o o o o o    o o o x x x x x
  x x o x o x o x    o x o x x x x x    x x x x x x x x    o o o x x x x x
  x x x o x o x x    o x x o x x x x    x x x x x x x x    x x x o x x x x
  x x o x o x o x    x x x x x x x x    x x x x x x x x    x x x x x x x x
  x x x o x o x x    x x x x x x x x    x x x x x x x x    x x x x x x x x
  x x x x x x x x    x x x x x x x x    x x x x x x x x    x x x x x x x x
  x x x x x x x x    x x x x x x x x    x x x x x x x x    x x x x x x x x

  x x x x x x x x    x x x x x x x x    x x x x x x x x    x x x x x x x x













*/

