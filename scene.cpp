#include "bsp.h"
extern BspNode CreateNode (const Vec2&, const Vec2&);
extern void AddToRight (BspNode, BspNode);
extern void AddToLeft (BspNode, BspNode);

// this file returns ...

vector <LOOP> loops;


// test scene 1: triangle (concave)
BspNode BuildTree1()
{
	Vec2 v[3];
	int npoints = 3;
	
	// loops construction
	LOOP outer, inner;
	loops.push_back (outer);  // empty outer loop
	inner.push_back (v[0] = Vec2(6,0));
	inner.push_back (v[1] = Vec2(0,4));
	inner.push_back (v[2] = Vec2(6,4));
	loops.push_back (inner);
	
	// bsp tree construction
	BspNode l[3], root;
	for (int i =0; i < npoints; i++) 
		l[i] = CreateNode (v[i], v[(i+1)%npoints]);

	root = l[0];
	
	AddToLeft (root, l[1]);
	AddToLeft (l[1], l[2]);

	return root;
}

// test scene 2: "concave"
static BspNode BuildTree2()
{
	Vec2 v[8];
	int npoints = 8;
	
	// loops construction
	LOOP outer;
	outer.push_back (v[0] = Vec2(0,0));
	outer.push_back (v[1] = Vec2(0,-1));
	outer.push_back (v[2] = Vec2(2,-1));
	outer.push_back (v[3] = Vec2(2,1));
	outer.push_back (v[4] = Vec2(-2,1));
	outer.push_back (v[5] = Vec2(-2,-1));
	outer.push_back (v[6] = Vec2(-1,-1));
	outer.push_back (v[7] = Vec2(-1,0));
	loops.push_back (outer);  // empty outer loop


	// bsp tree construction
	BspNode root, l[8];
	for (int i =0; i < npoints; i++) 
		l[i] = CreateNode (v[i], v[(i+1)%npoints]);

	root = l[0];
	AddToRight (l[0], l[1]); AddToLeft (l[0],l[7]);
	AddToRight (l[1], l[2]); AddToRight (l[2], l[3]);
	AddToRight (l[7], l[3]); AddToRight (l[3], l[4]);
	AddToLeft (l[7], l[5]); AddToRight (l[5], l[6]);
	
	AddToRight (l[6],l[4]);   // correction! (4/7/2014)

	return root;
}

// test scene 3: "concave"
static BspNode BuildTree3()
{
	Vec2 v[7];
	int npoints = 7;
	
	// loops construction
	LOOP outer, inner;
	outer.push_back (v[0] = Vec2(-20,-20));
	outer.push_back (v[1] = Vec2(20,-20));
	outer.push_back (v[2] = Vec2(20,20));
	outer.push_back (v[3] = Vec2(-20,20));
	loops.push_back (outer);  // outer loop

	inner.push_back (v[4] = Vec2(0,0));
	inner.push_back (v[5] = Vec2(0,10));
	inner.push_back (v[6] = Vec2(10,0));
	loops.push_back (inner);  // inner loop


	// bsp tree construction
	BspNode root, l[7];
	int i;
	// outer: [0-3]
	for (i =0; i < 4; i++) 
		l[i] = CreateNode (v[i], v[(i+1)%4]);  // [01],[12],[23],[30]
	// inner: [4-6]
	for (i = 0; i < 3; i++) 
		l[i+4] = CreateNode (v[i +4], v[(i+1)%3 +4]);  // [45],[56],[64]
	
	root = l[0];

	AddToRight (l[0], l[1]); 
	AddToRight (l[1], l[2]); 
	AddToRight (l[2], l[3]);
	AddToRight (l[3], l[4]);
	AddToLeft (l[4], l[5]); AddToLeft (l[5], l[6]);
	
	/*root = l[6];

	AddToRight (l[6], l[0]);
	AddToRight (l[0], l[1]);
	AddToRight (l[1], l[2]);

	AddToLeft (l[6], l[4]);
	AddToRight (l[4], l[0]);
	AddToRight (l[0], l[3]);
	AddToLeft (l[4], l[5]);
	AddToRight (l[5], l[1]);
	AddToRight (l[1], l[2]);*/


	return root;
}


