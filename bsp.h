#include <vector>
using namespace std;

#include "svl/svl.h"

typedef struct _bspnode *BspNode;

struct _bspnode {
	Vec3 coeff;  // bsp node equation: coeff[0]*x + coeff[1]*y + coeff[2] = 0
	BspNode leftChild;
	BspNode rightChild;
};


typedef vector<Vec2> LOOP;