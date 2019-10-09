#include "bsp.h"
//#include <stdio.h>

// derivation see the accompanying ppt
BspNode CreateNode (const Vec2 &p1, const Vec2 &p2)
{
	BspNode node = (BspNode) malloc (sizeof (struct _bspnode));
	double a = p1[1] - p2[1]; // y1 - y2
	double b = p1[0] - p2[0]; // x1 - x2
	double scale = 1./sqrt (a*a + b*b);
	
	node->coeff = Vec3 (a*scale, -b*scale, (b*p1[1]-a*p1[0])*scale);
	node->rightChild = node->leftChild = NULL;
	return node;
}

void AddToRight (BspNode parent, BspNode child)
{
	parent->rightChild = child; 
}

void AddToLeft (BspNode parent, BspNode child)
{
	parent->leftChild = child; 
}


float r = 1;
// recursive call
// return 0 if free; 1 if solid
int QueryBspTree (BspNode root, const Vec2 &xy) 
{
	// exit condition
	float fxy = root->coeff[0]*xy[0] + root->coeff[1]*xy[1] + root->coeff[2];
	
	if (fxy > r) {
		if (root->rightChild == NULL)
			return 1;
		else 
			return QueryBspTree (root->rightChild, xy);
	} else {
		if (root->leftChild == NULL)
			return 0;
		else 
			return QueryBspTree (root->leftChild, xy);
	}
		
}
float rMaro = 2.5;
int QueryBspTreeMario (BspNode root, const Vec2 &xy) 
{
	// exit condition
	float fxy = root->coeff[0]*xy[0] + root->coeff[1]*xy[1] + root->coeff[2];
	
	if (fxy > rMaro) {
		if (root->rightChild == NULL)
			return 1;
		else 
			return QueryBspTreeMario (root->rightChild, xy);
	} else {
		if (root->leftChild == NULL)
			return 0;
		else 
			return QueryBspTreeMario (root->leftChild, xy);
	}
		
}
int rcamera = 1;
int QueryBspTreeforCamera (BspNode root, const Vec2 &xy) 
{
	// exit condition
	float fxy = root->coeff[0]*xy[0] + root->coeff[1]*xy[1] + root->coeff[2];
	
	if (fxy > rcamera) {
		if (root->rightChild == NULL)
			return 1;
		else 
			return QueryBspTreeforCamera (root->rightChild, xy);
	} else {
		if (root->leftChild == NULL)
			return 0;
		else 
			return QueryBspTreeforCamera (root->leftChild, xy);
	}
		
}
#if 0
void main ()
{
	extern BspNode BuildTree();

	BspNode root = BuildTree();
	
	while (1) {
		float x,y;

		printf ("point (x,y): ");
		scanf ("%f%f", &x,&y);
		
		printf ("result: %d\n",	QueryBspTree (root, Vec2(x,y)));;
	}
}
#endif