static BspNode BuildTree4()       ////¥ª¥k¨â®æ
{
	Vec2 v[12];
	int npoints = 12;

	// loops construction
	LOOP outer, inner1 , inner2;
	outer.push_back (v[0] = Vec2(-20,20));
	outer.push_back (v[1] = Vec2(-20,-20));
	outer.push_back (v[2] = Vec2(20,-20));
	outer.push_back (v[3] = Vec2(20,20));
	loops.push_back (outer);  // outer loop

	inner1.push_back (v[4] = Vec2(-14,4));
	inner1.push_back (v[5] = Vec2(-6,4));
	inner1.push_back (v[6] = Vec2(-6,-4));
	inner1.push_back (v[7] = Vec2(-14,-4));
	loops.push_back (inner1);  // inner loop


	inner2.push_back (v[8] = Vec2(6,4));
	inner2.push_back (v[9] = Vec2(14,4));
	inner2.push_back (v[10] = Vec2(14,-4));
	inner2.push_back (v[11] = Vec2(6,-4));
	loops.push_back (inner2);  // inner2 loop

	BspNode root, l[12];
	int i;
	// outer: [0-3]
	for (i =0; i < 4; i++) 
		l[i] = CreateNode (v[i], v[(i+1)%4]);  // [01],[12],[23],[30]
	// inner: [4-7]
	for (i = 0; i < 4; i++) 
		l[i+4] = CreateNode (v[i +4], v[(i+1)%4 +4]);  // [45],[56],[67],[74]

	// inner: [8-11]
	for (i = 0; i < 4; i++) 
		l[i+8] = CreateNode (v[i +8], v[(i+1)%4 +8]);  // [89],[9 10],[10 11],[11 8]

	/*
	root = l[5];

	//AddToLeft (l[6], l[4]);


	AddToRight (l[5], l[9]);
	AddToRight (l[9], l[1]);
	AddToRight (l[1], l[2]);
	AddToRight (l[2], l[3]);


	AddToLeft (l[9], l[8]);
	AddToRight (l[8], l[3]);

	AddToLeft (l[8], l[1]);
	AddToRight (l[1], l[10]);
	AddToLeft (l[10], l[11]);


	AddToLeft (l[5], l[4]);
	AddToRight (l[4], l[0]);
	AddToRight (l[0], l[3]);

	AddToLeft (l[4], l[0]);
	AddToRight (l[0], l[1]);
	AddToRight (l[1], l[6]);
	AddToLeft (l[6], l[7]);


  */

#if 0
	/*root = l[0];

	AddToRight (l[0], l[1]);
	AddToRight (l[1], l[2]);
	AddToRight (l[2], l[3]);
	AddToRight (l[3], l[7]);

	AddToLeft (l[7], l[11]);
	AddToLeft (l[11], l[8]);
	AddToLeft (l[8], l[9]);
	AddToLeft (l[9], l[10]);
	
	AddToRight (l[11], l[4]);
	AddToLeft (l[4], l[5]);
	AddToLeft (l[5], l[6]);*/
#endif

#if 1

	root = l[0];

	AddToRight (l[0], l[1]);
	AddToRight (l[1], l[2]);
	AddToRight (l[2], l[3]);
	AddToRight (l[3], l[6]);

	AddToLeft (l[6], l[7]);
	AddToLeft (l[7], l[4]);
	AddToLeft (l[4], l[5]);
	AddToRight (l[5], l[9]);
	AddToLeft (l[9], l[11]);

#endif


	//tern Vec2 move;
	//ve = Vec2 (0,0);
	return root;

}



