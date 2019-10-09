#include <stdlib.h>
#include <gl/glew.h>
#include <gl/glut.h>
#include "gluit.h"
#include "svl/svl.h"
#include "bsp.h"
#include "gl/glpng.h"
#include <math.h>
#include <time.h>
#include "md2m.h"
#pragma comment (lib, "glew32.lib")
#pragma comment (lib, "glpngd.lib")
// (convex or concave) boundary vertices, in CCW order

Vec3 point;
float theta2, theta3;
Vec2 cameramove = Vec2(17,15);
float forward = 0.5;
int cameracheck = 1;
BspNode root;
GLuint wall;
float angle;
float _distance;
float speed = 0.0;
float check = 1;
int in = 1;
int camerain = 1;
Vec3 boundaryColor(1,1,1);
float theta = 0;
static Vec2 cmove = Vec2(17,15);

static Vec2 almove = Vec2(-17,-17);
float altheta = 0;
int alin = 1;
float alrandomtheta;
GLMmodel *al;

static Vec2 al2move = Vec2(-15,-17);
float al2theta = 0;
int al2in = 1;
float al2randomtheta;
GLMmodel *al2;

static Vec2 al3move = Vec2(-13,-17);
float al3theta = 0;
int al3in = 1;
float al3randomtheta;
GLMmodel *al3;

GLMmodel *porsche;

void patrol();

int toggle = 1;

//int viewchange = 1;

GLuint skybox;
GLuint ground;
GLuint ceiling;
GLuint anywheredoor;
GLuint exitdoor;
Vec2 doorpos = Vec2(-18.5,-19.9);
float doorposdis = 0;

extern void setEnd(Vec2);

Vec3 startpos = Vec3(0,0,5);
/////////////////////////////
GLuint g_sphereQuery;
GLuint sphereFragmentCount;
//////////////////////////////
t3DModel *yoshi;
t3DModel *mariored;
t3DModel *mariogreen;
t3DModel *marioblue;
int r = 1;
int g = 1;
int b = 1;
float scale , center[3], size[3];
float scale2 , center2[3], size2[3];
int pose , oldpose;
int loopover;
//////////////////////////////
GLuint startview;
int startnum = 0;
///////////////////////////////
float colorchange1 = 255;
float colorchange2 = 255;
float colorchange3 = 255;
////////////////////////////////normalmap
GLuint p, colortex, normaltex;
GLuint tan_loc, bitan_loc;
GLuint Pyramidcolortex,Pyramidnormaltex;
GLuint groundcolortex,groundnormaltex;

///////////////////////////////level
int level = 1;
//////////////////////////////BSP BuildTree
extern BspNode BuildTree(int);
int levelcounter = 1;
/////////////////////////////Definition function
void delaytimer ();
////////////////////////////life view
GLuint lifeimage;
GLuint HP;
int totallife = 8;
/////////////////////////////
GLuint gamepass;
GLuint gameend;
GLuint party1;
GLuint party2;
GLuint party3;
GLuint party4;

////////////////////////////
int UseProgramYN = 0;
/////////////////////////////hall
GLuint hallimage1;
/////////////////////////////blue floor
GLuint blue;

void drawstartview()
{
	glPushAttrib (GL_ALL_ATTRIB_BITS);
		glBindTexture (GL_TEXTURE_2D, startview);
		glEnable (GL_TEXTURE_2D);
		glDisable (GL_LIGHTING);

		glBegin (GL_QUADS);
		glTexCoord2f (0,0); glVertex3i (-10,0,10); 
		glTexCoord2f (1,0); glVertex3i (10,0,10);
		glTexCoord2f (1,1); glVertex3i (10,0,-10); 
		glTexCoord2f (0,1); glVertex3i (-10,0,-10);
		glEnd();
	glPopAttrib();
}

