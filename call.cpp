#include <gl/glew.h>
#include <gl/glut.h>
#include "gluit.h"
#include "svl/svl.h"
#include "gl/glpng.h"
#include <math.h>
#include <time.h>
#pragma comment (lib, "glew32.lib")
#pragma comment (lib, "glpngd.lib")

#include <vector>
#include <iostream>
using namespace std;

void setEnd(Vec2 e);

typedef struct {
	int i;
	int j;
} TILE;  // the (i,j) of the map

extern vector<TILE> myfindpath (TILE,TILE,int*,int,int);
const int MAP_WIDTH = 41;
const int MAP_HEIGHT = 41;

//
// note the index (i,j) is [z,x], when the map is drawing on ZX plane
//
int map[ MAP_WIDTH * MAP_HEIGHT ] = 
{

// 0001020304050607080910111213141516171819
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,   // 00
	1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,1,   // 01
	1,9,9,1,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1,   // 02
	1,9,9,1,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1,   // 03
	1,9,1,1,1,1,9,9,1,9,1,9,1,1,1,1,9,9,1,1,   // 04
	1,9,1,1,9,1,1,1,1,9,1,1,1,1,9,1,1,1,1,1,   // 05
	1,9,9,9,9,1,1,1,1,1,1,9,9,9,9,1,1,1,1,1,   // 06
	1,9,9,9,9,9,9,9,9,1,1,1,9,9,9,9,9,9,9,1,   // 07
	1,9,1,1,1,1,1,1,1,1,1,9,1,1,1,1,1,1,1,1,   // 08
	1,9,1,9,9,9,9,9,9,9,1,1,9,9,9,9,9,9,9,1,   // 09
	1,9,1,1,1,1,9,1,1,9,1,1,1,1,1,1,1,1,1,1,   // 10
	1,9,9,9,9,9,1,9,1,9,1,9,9,9,9,9,1,1,1,1,   // 11
	1,9,1,9,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1,   // 12
	1,9,1,9,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1,   // 13
	1,9,1,1,1,1,9,9,1,9,1,9,1,1,1,1,9,9,1,1,   // 14
	1,9,1,1,9,1,1,1,1,9,1,1,1,1,9,1,1,1,1,1,   // 15
	1,9,9,9,9,1,1,1,1,1,1,9,9,9,9,1,1,1,1,1,   // 16
	1,1,9,9,9,9,9,9,9,1,1,1,9,9,9,1,9,9,9,9,   // 17
	1,9,1,1,1,1,1,1,1,1,1,9,1,1,1,1,1,1,1,1,   // 18
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,   // 19

};

void prtMap()
{
	for(int i = 0; i < MAP_WIDTH; i++)
	{
		for(int j = 0; j < MAP_HEIGHT; j++)
			cout << map[i*MAP_WIDTH+j];
		cout << endl;
	}
}
void setMap()
{
	Vec2 v2;
	extern int isSolid(Vec2);

	for ( int i = 0; i < MAP_WIDTH; i++ /*= i + 0.5*/){
		for ( int j = 0; j < MAP_HEIGHT; j++/* = j + 0.5*/)
		{
			v2 = Vec2(i-20, j-20);
			if ( isSolid(v2) )
				map[i*MAP_WIDTH+j] = 1;
			else
				map[i*MAP_WIDTH+j] = 9;
		}
	}


}

static TILE start, end;
static vector<TILE> tiles;

Vec2 getStart()
{
	tiles = myfindpath (start, end, map, MAP_WIDTH, MAP_HEIGHT);

	
	//cout << "123135" << endl;
	//cout << tiles[0].i-20 << ' ' << tiles[0].j-20 << endl;

	if( !tiles.empty() && tiles.size() > 1 )
		start = tiles[1];
	else{
		printf("/////////////////////////////");
		setEnd(Vec2(17, 17));
	}
	/*else
		cout << map[end.i*MAP_WIDTH+end.j] << endl;


	cout << start.i-20 << ' ' << start.j-20 << endl;*/

	
	return Vec2(start.i-20, start.j-20);//0~40-----20~20
}
void cleartitle()
{
	tiles.clear();
}
void setEnd(Vec2 e)//standar
{
	end.i = e[0]+20;
	end.j = e[1]+20;
}

void initAstar ()
{
	start.i = 4; start.j = 5;
	end.i = 20; end.j = 20;
	tiles = myfindpath (start, end, map, MAP_WIDTH, MAP_HEIGHT);
}

int mainwin, viewer;
void displayAstar(){}
void reshape(int w, int h)
{
	glViewport (0,0,w,h);
	ViewerReshape(viewer);
}

static void showtile (int i, int j, int mode)
{
	int x = j;
	int z = i;

	glPolygonMode (GL_FRONT, mode);
	glBegin (GL_QUADS);
	glVertex3i (x,0,z);
	glVertex3i (x,0,z+1);
	glVertex3i (x+1,0,z+1);
	glVertex3i (x+1,0,z);
	glEnd();
}

void content()
{
	glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < MAP_WIDTH; i++) {
		for (int j = 0; j < MAP_HEIGHT; j++) {
			if (map[i*MAP_WIDTH+j] == 1) {
				glColor3f (1,1,1); showtile (i,j,GL_LINE);
			} else {
				glColor3f (0,0,0); showtile (i,j,GL_FILL);
			}
		}
	}
	
	glColor3f (1,0,0); showtile (start.i, start.j, GL_LINE);
	glColor3f (0,1,0); showtile (end.i, end.j, GL_LINE);

	glColor4f (1,1,0,.5);
	glEnable (GL_BLEND);
	if (tiles.size() > 0) {
		for (i = 1; i < tiles.size()-1; i++) {
			showtile (tiles[i].i, tiles[i].j, GL_FILL);
		}
	}
	glDisable (GL_BLEND);

	glutSwapBuffers();
}

#define max(x,y) ((x)>(y)? (x):(y))

void keyboardAstar (unsigned char key, int x, int y)
{
	start.i = rand() % MAP_WIDTH;
	start.j = rand() % MAP_HEIGHT;

	end.i = rand() % MAP_WIDTH;
	end.j = rand() % MAP_HEIGHT;

	tiles = myfindpath (start, end, map, MAP_WIDTH, MAP_HEIGHT);
	// if search fails, returns an empty vector
	ViewerRedisplay(viewer);
}
void specialAstar (int key, int x, int y)
{

	switch (key) {
	case GLUT_KEY_UP:
		end.i++;
		break;
	case GLUT_KEY_DOWN: 
		end.i--;
		break;
	case GLUT_KEY_RIGHT:
		end.j++;
		break;
	case GLUT_KEY_LEFT:
		end.j--;
		break;
	}

	tiles = myfindpath (start, end, map, MAP_WIDTH, MAP_HEIGHT);

	glutPostRedisplay();
}
#if 0
void main (int argc, char** argv)
{
	glutInit (&argc,argv);
	glutInitWindowSize (400,400);
	glutInitDisplayMode (GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
	mainwin = glutCreateWindow ("astar");
	glutDisplayFunc(display);
	glutReshapeFunc (reshape);

	viewer = ViewerNew (mainwin, 0,0,400,400, content);
	init();

	ViewerExtent (viewer, max(MAP_WIDTH,MAP_HEIGHT));
	ViewerCenter (viewer, MAP_WIDTH/2, 0, MAP_HEIGHT/2);
	glClearColor (.4,.4,.4,0);
	//glutKeyboardFunc (keyboard);
	glutSpecialFunc (special);	
	glBlendFunc (GL_SRC_ALPHA, GL_ONE);

	glutMainLoop();
}
#endif