static BspNode BuildTree5()       ////4®æ
{
	Vec2 v[20];
	int npoints = 20;

	// loops construction
	LOOP outer, inner1 , inner2, inner3, inner4;
	outer.push_back (v[0] = Vec2(-20,20));
	outer.push_back (v[1] = Vec2(-20,-20));
	outer.push_back (v[2] = Vec2(20,-20));
	outer.push_back (v[3] = Vec2(20,20));
	loops.push_back (outer);  // outer loop

	inner1.push_back (v[4] = Vec2(-14,14));
	inner1.push_back (v[5] = Vec2(-6,14));
	inner1.push_back (v[6] = Vec2(-6,6));
	inner1.push_back (v[7] = Vec2(-14,6));
	loops.push_back (inner1);  // inner loop


	inner2.push_back (v[8] = Vec2(6,14));
	inner2.push_back (v[9] = Vec2(14,14));
	inner2.push_back (v[10] = Vec2(14,6));
	inner2.push_back (v[11] = Vec2(6,6));
	loops.push_back (inner2);  // inner2 loop


	inner3.push_back (v[12] = Vec2(6,-6));
	inner3.push_back (v[13] = Vec2(14,-6));
	inner3.push_back (v[14] = Vec2(14,-14));
	inner3.push_back (v[15] = Vec2(6,-14));
	loops.push_back (inner3);  // inner2 loop


	inner4.push_back (v[16] = Vec2(-14,-6));
	inner4.push_back (v[17] = Vec2(-6,-6));
	inner4.push_back (v[18] = Vec2(-6,-14));
	inner4.push_back (v[19] = Vec2(-14,-14));
	loops.push_back (inner4);  // inner loop


	BspNode root, l[20];
	int i;
	// outer: [0-3]
	for (i =0; i < 4; i++) 
		l[i] = CreateNode (v[i], v[(i+1)%4]);  // [01],[12],[23],[30]
	// inner: [4-7]
	for (i = 0; i < 4; i++) 
		l[i+4] = CreateNode (v[i +4], v[(i+1)%4 +4]);  // [45],[56],[67],[74]

	// inner: [8-11]
	for (i = 0; i < 4; i++) 
		l[i+8] = CreateNode (v[i +8], v[(i+1)%4 +8]);  // [89],[9 10],[10 11],[11 8]

	// inner: [12 - 15]
	for (i = 0; i < 4; i++) 
		l[i+12] = CreateNode (v[i +12], v[(i+1)%4 +12]);  // [89],[9 10],[10 11],[11 8]

	// inner: [16 - 19]
	for (i = 0; i < 4; i++) 
		l[i+16] = CreateNode (v[i +16], v[(i+1)%4 +16]);  // [89],[9 10],[10 11],[11 8]



	root = l[0];

	AddToRight (l[0], l[1]);
	AddToRight (l[1], l[2]);
	AddToRight (l[2], l[3]);
	AddToRight (l[3], l[7]);
	AddToLeft (l[7], l[11]);

	AddToLeft (l[11], l[8]);
	AddToLeft (l[8], l[12]);
	AddToRight (l[12], l[9]);
	AddToLeft (l[9], l[10]);
	AddToLeft (l[12], l[13]);
	AddToLeft (l[13], l[14]);

	AddToRight (l[11], l[4]);
	AddToLeft (l[4], l[16]);
	AddToLeft (l[16], l[17]);
	AddToLeft (l[17], l[18]);
	AddToRight (l[16], l[5]);
	AddToLeft (l[5], l[6]);

	return root;
}

BspNode BuildTree (int which)
{
	loops.clear();

	switch (which) {
	case 1:
		return BuildTree1();
		break;
	case 2:
		return BuildTree2();
		break;
	case 3:
		return BuildTree3();
		break;

	case 4:
		return BuildTree4();
		break;
	case 5:
		return BuildTree5();
		break;

  
	}
	return NULL;
}