void normalmapwall2(float x ,float z, float x1, float z1)
{
	glPushAttrib (GL_ALL_ATTRIB_BITS);
		glUseProgram (p);
		glUniform1i (glGetUniformLocation (p,"NormalMap"), 0);
		glUniform1i (glGetUniformLocation (p,"ColorMap"), 1);

		glActiveTexture (GL_TEXTURE0);
		glBindTexture (GL_TEXTURE_2D, Pyramidnormaltex);
		glActiveTexture (GL_TEXTURE1);
		glBindTexture (GL_TEXTURE_2D, Pyramidcolortex);
		
		tan_loc = glGetAttribLocation (p,"Tangent");
		bitan_loc = glGetAttribLocation (p,"Bitangent");

		Vec3 a = Vec3(norm(cross(Vec3(x - x1,z -z1,0),Vec3(0,0,6))));

		glBegin (GL_QUADS);
			glVertexAttrib3f(tan_loc,1,0,0);
			glVertexAttrib3f(bitan_loc, 0,0,1);
			glNormal3f (a[0],a[1],a[2]);
			//glNormal3fv (Vec3(norm(cross(Vec3(x - x1,z -z1,0),Vec3(0,0,8)))));
			
			glMultiTexCoord2f (GL_TEXTURE0, 0,0); glVertex3i (x1,z1,0); 
			glMultiTexCoord2f (GL_TEXTURE0, 1,0); glVertex3i (x,z,0);
			glMultiTexCoord2f (GL_TEXTURE0, 1,1); glVertex3i (x,z,6);
			glMultiTexCoord2f (GL_TEXTURE0, 0,1); glVertex3i (x1,z1,6);
		glEnd();
	glPopAttrib();
}
///////////////////////////////////////////////////
void normalmapwall1(float x ,float z, float x1, float z1)
{
	glPushAttrib (GL_ALL_ATTRIB_BITS);
		glUseProgram (p);
		glUniform1i (glGetUniformLocation (p,"NormalMap"), 0);
		glUniform1i (glGetUniformLocation (p,"ColorMap"), 1);

		glActiveTexture (GL_TEXTURE0);
		glBindTexture (GL_TEXTURE_2D, normaltex);
		glActiveTexture (GL_TEXTURE1);
		glBindTexture (GL_TEXTURE_2D, colortex);
			
		tan_loc = glGetAttribLocation (p,"Tangent");
		bitan_loc = glGetAttribLocation (p,"Bitangent");

		Vec3 a = Vec3(norm(cross(Vec3(x - x1,z -z1,0),Vec3(0,0,6))));

		glBegin (GL_QUADS);
			glVertexAttrib3f(tan_loc,1,0,0);
			glVertexAttrib3f(bitan_loc, 0,0,1);
			glNormal3f (a[0],a[1],a[2]);

			glMultiTexCoord2f (GL_TEXTURE0, 0,0); glVertex3i (x1,z1,0); 
			glMultiTexCoord2f (GL_TEXTURE0, 1,0); glVertex3i (x,z,0);
			glMultiTexCoord2f (GL_TEXTURE0, 1,1); glVertex3i (x,z,6);
			glMultiTexCoord2f (GL_TEXTURE0, 0,1); glVertex3i (x1,z1,6);
		glEnd();
	glPopAttrib();
}
///////////////////////////////////////////////////////////
void grid(int a)
{	
	/*glPushAttrib (GL_ALL_ATTRIB_BITS);
		glBindTexture (GL_TEXTURE_2D, groundcolortex);
		glEnable (GL_TEXTURE_2D);
		glDisable (GL_LIGHTING);
		int i,j;
		for(j = 0;j <= 40;j = j + 4){
			for(i = 0;i <= 40;i = i + 4){
				glBegin(GL_QUADS);	
				glTexCoord2f(0, 1);glVertex3i(20-i,-20+j,0);
				glTexCoord2f(0, 0);glVertex3i(20-i,-16+j,0);
				glTexCoord2f(1, 0);glVertex3i(16-i,-16+j,0);
				glTexCoord2f(1, 1);glVertex3i(16-i,-20+j,0);	
				glEnd();
			}
		}
	glPopAttrib();*/
	if(a == 1){
		glPushAttrib (GL_ALL_ATTRIB_BITS);
			glUseProgram(0);
			glBindTexture (GL_TEXTURE_2D, blue);
			glEnable (GL_TEXTURE_2D);
			glDisable (GL_LIGHTING);
			glBegin(GL_QUADS);	
			glTexCoord2f(0, 1);glVertex3i(-20,20,0);
			glTexCoord2f(0, 0);glVertex3i(25,20,0);
			glTexCoord2f(1, 0);glVertex3i(25,-20,0);
			glTexCoord2f(1, 1);glVertex3i(-20,-20,0);	
			glEnd();
		glPopAttrib();

		glPushAttrib (GL_ALL_ATTRIB_BITS);
			glDisable (GL_TEXTURE_2D);
			glDisable (GL_LIGHTING);
			glUseProgram(0);
			glColor3f (1,0,1);
			glLineWidth (2.0);
			glBegin (GL_LINES);
			for (int i = -20; i <= 20; i=i+5) {
				glVertex3i (-20,i,0); glVertex3i (20,i,0);
				glVertex3i (i,-20,0); glVertex3i (i,20,0);
			}
			glEnd();
		glPopAttrib ();
	}
	if(a == 0){
		glPushAttrib (GL_ALL_ATTRIB_BITS);
			glUseProgram (p);
			glUniform1i (glGetUniformLocation (p,"NormalMap"), 0);
			glUniform1i (glGetUniformLocation (p,"ColorMap"), 1);

			glActiveTexture (GL_TEXTURE0);
			glBindTexture (GL_TEXTURE_2D, groundnormaltex);
			glActiveTexture (GL_TEXTURE1);
			glBindTexture (GL_TEXTURE_2D, groundcolortex);
				
			tan_loc = glGetAttribLocation (p,"Tangent");
			bitan_loc = glGetAttribLocation (p,"Bitangent");

			//Vec3 a = Vec3(norm(cross(Vec3(x - x1,z -z1,0),Vec3(0,0,6))));

			glVertexAttrib3f(tan_loc,1,0,0);
			glVertexAttrib3f(bitan_loc, 0,1,0);
			glNormal3f (0,0,1);
			glEnable (GL_TEXTURE_2D);
			glDisable (GL_LIGHTING);
			int i,j;
			for(j = 0;j <= 40;j = j + 4){
				for(i = 0;i <= 40;i = i + 4){
					glBegin(GL_QUADS);	
					glTexCoord2f(0, 1);glVertex3i(20-i,-20+j,0);
					glTexCoord2f(0, 0);glVertex3i(20-i,-16+j,0);
					glTexCoord2f(1, 0);glVertex3i(16-i,-16+j,0);
					glTexCoord2f(1, 1);glVertex3i(16-i,-20+j,0);	
					glEnd();
				}
			}
		glPopAttrib();}
}
///////////////////////////////////////////////////////////
void lifeview()
{		
	int i,j;
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();
		glDisable (GL_DEPTH_TEST);
		glEnable (GL_TEXTURE_2D);
		glBindTexture (GL_TEXTURE_2D, lifeimage);
		glEnable (GL_BLEND);
		for(j = 0; j < 3; j++)
			for(i = 0;i <= 2; i++ ){
				if(totallife >= j*3+i){
					glBegin (GL_QUADS);
						glTexCoord2f (0,0),glVertex2f (6*i+.5*i,j*-7+6.8+6.5);
						glTexCoord2f (0,1),glVertex2f (6*i+.5*i,j*-7+2*6.8+6.5);
						glTexCoord2f (1,1),glVertex2f (6+6*i+.5*i,j*-7+2*6.8+6.5);
						glTexCoord2f (1,0),glVertex2f (6+6*i+.5*i,j*-7+6.8+6.5);
					glEnd();
				}
			}
	glPopAttrib();
	glPopMatrix();
}
///////////////////////////////////////////////////////////
void hp()
{		
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();
		glDisable (GL_DEPTH_TEST);
		glEnable (GL_TEXTURE_2D);
		glBindTexture (GL_TEXTURE_2D, HP);
		glEnable (GL_BLEND);		
		glBegin (GL_QUADS);
			glTexCoord2f (0,0),glVertex2f (0,0);
			glTexCoord2f (0,1),glVertex2f (0,20);
			glTexCoord2f (1,1),glVertex2f (20,20);
			glTexCoord2f (1,0),glVertex2f (20,0);
		glEnd();
	glPopAttrib();
	glPopMatrix();
}
int imagetimechage = 0;
void marioparty()
{		
	//int r = rand()%1;
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();
		glDisable (GL_DEPTH_TEST);
		glEnable (GL_TEXTURE_2D);
		switch(imagetimechage){
		case 0:
			glBindTexture (GL_TEXTURE_2D, party1);
			break;
		case 1:
			glBindTexture (GL_TEXTURE_2D, party2);
			break;
		case 2:
			glBindTexture (GL_TEXTURE_2D, party3);
			break;
		case 3:
			glBindTexture (GL_TEXTURE_2D, party4);
			break;
		}
		glEnable (GL_BLEND);		
		glBegin (GL_QUADS);
			glTexCoord2f (0,0),glVertex2f (0,0);
			glTexCoord2f (0,1),glVertex2f (0,20);
			glTexCoord2f (1,1),glVertex2f (20,20);
			glTexCoord2f (1,0),glVertex2f (20,0);
		glEnd();
	glPopAttrib();
	glPopMatrix();
}
///////////////////////////////////////////////////////////
void gameover()
{		
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();
		glDisable (GL_DEPTH_TEST);
		glEnable (GL_TEXTURE_2D);
		glBindTexture (GL_TEXTURE_2D, gameend);
		glEnable (GL_BLEND);		
		glBegin (GL_QUADS);
			glTexCoord2f (0,0),glVertex2f (0,0);
			glTexCoord2f (0,1),glVertex2f (0,20);
			glTexCoord2f (1,1),glVertex2f (20,20);
			glTexCoord2f (1,0),glVertex2f (20,0);
		glEnd();
	glPopAttrib();
	glPopMatrix();
}
///////////////////////////////////////////////////////////
void gamepassend()
{		
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();
		glDisable (GL_DEPTH_TEST);
		glEnable (GL_TEXTURE_2D);
		glBindTexture (GL_TEXTURE_2D, gamepass);
		glEnable (GL_BLEND);		
		glBegin (GL_QUADS);
			glTexCoord2f (0,0),glVertex2f (0,0);
			glTexCoord2f (0,1),glVertex2f (0,20);
			glTexCoord2f (1,1),glVertex2f (20,20);
			glTexCoord2f (1,0),glVertex2f (20,0);
		glEnd();
	glPopAttrib();
	glPopMatrix();
}
void CeilingMaterial() 
{	
	glPushAttrib (GL_ALL_ATTRIB_BITS);
		glBindTexture (GL_TEXTURE_2D, ceiling);
		glEnable (GL_TEXTURE_2D);
		glDisable (GL_LIGHTING);	
		//glColor3ub (255,255,255);
		glNormal3f (0,0,1);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 1);glVertex3i(20,-20,6);
		glTexCoord2f(0, 0);glVertex3i(20,20,6);
		glTexCoord2f(1, 0);glVertex3i(-20,20,6);
		glTexCoord2f(1, 1);glVertex3i(-20,-20,6);		
		glEnd();
	glPopAttrib();
}
void door() 
{	
	glPushAttrib (GL_ALL_ATTRIB_BITS);
		glBindTexture (GL_TEXTURE_2D, anywheredoor);
		glEnable (GL_TEXTURE_2D);
		glDisable (GL_LIGHTING);
		glEnable (GL_ALPHA_TEST);
		glAlphaFunc (GL_GREATER, 0);
		glDisable (GL_CULL_FACE);
		glBegin(GL_QUADS);	
		glTexCoord2f(0, 1);glVertex3f(-17,-19.9,5);
		glTexCoord2f(0, 0);glVertex3f(-17,-19.9,0);
		glTexCoord2f(1, 0);glVertex3f(-20,-19.9,0);
		glTexCoord2f(1, 1);glVertex3f(-20,-19.9,5);	
		glEnd();
	glPopAttrib();
}
///////////////////////////////////////////////////////////
void passgamedoor() 
{	
	glPushAttrib (GL_ALL_ATTRIB_BITS);
		glBindTexture (GL_TEXTURE_2D, exitdoor);
		glEnable (GL_TEXTURE_2D);
		glDisable (GL_LIGHTING);
		glEnable (GL_ALPHA_TEST);
		glDisable (GL_CULL_FACE);
		glAlphaFunc (GL_GREATER, 0);
		glDisable (GL_CULL_FACE);
		glBegin(GL_QUADS);	
		glTexCoord2f(0, 1);glVertex3f(-17,-19.9,5);
		glTexCoord2f(0, 0);glVertex3f(-17,-19.9,0);
		glTexCoord2f(1, 0);glVertex3f(-20,-19.9,0);
		glTexCoord2f(1, 1);glVertex3f(-20,-19.9,5);	
		glEnd();
	glPopAttrib();
}
void axes()
{
	glPushAttrib (GL_ALL_ATTRIB_BITS);
		glDisable (GL_LIGHTING);
		glLineWidth(4.5);

		glBegin (GL_LINES);
		glColor3f(1,0,0);glVertex3i(0,0,0);glVertex3i(10,0,0);
		glColor3f(0,1,0);glVertex3i(0,0,0);glVertex3i(0,10,0);
		glColor3f(0,0,1);glVertex3i(0,0,0);glVertex3i(0,0,10);
		glEnd();
	glPopAttrib();
	
}
extern vector<LOOP> loops;

void drawBoundary(int checkwall)
{
	for (int j = 0; j < loops.size(); j++){
		glPushAttrib (GL_ALL_ATTRIB_BITS);
			glEnable (GL_DEPTH_TEST);
			glDisable (GL_LIGHTING);
			glDisable (GL_TEXTURE_2D);

			for (int i = 1; i <= loops[j].size(); i++){
				float x,x1;
				float z,z1;
				x1 = loops[j][i-1][0];
				z1 = loops[j][i-1][1];

				if(i==loops[j].size()){
					x=loops[j][i%loops[j].size()][0];
					z=loops[j][i%loops[j].size()][1];
				}
				else {
					x=loops[j][i][0];
					z=loops[j][i][1];
				}
				if (checkwall == 1){
					switch(level){
					case 1:
						glUseProgram(p);
						//normalmapwall1(x1,z1 , x, z);
						normalmapwall2(x1,z1 , x, z);
						glUseProgram(0);
						break;
					case 2:
						glUseProgram(p);//glColor3f(boundaryColor[0],boundaryColor[1],boundaryColor[2]);
						//normalmapwall2(x1,z1 , x, z);
						normalmapwall1(x1,z1 , x, z);
						glUseProgram(0);
						break;
					}
				}
				else {
					glColor3f (0,0,0);
					glLineWidth(2);
					glBegin (GL_LINES);
					glVertex3d(x1,z1,0);   glVertex3d(x,z,0);
					glEnd();
				}
			}
		glPopAttrib();
	}
}

void pose_fsm ()
{
	switch (pose) {
	case 0: // stand
		if (speed > 0) {
			pose = 1;   // stand --> run
			MD2MSetAnimation (yoshi, pose);
		}
		break;
	case 1: // run
		if (speed == 0.0) {
			pose = 0;   // run --> stand
			MD2MSetAnimation (yoshi, pose);
		}
		break;
	case 6: // jump
		if (loopover == 1) {
			pose = oldpose;   // when jump is done --> oldpose (stand or run)
			MD2MSetLoop (yoshi, GL_TRUE);
			MD2MSetAnimation (yoshi, pose);
		}
		break;
	}
}
///////////////////////////////////////////////////////////
float texi = 0;
void texturetimer(int dummy);
void halltemp()
{		
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();
		glDisable (GL_DEPTH_TEST);
		glEnable (GL_TEXTURE_2D);
		glBindTexture (GL_TEXTURE_2D, hallimage1);
		glEnable (GL_BLEND);		
		/*glBegin (GL_QUADS);
			glTexCoord2f (1/3*texi,0),glVertex2f (0,0);
			glTexCoord2f (2/3*texi,0),glVertex2f (20,0);
			glTexCoord2f (2/3*texi,1),glVertex2f (20,20);
			glTexCoord2f (1/3*texi,1),glVertex2f (0,20);
		glEnd();*/		
		glBegin (GL_QUADS);
			glTexCoord2f (0,0),glVertex2f (0,0);
			glTexCoord2f (0,1),glVertex2f (0,20);
			glTexCoord2f (1,1),glVertex2f (20,20);
			glTexCoord2f (1,0),glVertex2f (20,0);
		glEnd();
	glPopAttrib();
	glPopMatrix();glutPostRedisplay();
}
void tempview()
{		
	glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glViewport (0,0,800,600);
	glMatrixMode (GL_PROJECTION); glLoadIdentity(); gluOrtho2D (-10,10,-4,16);
	glMatrixMode (GL_MODELVIEW);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glDisable (GL_TEXTURE_2D);
	glPushMatrix();
	BEGIN_2D_OVERLAY(20,20);
	halltemp();
	END_2D_OVERLAY();
	glPopMatrix();
	glPopAttrib();

	glutSwapBuffers();
	_sleep(1000);
}
int gridchange = 0;
void display()
{
	if(levelcounter <= 2){
		if(totallife >= 0){
			if(toggle == 1 ){		
				glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

				glViewport (0,0,800,600);//star view
				glMatrixMode (GL_PROJECTION);
				glLoadIdentity();
				gluPerspective (90, 1, .5, 100);
				glMatrixMode (GL_MODELVIEW); 
				glLoadIdentity();
				gluLookAt (0, -10, 0 ,  0,0, 0,  0,0,1);

				drawstartview();

				glPushAttrib (GL_ALL_ATTRIB_BITS);
					glDisable (GL_LIGHTING);
					glDisable (GL_TEXTURE_2D);
					glColor3f (1,0,1);
					glPointSize (20);
					glBegin (GL_POINTS);//printf("startpos[0]%.2f",startpos[0]);
					glVertex3f(startpos[0]-4,startpos[1]-.01,startpos[2]);
					glEnd();
				glPopAttrib();
				//toggle = 100;
			}
			else{
				glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

				glViewport (150,0,450,200);//A star mario's view
				glMatrixMode (GL_PROJECTION);
				glLoadIdentity();
				gluPerspective (90, 1, .5, 100);
				glMatrixMode (GL_MODELVIEW); 
				glLoadIdentity();

				gluLookAt (almove[0]+0.5*sin((altheta)*3.14/180), almove[1]+0.5*cos((altheta)*3.14/180), 1.5,  almove[0]-3*sin((altheta)*3.14/180), almove[1]-3*cos((altheta)*3.14/180), 1.5 ,  0,0,1);//BeginQuery		

				drawBoundary(1);
				/*glPushAttrib (GL_ALL_ATTRIB_BITS);
				glUseProgram(p);
				grid();
				glUseProgram(0);
				glPopAttrib ();*/

				glPushAttrib(GL_ALL_ATTRIB_BITS);
				glPushMatrix();//draw andy
					glTranslatef (0, 0, 1);
					glTranslatef (cmove[0], cmove[1], 0);
					glRotatef (-theta, 0,0,1);
					glRotatef (90 , 1,0,0);	
					glRotatef (90  ,0,-1,0);
					glDisable (GL_LIGHTING);
					glScalef (2/scale, 2/scale, 2/scale);
					glBeginQuery ( GL_SAMPLES_PASSED, g_sphereQuery );
					loopover = MD2MInterpolate (yoshi);
   					glEndQuery ( GL_SAMPLES_PASSED );

					glGetQueryObjectuiv ( g_sphereQuery, GL_QUERY_RESULT, &sphereFragmentCount);
					glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
				//-----------------------------------------------------	
					glDisable (GL_TEXTURE_2D);
					//glColor3f(1,0,0);
					BEGIN_2D_OVERLAY (20,20);
					/*glBegin( GL_QUADS );
						glVertex2f( 0, .3 );
						glVertex2f( 15, .3 );
						glVertex2f( 15, 0 );
						glVertex2f( 0, 0 );
					glEnd();
					glBegin( GL_QUADS );
						glVertex2f( 0, 14.7 );
						glVertex2f( 15, 14.7 );
						glVertex2f( 15, 15.0 );
						glVertex2f( 0, 15.0 );
					glEnd();
					glBegin( GL_QUADS );
						glVertex2f( 0, 15 );
						glVertex2f( 0, 0 );
						glVertex2f( .3, 0 );
						glVertex2f( .3, 15.0 );
					glEnd();
					glBegin( GL_QUADS );
						glVertex2f( 14.7, 0 );
						glVertex2f( 14.7, 15 );
						glVertex2f( 15, 15 );
						glVertex2f( 15, 0 );
					glEnd();*/
					marioparty();
					END_2D_OVERLAY();

				glPopMatrix();
				glPopAttrib();
			
				////////////////////////////////////////////////////////////////////////////////////////////////

				glViewport (0,200,800,600);//main view
				glMatrixMode (GL_PROJECTION);
				glLoadIdentity();
				gluPerspective (90, 1, .5, 100);
				glMatrixMode (GL_MODELVIEW); 
				glLoadIdentity();
				if( !cameracheck )//cameracheck
					gluLookAt (cmove[0]+1*sin(theta*3.14/180), cmove[1]+1*cos(theta*3.14/180), 4.5 ,  cmove[0], cmove[1], 2,  0,0,1);
				else 
					gluLookAt (cmove[0]+2.5*sin(theta*3.14/180), cmove[1]+2.5*cos(theta*3.14/180), 3 ,  cmove[0]-6*sin(theta*3.14/180), cmove[1]-6*cos(theta*3.14/180), 3,  0,0,1);

				//gluLookAt (17, 17, 3 ,  cmove[0]-6*sin(theta*3.14/180), cmove[1]-6*cos(theta*3.14/180), 3,  0,0,1);
				//gluLookAt (0,0,55 ,  0,0,24,  0,-1,0);

				//glColor3d (boundaryColor[0], boundaryColor[1], boundaryColor[2]);
				

				///////////////////////////////////////////
					
				//Vec3 lightpos = Vec3 (0, 0, 6);
				//Vec3 lpos = Rot3 (Vec3 (0, 1, 0), theta) * lightpos;

				float lpos[4];
				lpos[0] = cmove[0]-sin(theta*3.14/180);
				lpos[1] = cmove[1]-cos(theta*3.14/180);
				lpos[2] = 2.5;
				lpos[3] = 1.0;

				glLightfv (GL_LIGHT0, GL_POSITION, lpos);

				float white[] = {1,1,1,1};
				glLightfv (GL_LIGHT0, GL_AMBIENT, white);

				/*glPushAttrib(GL_ALL_ATTRIB_BITS);
				glPushMatrix();//draw andy
					glDisable (GL_TEXTURE_2D);
					glDisable(GL_LIGHTING);
					glColor3ub (255,255,0); 
					glTranslatef (cmove[0]-sin(theta*3.14/180), cmove[1]-cos(theta*3.14/180),2.5);
					//glTranslatef (17, -17,2.5);
					glutWireSphere(0.1, 20, 20);
				glPopMatrix();
				glPopAttrib();*/
				//tempview();
				if(level == 1){
					door();
				}
				if(level == 2){
					passgamedoor();
				}

				CeilingMaterial();
				drawBoundary(1);
				glPushAttrib (GL_ALL_ATTRIB_BITS);
				glUseProgram(p);
				grid(gridchange);
				glUseProgram(0);
				glPopAttrib ();

				glPushAttrib(GL_ALL_ATTRIB_BITS);
				glPushMatrix();//draw yoshi
					glTranslatef (0, 0, 1);
					glTranslatef (cmove[0], cmove[1], 0);
					glRotatef (-theta, 0,0,1);
					glRotatef (90 , 1,0,0);	
					glRotatef (90  ,0,-1,0);	
					glDisable (GL_LIGHTING);
					glScalef (2/scale, 2/scale, 2/scale);
					pose_fsm ();
					loopover = MD2MInterpolate (yoshi);
				glPopMatrix();
				glPopAttrib();

				glPushAttrib(GL_ALL_ATTRIB_BITS);
				glPushMatrix();//draw mariored
					glTranslatef (0, 0, 1);
					glTranslatef (almove[0], almove[1], 0);
					glRotatef (90 , 1,0,0);
					glRotatef (270 - altheta, 0,1,0);
					glScalef (2/scale2, 2/scale2, 2/scale2);
					MD2MInterpolate (mariored);
				glPopMatrix();
				glPopAttrib();
					
				glPushAttrib(GL_ALL_ATTRIB_BITS);
				glPushMatrix();//draw mariogreen
					glTranslatef (0, 0, 1);
					glTranslatef (al2move[0], al2move[1], 0);
					glRotatef (90 , 1,0,0);
					glRotatef (270 - al2theta, 0,1,0);
					glScalef (2/scale2, 2/scale2, 2/scale2);
					MD2MInterpolate (mariogreen);
				glPopMatrix();
				glPopAttrib();
					
				glPushAttrib(GL_ALL_ATTRIB_BITS);
				glPushMatrix();//draw marioblue
					glTranslatef (0, 0, 1);
					glTranslatef (al3move[0], al3move[1], 0);
					glRotatef (90 , 1,0,0);
					glRotatef (270 - al3theta, 0,1,0);
					glScalef (2/scale2, 2/scale2, 2/scale2);
					MD2MInterpolate (marioblue);
				glPopMatrix();
				glPopAttrib();

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				glViewport (600,0,200,200);
				glMatrixMode (GL_PROJECTION);
				glLoadIdentity();
				gluPerspective (90, 1, .5, 100);
				//glOrtho (-120,120,-120,120,-20,20);
				glMatrixMode (GL_MODELVIEW); 
				glLoadIdentity();

				//gluLookAt (cmove[0],cmove[1],25 ,  cmove[0],cmove[1],24,  sin(theta*3.14/180),-cos(theta*3.14/180),0);
			
				gluLookAt (0,0,30 ,  0,0,29,  0,-1,0);
				
				/*glViewport (600,0,200,200);
				glMatrixMode (GL_PROJECTION);
				glLoadIdentity();
				glOrtho (-30,30,-30,30,-20,20);
				glRotatef (90 , 0,0,1);*/

				//glColor3d (boundaryColor[0], boundaryColor[1], boundaryColor[2]);	
				
				//if(level == 1){}
				drawBoundary(2);		

				glDisable(GL_LIGHTING);		
					
				glPushAttrib(GL_ALL_ATTRIB_BITS);
				glPushMatrix();//draw yoshi
					glColor3ub (colorchange1,colorchange2,colorchange3);
					glPointSize (10);
					glDisable (GL_TEXTURE_2D);
					glDisable (GL_POINT_SMOOTH);
					glBegin (GL_POINTS);
					glVertex3f (cmove[0], cmove[1], 5);
					glEnd();		
				glPopMatrix();
				glPopAttrib();

				glPushAttrib(GL_ALL_ATTRIB_BITS);
				glPushMatrix();//draw mariored
					glColor3f (1,0,0);
					glPointSize (8);
					glDisable (GL_TEXTURE_2D);
					glEnable (GL_POINT_SMOOTH);
					glBegin (GL_POINTS);
					glVertex3f (almove[0], almove[1], 5);
					glEnd();
				glPopMatrix();
				glPopAttrib();

				glPushAttrib(GL_ALL_ATTRIB_BITS);
				glPushMatrix();//draw mariogreen
					glColor3f (0,1,0);
					glPointSize (8);
					glDisable (GL_TEXTURE_2D);
					glEnable (GL_POINT_SMOOTH);
					glBegin (GL_POINTS);
					glVertex3f (al2move[0], al2move[1], 5);
					glEnd();
				glPopMatrix();
				glPopAttrib();
					
				glPushAttrib(GL_ALL_ATTRIB_BITS);
				glPushMatrix();//draw marioblue
					glColor3f (0,0,1);
					glPointSize (8);
					glDisable (GL_TEXTURE_2D);
					glEnable (GL_POINT_SMOOTH);
					glBegin (GL_POINTS);
					glVertex3f (al3move[0], al3move[1], 5);
					glEnd();
				glPopMatrix();
				glPopAttrib();
			//-------------------------------------------------------	
				glPushAttrib(GL_ALL_ATTRIB_BITS);
				glPushMatrix();
					glDisable (GL_TEXTURE_2D);
					glColor3f(0,1,0);
					BEGIN_2D_OVERLAY (15,15);
					glBegin( GL_QUADS );
						glVertex2f( 0, .3 );
						glVertex2f( 15, .3 );
						glVertex2f( 15, 0 );
						glVertex2f( 0, 0 );
					glEnd();
					glBegin( GL_QUADS );
						glVertex2f( 0, 14.7 );
						glVertex2f( 15, 14.7 );
						glVertex2f( 15, 15.0 );
						glVertex2f( 0, 15.0 );
					glEnd();
					glBegin( GL_QUADS );
						glVertex2f( 0, 15 );
						glVertex2f( 0, 0 );
						glVertex2f( .3, 0 );
						glVertex2f( .3, 15.0 );
					glEnd();
					glBegin( GL_QUADS );
						glVertex2f( 14.7, 0 );
						glVertex2f( 14.7, 15 );
						glVertex2f( 15, 15 );
						glVertex2f( 15, 0 );
					glEnd();
					END_2D_OVERLAY();
				glPopMatrix();
				glPopAttrib();
				////////////////////////////////////////////////////////////////////

				/*glViewport (0,0,50,200);//draw hp texture
				glMatrixMode (GL_PROJECTION); glLoadIdentity(); gluOrtho2D (-10,10,-4,16);
				glMatrixMode (GL_MODELVIEW);
				glPushAttrib(GL_ALL_ATTRIB_BITS);
				glDisable (GL_TEXTURE_2D);
				glPushMatrix();
				BEGIN_2D_OVERLAY(20,20);
				hp();
				END_2D_OVERLAY();
				glPopMatrix();
				glPopAttrib();*/
				
				glViewport (0,0,150,200);//draw life texture
				glMatrixMode (GL_PROJECTION); glLoadIdentity(); gluOrtho2D (-10,10,-4,16);
				glMatrixMode (GL_MODELVIEW);
				glPushAttrib(GL_ALL_ATTRIB_BITS);
				glDisable (GL_TEXTURE_2D);
				glPushMatrix();
				BEGIN_2D_OVERLAY(20,20);
				lifeview();
				END_2D_OVERLAY();
				glPopMatrix();
				glPopAttrib();

			////////////////////////////////////////////doorcheck
				doorposdis = sqrt(pow(cmove[0] - doorpos[0],2) + pow(cmove[1] - doorpos[1],2));

				if(levelcounter == 1){
					if(doorposdis <= 3){
						root = BuildTree(5);
						level = 2;
						cmove = Vec2(17,17);
						almove = Vec2(-17,-17);
						al2move = Vec2(-15,-17);
						al3move = Vec2(-13,-17);
						levelcounter ++;

						/*glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
						glViewport (0,0,800,600);
						glMatrixMode (GL_PROJECTION); glLoadIdentity(); gluOrtho2D (-10,10,-4,16);
						glMatrixMode (GL_MODELVIEW);
						glPushAttrib(GL_ALL_ATTRIB_BITS);
						glDisable (GL_TEXTURE_2D);
						glPushMatrix();
						BEGIN_2D_OVERLAY(20,20);
						gamepassend();
						END_2D_OVERLAY();
						glPopMatrix();
						glPopAttrib();
						glutSwapBuffers();
						_sleep(500);
						glutSwapBuffers();*/
						tempview();
					
						extern BspNode BuildTree(int);
						root = BuildTree(5);

						extern void setMap();
						setMap();

						extern void prtMap();
						prtMap();

						setEnd(Vec2(17, 17));

						extern void initAstar ();
						initAstar ();
						extern void musicchange(int musicnum);
						musicchange(2);
						gridchange++;
					}
				}
				else{
					if(doorposdis <= 3){
						extern void musicchange(int musicnum);
						musicchange(3);		
						glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

						glViewport (0,0,800,600);
						glMatrixMode (GL_PROJECTION); glLoadIdentity(); gluOrtho2D (-10,10,-4,16);
						glMatrixMode (GL_MODELVIEW);
						glPushAttrib(GL_ALL_ATTRIB_BITS);
						glDisable (GL_TEXTURE_2D);
						glPushMatrix();
						BEGIN_2D_OVERLAY(20,20);
						gamepassend();
						END_2D_OVERLAY();
						glPopMatrix();
						glPopAttrib();
						levelcounter = 3;
					}
				}
			}
		}
		else {	
			extern void musicchange(int musicnum);
			musicchange(4);		
			glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

			glViewport (0,0,800,600);
			glMatrixMode (GL_PROJECTION); glLoadIdentity(); gluOrtho2D (-10,10,-4,16);
			glMatrixMode (GL_MODELVIEW);
			glPushAttrib(GL_ALL_ATTRIB_BITS);
			glDisable (GL_TEXTURE_2D);
			glPushMatrix();
			BEGIN_2D_OVERLAY(20,20);
			gameover();
			END_2D_OVERLAY();
			glPopMatrix();
			glPopAttrib();
		}
		glutSwapBuffers();	
	}
	else{
		extern void musicchange(int musicnum);
		musicchange(3);		
		glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		glViewport (0,0,800,600);
		glMatrixMode (GL_PROJECTION); glLoadIdentity(); gluOrtho2D (-10,10,-4,16);
		glMatrixMode (GL_MODELVIEW);
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glDisable (GL_TEXTURE_2D);
		glPushMatrix();
		BEGIN_2D_OVERLAY(20,20);
		gamepassend();
		END_2D_OVERLAY();
		glPopMatrix();
		glPopAttrib();glutSwapBuffers();
		//levelcounter ++;
	}
		//system("PAUSE");
}
//-----------------------------------------------------------------------------------------------------
float alran()//----------------------------collide wall
{
	int nowtheta = altheta;
	int r90 = 0, isIn;
	
	nowtheta = atan2(cmove[0]-almove[0], cmove[1]-almove[1]) * 180 / 3.14;
	nowtheta = (nowtheta+540)%360;
	
	
	almove[0] -= sin(nowtheta*3.14/180);
	almove[1] -= cos(nowtheta*3.14/180);
	
	extern int QueryBspTree (BspNode, const Vec2&);
	isIn = QueryBspTree (root, almove);
	
	almove[0] += sin(nowtheta*3.14/180);
	almove[1] += cos(nowtheta*3.14/180);
	

	if(!isIn){
		if ( 0 < nowtheta && nowtheta < 90 ){
			nowtheta = 0 ;
		}
		else if ( 90 < nowtheta && nowtheta < 180){
			nowtheta = 90 ;
		}
		else if ( 180 < nowtheta && nowtheta < 270){
			nowtheta = 180 ;
		}
		else if( 270 < nowtheta && nowtheta < 360){
			nowtheta = 270 ;
		}
		
		almove[0] -= sin(nowtheta*3.14/180);
		almove[1] -= cos(nowtheta*3.14/180);
		
		r90 = QueryBspTree (root, almove);
		
		almove[0] += sin(nowtheta*3.14/180);
		almove[1] += cos(nowtheta*3.14/180);
		
		if(!r90)
			nowtheta = (nowtheta+90)%360;//avoid into wall with 90

		if(abs(nowtheta - altheta) == 180)//avoid turn left and turn right
			nowtheta = altheta;
	}
	return nowtheta;
}

void altimer (int dummy)
{
	Vec2 oldmove = almove;
	extern Vec2 getStart();
	almove = getStart();

	//if ( sphereFragmentCount > 0){
		altheta = alran();	
		boundaryColor = Vec3(1,0,0);
		setEnd(Vec2(cmove[0], cmove[1]));//setAndy
		if ( pow(almove[0] - cmove[0], 2) + pow(almove[1] - cmove[1], 2) < 4 /*&& totallife >= 0*/){
			almove = oldmove;
			MD2MSetAnimation (mariored, 0);
			extern void musicchange(int musicnum);
			musicchange(5);	
			_sleep(50);
			musicchange(6);	
			if(cmove == Vec2(17,15))
				cmove = Vec2(0,0);
			else
				cmove = Vec2(17,15);
			totallife--;			
		}
		else{
			MD2MSetAnimation (mariored, 1);
			//boundaryColor = Vec3(1,1,1);
		}
		//printf("---------------------------------------------------------- %d",sphereFragmentCount);
	//}
	/*else if ( sphereFragmentCount == 0 ){
		boundaryColor = Vec3(1,1,1);
		patrol();
		//printf("toggle %d",toggle);
	}*/
	glutTimerFunc (500, altimer, 0);
	glutPostRedisplay();

}
//-----------------------------------------------------------------------------------------------------
float al2ran()
{
	int nowtheta = al2theta;
	int r90 = 0 ;//,isIn;
	if( nowtheta % 90 == 0 ){
		nowtheta = (nowtheta + rand() % 181) % 360;
		return nowtheta;
	}
	else
	{		
		/*almove[0] -= sin(nowtheta*3.14/180);
		almove[1] -= cos(nowtheta*3.14/180);
		
		extern int QueryBspTree (BspNode, const Vec2&);
		isIn = QueryBspTree (root, almove);
		
		almove[0] += sin(nowtheta*3.14/180);
		almove[1] += cos(nowtheta*3.14/180);*/

		if ( 0 < nowtheta && nowtheta < 90){
			nowtheta = 0 ;
			/*for(int now = nowtheta; now < 90; now = now + 5){
				almove[0] -= sin(now*3.14/180);
				almove[1] -= cos(now*3.14/180);
		
				r90 = QueryBspTree (root, almove);
				if(r90 <= 0){
					almove[0] += sin(nowtheta*3.14/180);
					almove[1] += cos(nowtheta*3.14/180);
				}else
					nowtheta = now;
			}*/
		}
		else if ( 90 < nowtheta && nowtheta < 180){
			nowtheta = 90 ;
			/*for(int now = nowtheta; now < 180; now = now + 5){
				almove[0] -= sin(now*3.14/180);
				almove[1] -= cos(now*3.14/180);
		
				r90 = QueryBspTree (root, almove);
				if(r90 <= 0){
					almove[0] += sin(nowtheta*3.14/180);
					almove[1] += cos(nowtheta*3.14/180);
				}else
					nowtheta = now;
			}*/
		}
		else if ( 180 < nowtheta && nowtheta < 270){
			nowtheta = 180 ;
			/*for(int now = nowtheta; now < 270; now = now + 5){
				almove[0] -= sin(now*3.14/180);
				almove[1] -= cos(now*3.14/180);
		
				r90 = QueryBspTree (root, almove);
				if(r90 <= 0){
					almove[0] += sin(nowtheta*3.14/180);
					almove[1] += cos(nowtheta*3.14/180);
				}else
					nowtheta = now;
			}*/
		}
		else if( 270 < nowtheta && nowtheta < 360){
			nowtheta = 270 ;
			/*for(int now = nowtheta; now < 360; now = now + 5){
				almove[0] -= sin(now*3.14/180);
				almove[1] -= cos(now*3.14/180);
		
				r90 = QueryBspTree (root, almove);
				if(r90 <= 0){
					almove[0] += sin(nowtheta*3.14/180);
					almove[1] += cos(nowtheta*3.14/180);
				}else
					nowtheta = now;
			}*/
		}
		
		al2move[0] -= sin(nowtheta*3.14/180)*2;
		al2move[1] -= cos(nowtheta*3.14/180)*2;
		
		extern int QueryBspTreeMario (BspNode, const Vec2&);
		r90 = QueryBspTreeMario (root, al2move);
		
		al2move[0] += sin(nowtheta*3.14/180)*2;
		al2move[1] += cos(nowtheta*3.14/180)*2;
		
		if(!r90)
			nowtheta = (nowtheta+90)%360;
	}
	
	return nowtheta;
}
void al2timer (int dummy)
{
	Vec2 oldmove = al2move;

	al2move[0] -= sin(al2theta*3.14/180);
	al2move[1] -= cos(al2theta*3.14/180);

	extern int QueryBspTreeMario (BspNode, const Vec2&);
	al2in = QueryBspTreeMario (root, al2move);
	if (! al2in) {
		al2move = oldmove;		
		al2theta = al2ran();		
	} 
	else {
		boundaryColor = Vec3(1,1,1);
		if ( pow(al2move[0] - cmove[0], 2) + pow(al2move[1] - cmove[1], 2) < 4 /*&& totallife >= 0*/){
			al2move = oldmove;
			MD2MSetAnimation (mariogreen, 0);
			extern void musicchange(int musicnum);
			musicchange(5);	
			_sleep(50);
			musicchange(6);	
			if(cmove == Vec2(17,15))
				cmove = Vec2(0,0);
			else
				cmove = Vec2(17,15);
			totallife--;
		}
		else
			MD2MSetAnimation (mariogreen, 1);		
	}
	glutTimerFunc (500, al2timer, 0);
	glutPostRedisplay();
}
//-----------------------------------------------------------------------------------------------------
float al3ran()
{
	int nowtheta = al3theta;
	int r90 = 0, isIn;
	
	nowtheta = atan2(cmove[0]-al3move[0], cmove[1]-al3move[1]) * 180 / 3.14;
	//cout << nowtheta << endl;
	nowtheta = (nowtheta+540)%360;
	//return nowtheta;
	
	
	al3move[0] -= sin(nowtheta*3.14/180);
	al3move[1] -= cos(nowtheta*3.14/180);
	
	extern int QueryBspTreeMario (BspNode, const Vec2&);
	isIn = QueryBspTreeMario (root, al3move);
	
	al3move[0] += sin(nowtheta*3.14/180);
	al3move[1] += cos(nowtheta*3.14/180);	

	if(!isIn){
		if ( 0 < nowtheta && nowtheta < 90 ){
			nowtheta = 0 ;
		}
		else if ( 90 < nowtheta && nowtheta < 180){
			nowtheta = 90 ;
		}
		else if ( 180 < nowtheta && nowtheta < 270){
			nowtheta = 180 ;
		}
		else if( 270 < nowtheta && nowtheta < 360){
			nowtheta = 270 ;
		}
		
		al3move[0] -= sin(nowtheta*3.14/180);
		al3move[1] -= cos(nowtheta*3.14/180);
		
		r90 = QueryBspTreeMario (root, al3move);
		
		al3move[0] += sin(nowtheta*3.14/180);
		al3move[1] += cos(nowtheta*3.14/180);
		
		if(!r90)
			nowtheta = (nowtheta+90)%360;//avoid into wall with 90

		if(abs(nowtheta - al3theta) == 180)//avoid turn left and turn right
			nowtheta = al3theta;
	}
	return nowtheta;
}
void al3timer (int dummy)
{
	Vec2 oldmove = al3move;
	
	al3theta = al3ran();

	al3move[0] -= sin(al3theta*3.14/180);
	al3move[1] -= cos(al3theta*3.14/180);

	extern int QueryBspTreeMario (BspNode, const Vec2&);
	al3in = QueryBspTreeMario (root, al3move);
	if (! al3in) {
		al3move = oldmove;	
	}
	else {
		boundaryColor = Vec3(1,1,1);
		if ( pow(al3move[0] - cmove[0], 2) + pow(al3move[1] - cmove[1], 2) < 4 /*&& totallife >= 0*/){
			al3move = oldmove;
			MD2MSetAnimation (marioblue, 0);
			extern void musicchange(int musicnum);
			musicchange(5);	
			_sleep(50);
			musicchange(6);	
			if(cmove == Vec2(17,15))
				cmove = Vec2(0,0);
			else
				cmove = Vec2(17,15);
			totallife--;
		}
		else
			MD2MSetAnimation (marioblue, 1);
	}
	glutTimerFunc (500, al3timer, 0);
	glutPostRedisplay();
}
//-----------------------------------------------------------------------------------------------------
float randomtheta;
float ran()//-----------------------------------------------Andy
{
	int nowtheta = theta;
	int r90 = 0;
	if( nowtheta % 90 == 0 ){
		nowtheta = (nowtheta + rand() % 181 + 90) % 360;
		return nowtheta;
	}
	else
	{
		if ( 0 < nowtheta && nowtheta < 90){
			nowtheta = 0 ;
		}
		else if ( 90 < nowtheta && nowtheta < 180){
			nowtheta = 90 ;
		}
		else if ( 180 < nowtheta && nowtheta < 270){
			nowtheta = 180 ;
		}
		else if( 270 < nowtheta && nowtheta < 360){
			nowtheta = 270 ;
		}
		
		cmove[0] -= sin(nowtheta*3.14/180)*2;
		cmove[1] -= cos(nowtheta*3.14/180)*2;
		
		extern int QueryBspTree (BspNode, const Vec2&);
		r90 = QueryBspTree (root, cmove);
		
		cmove[0] += sin(nowtheta*3.14/180)*2;
		cmove[1] += cos(nowtheta*3.14/180)*2;
		
		if(!r90)
			nowtheta = (nowtheta+90)%360;
	}
	
	return nowtheta;
}

void colortimer (int dummy)
{
	float a;
	float b;
	float c;
	a = pow(almove[0] - cmove[0], 2) + pow(almove[1] - cmove[1], 2);
	b = pow(al2move[0] - cmove[0], 2) + pow(al2move[1] - cmove[1], 2);
	c = pow(al3move[0] - cmove[0], 2) + pow(al3move[1] - cmove[1], 2);
	if( a < 10 || b < 10 || c < 10 ){
		colorchange1 = (255/50)*(10*(5-a));
		colorchange2 = (255/50)*(10*(5-b));
		colorchange3 = (255/50)*(10*(5-c));
	}
	else{
		//if(colorchange1 == 0 && colorchange2 == 0 && colorchange3 == 0){
			colorchange1 = 0;
			colorchange2 = 0;
			colorchange3 = 0;
		//}
		/*if(colorchange1 == 255 && colorchange2 == 255 && colorchange3 == 255){
			colorchange1 = 0;
			colorchange2 = 0;
			colorchange3 = 0;
		}*/
	}	
	glutTimerFunc (10, colortimer, 0);
}

void timer (int dummy)
{
	speed -= 1;
	if(speed < 0)
		speed = 0;

	extern int QueryBspTreeforCamera (BspNode, const Vec2&);
	camerain = QueryBspTreeforCamera (root, cameramove);
	if (! camerain) {
		cameracheck = 0;
	} else {
		cameracheck = 1;
	}
	
	glutTimerFunc (100, timer, 0);
}
void texturetimer (int dummy)
{
	if(texi == 3)
		texi = 0;
	else
		texi = texi + 1;glutPostRedisplay();
	glutTimerFunc (150, texturetimer, 0);
}
void partyimage (int dummy)
{
	int oldrand;
	oldrand = imagetimechage;
	imagetimechage = rand()%4;

	while(imagetimechage == oldrand)
		imagetimechage = rand()%4;

	glutPostRedisplay();
	glutTimerFunc (1000, partyimage, 0);
}
int isSolid(Vec2 v2)
{
	extern int QueryBspTree (BspNode, const Vec2&);
	return QueryBspTree (root, v2);
}

void patrol()
{
	int tag = 0;

	if ( almove[0] == 17 && almove[1] == 17){
		tag = 1 ;
	}
	else if ( almove[0] == -17 && almove[1] == 17){
		tag = 2 ;
	}
	else if ( almove[0] == -17 && almove[1] == -17){
		tag = 3 ;
	}
	else if( almove[0] == 17 && almove[1] == -17){
		tag = 4 ;
	}

	switch(tag) {
	case 1:
		setEnd(Vec2(-17, 17));
		altheta = 90;
		break;
	case 2:
		setEnd(Vec2(-17, -17));
		altheta = 0;
		break;
	case 3:
		setEnd(Vec2(17, -17));
		altheta = 270;
		break;
	case 4:
		setEnd(Vec2(17, 17));
		altheta = 180;
		break;
	}
}
void special (int key, int x, int y)
{
	Vec3 oldstartpos = startpos;
		switch (key) {
		case GLUT_KEY_UP: 
			speed = 2;
			startpos[2] = startpos[2] + 5;
			//startnum = startpos[2];
			break;
		case GLUT_KEY_DOWN:  
			speed = 2;
			startpos[2] = startpos[2] - 5;
			break;		
		}
	if (toggle == 1){
		if (startpos[2] >= 6 || startpos[2] <= -1){
			  startpos[2] = oldstartpos[2]; 
		}
	}else {	
		Vec2 oldmove = cmove;
		cameramove[0] = cmove[1]+2*cos(theta*3.14/180);
		cameramove[1] = cmove[0]+2*sin(theta*3.14/180);

		switch (key) {
		case GLUT_KEY_UP: 
			cmove[0] -= sin(theta*3.14/180)/4;
			cmove[1] -= cos(theta*3.14/180)/4; 
			break;
		case GLUT_KEY_DOWN: 
			cmove[0] += sin(theta*3.14/180);
			cmove[1] += cos(theta*3.14/180);
			break;
		case GLUT_KEY_RIGHT:
			theta += 5;
			break;
		case GLUT_KEY_LEFT:
			theta -= 5;
			break;
		}
		
		extern int QueryBspTree (BspNode, const Vec2&);
		in = QueryBspTree (root, cmove);
		if (! in) {
			cmove = oldmove;
		} else {
			boundaryColor = Vec3(1,1,1);
		}
		extern int QueryBspTreeforCamera (BspNode, const Vec2&);
		camerain = QueryBspTreeforCamera (root, cameramove);
		if (! camerain) {
			cameracheck = 0;
		} else {
			cameracheck = 1;
		}
	}		
	
	glutPostRedisplay();
}
//-----------------------------------------------------------------------------------------------------
void keyboard (unsigned char key, int x, int y)
{

	/*if (key == ' '){
		toggle  *= -1;
	}*/

	switch (key) {
		case ' ': // switch
		//if(startpos[0] == 0)
			toggle  += 1;//startpos[0] = 0;
			break;
		case 'y':
			UseProgramYN ^= 1;

			glUseProgram (p);
			glUniform1i (glGetUniformLocation (p,"nobump"), UseProgramYN);
			break;
		case 'r':
			r *= -1;
			//glutTimerFunc (0, altimer, 0);	
			break;
		case 'g':
			g *= -1;
			//glutTimerFunc (0, al2timer, 0);	
			break;
		case 'b':
			b *= -1;
			//glutTimerFunc (0, al3timer, 0);
			break;

	}
	if(toggle == 1)
		setEnd(Vec2(17, 17));
	glutPostRedisplay();
}
#define max2(x,y) ((x)>(y)?(x):(y))
#define max3(x,y,z) (max2(max2(x,y),max2(y,z)))

void init_md2()
{
	// load MD2 model
	glEnable (GL_TEXTURE_2D);
	yoshi = MD2MReadMD2 ("yoshi-tris.md2", "yoshi.png");
	MD2MFindDimension  (yoshi, center, size);
	scale = max3 (size[0],size[1],size[2]);

	MD2MSetLoop (yoshi, GL_TRUE); 
	MD2MSetAnimation (yoshi, pose);  // 0: stand
	MD2MSetAnimationSpeed (yoshi, 10);

		
	mariored = MD2MReadMD2 ("tris.md2", "mario2.png");//red
	MD2MFindDimension  (mariored, center, size2);
	scale2 = max3 (size2[0],size2[1],size2[2]);

	MD2MSetLoop (mariored, GL_TRUE); 
	MD2MSetAnimation (mariored, 1);  // 0: stand
	MD2MSetAnimationSpeed (mariored, 10);
		
	mariogreen = MD2MReadMD2 ("tris.md2", "mariogreen.png");//green
	MD2MFindDimension  (mariogreen, center, size2);
	scale2 = max3 (size2[0],size2[1],size2[2]);

	MD2MSetLoop (mariogreen, GL_TRUE); 
	MD2MSetAnimation (mariogreen, 1);  // 0: stand
	MD2MSetAnimationSpeed (mariogreen, 10);	
	
	marioblue = MD2MReadMD2 ("tris.md2", "marioblue.png");//blue
	MD2MFindDimension  (marioblue, center, size2);
	scale2 = max3 (size2[0],size2[1],size2[2]);

	MD2MSetLoop (marioblue, GL_TRUE); 
	MD2MSetAnimation (marioblue, 1);  // 0: stand
	MD2MSetAnimationSpeed (marioblue, 10);
}
void init()
{

#if 1
	glEnable (GL_DEPTH_TEST);
	glClearColor (.8,.8,.8,1);
	//glClearColor3ub(130,243,253,255);
	extern void initAstar ();
	initAstar ();
	//cmove = Vec2(16,16);
	glPointSize (10);
	glEnable (GL_POINT_SMOOTH);
	glLineWidth (5.0);	

	glEnable (GL_DEPTH_TEST);
	glEnable (GL_LIGHTING);
	glEnable (GL_LIGHT0);
#endif
	pngSetStandardOrientation(0);
	pngSetStencil (255,255,255);

	//wall = pngBind("Pyramid.png", PNG_NOMIPMAP, PNG_SOLID, NULL, GL_CLAMP, GL_LINEAR, GL_LINEAR);
	//texid = pngBind("test2.png", PNG_BUILDMIPMAPS, PNG_STENCIL, NULL, GL_REPEAT, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	//aimid = pngBind("aim.png", PNG_NOMIPMAP, PNG_ALPHA, NULL, GL_CLAMP, GL_LINEAR, GL_LINEAR); 
	//ground = pngBind("magma.png", PNG_NOMIPMAP, PNG_SOLID, NULL, GL_REPEAT, GL_LINEAR, GL_LINEAR);
	startview = pngBind("startview.png", PNG_NOMIPMAP, PNG_SOLID, NULL, GL_CLAMP, GL_LINEAR, GL_LINEAR);
	ceiling = pngBind("starsky.png", PNG_NOMIPMAP, PNG_SOLID, NULL, GL_CLAMP, GL_LINEAR, GL_LINEAR);

	pngSetStandardOrientation(1);

	anywheredoor = pngBind("Door.png", PNG_NOMIPMAP, PNG_ALPHA, NULL, GL_CLAMP, GL_LINEAR, GL_LINEAR);
	lifeimage = pngBind("yoshilife.png", PNG_NOMIPMAP, PNG_SOLID, NULL, GL_CLAMP, GL_NEAREST, GL_NEAREST);
	HP = pngBind("HP2.png", PNG_NOMIPMAP, PNG_SOLID, NULL, GL_CLAMP, GL_NEAREST, GL_NEAREST);
	exitdoor = pngBind("exit2.png", PNG_NOMIPMAP, PNG_ALPHA, NULL, GL_CLAMP, GL_NEAREST, GL_NEAREST);
	gameend = pngBind("gameover.png", PNG_NOMIPMAP, PNG_SOLID, NULL, GL_CLAMP, GL_NEAREST, GL_NEAREST);
	gamepass = pngBind("thanks.png", PNG_NOMIPMAP, PNG_SOLID, NULL, GL_CLAMP, GL_NEAREST, GL_NEAREST);
	hallimage1 = pngBind("yoshipasstemp.png", PNG_NOMIPMAP, PNG_SOLID, NULL, GL_REPEAT,  GL_LINEAR, GL_LINEAR);
	blue = pngBind("yellow.png", PNG_NOMIPMAP, PNG_SOLID, NULL, GL_REPEAT,  GL_LINEAR, GL_LINEAR);
	party1 = pngBind("mario_party1.png", PNG_NOMIPMAP, PNG_SOLID, NULL, GL_CLAMP, GL_NEAREST, GL_NEAREST);
	party2 = pngBind("mario_party2.png", PNG_NOMIPMAP, PNG_SOLID, NULL, GL_CLAMP, GL_NEAREST, GL_NEAREST);
	party3 = pngBind("mario_party3.png", PNG_NOMIPMAP, PNG_SOLID, NULL, GL_CLAMP, GL_NEAREST, GL_NEAREST);
	party4 = pngBind("mario_party4.png", PNG_NOMIPMAP, PNG_SOLID, NULL, GL_CLAMP, GL_NEAREST, GL_NEAREST);

	//initkey();
	extern BspNode BuildTree(int);
	root = BuildTree(3);

	extern void setMap();
	setMap();

	extern void prtMap();
	prtMap();

	setEnd(Vec2(17, 17));
	////////////////////////////////////////
	glewInit ();
    glewGetExtension("GL_ARB_occlusion_query");//
	//glEnable (GL_DEPTH_TEST);
	glGenQueries (1, &g_sphereQuery);
	/////////////////////////////////////////// load MD2 model
	init_md2(); 
	///////////////////////////////////////////normalmap
	glewInit();
	extern GLuint setShaders(char*,char*);
	p = setShaders ("bumpmap.vert", "bumpmap.frag");
	pngSetStandardOrientation(1);
	
	Pyramidcolortex = pngBind("Pyramid2.png", PNG_NOMIPMAP, PNG_SOLID, NULL, GL_REPEAT, GL_LINEAR, GL_LINEAR);
	Pyramidnormaltex = pngBind("Pyramid2DOT3.png", PNG_NOMIPMAP, PNG_SOLID, NULL, GL_REPEAT, GL_LINEAR, GL_LINEAR);
/*rock*//*rockDOT3*/
	colortex = pngBind("brick-wallpaper-3.png", PNG_NOMIPMAP, PNG_SOLID, NULL, GL_REPEAT, GL_LINEAR, GL_LINEAR);
	normaltex = pngBind("brick-wallpaper-3DOT3.png", PNG_NOMIPMAP, PNG_SOLID, NULL, GL_REPEAT, GL_LINEAR, GL_LINEAR);
		
	groundcolortex = pngBind("ground.png", PNG_NOMIPMAP, PNG_SOLID, NULL,  GL_REPEAT, GL_LINEAR, GL_LINEAR);
	groundnormaltex = pngBind("groundDOT3.png", PNG_NOMIPMAP, PNG_SOLID, NULL, GL_REPEAT, GL_LINEAR, GL_LINEAR);	

}
void main (int argc, char** argv)
{
	glutInit (&argc,argv);
	glutInitDisplayMode (GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
	glutInitWindowSize (800,600);
	glutCreateWindow ("space into game ,y for nomalmap yes or no");	
	
	init();	
	extern void init_fmod();
	init_fmod();

	glutDisplayFunc (display);
	glutSpecialFunc (special);	
	glutKeyboardFunc (keyboard);
	
	glutTimerFunc (0, timer, 0);
	glutTimerFunc (0, altimer, 0);	
	glutTimerFunc (0, al2timer, 0);
	glutTimerFunc (0, al3timer, 0);
	glutTimerFunc (0, colortimer, 0);
	glutTimerFunc (0, texturetimer, 0);
	glutTimerFunc (0, partyimage, 0);

	glutMainLoop();
}