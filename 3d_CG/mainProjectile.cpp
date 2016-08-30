#include <Windows>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

#include <stdio>
#include <stdlib>

#include "TestOpenGL_Texture\myPrimitive.h"
#include "ParticleProgram\particle.h"
#include "ParticleProgram\wave.h"



void init();
void idle();
void display();
void keyboard(unsigned char key, int x, int y);
void special(int key, int x, int y);
void resize(int w, int h);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void setCamera();
void setLight();

int width = 400;
int height = 400;


float lightPos[] = {10.0, 15.0, 10.0, 1.0}; 
float lightPos0[] = {10.0, 15.0, 10.0, 1.0};

static float eye[] = { 0.0, 2.0, 5.0};
static float cnt[] = { 0.0, 0.0, 0.0};

int xStart, yStart;
bool flagMouse = false;

double distC = 15.0, thetaC = 20.0, phiC = 0.0;

double fovY = 30.0;
double distC0 = distC, thetaC0 = thetaC, phiC0 = phiC, fovY0 = fovY;
double pp = PI / 180.0;


bool flagLight = false;
bool flagShadow = false;

CParticle p[MAX_PARTICLE];
double curTime, lastTime;
int count = 0;
int fps = 0; //frames per sec
float accelX = 0.0;

double elapseTime = 0.0;
double waveElapseTime = 0.0;
double dt;
int num0 = 10;

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(600,600);
  glutInitWindowPosition(100,100);
  glutCreateWindow("Physics)");
  glutReshapeFunc(resize);

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutIdleFunc(idle);
  init();
  glutMainLoop();
  return 0;
}

void idle(void)
{
  glutPostRedisplay();
}

void init(void)
{

  glClearColor(0.1, 0.2, 0.3, 1.0);
  setCamera();
  setLight();
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glShadeModel(GL_SMOOTH);
    
  lastTime = timeGetTime();
  
    
  elapseTime = 0;
  count = 0;
  fps = 0;
  for(int i = 0; i < MAX_PARTICLE; i++) p[i] = CParticle();
}

void display(void)
{

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  if(cos(PI * thetaC /180.0) >= 0.0)
	  gluLookAt(eye[0], eye[1], eye[2], cnt[0], cnt[1], cnt[2], 0.0, 1.0, 0.0);
  else
	  gluLookAt(eye[0], eye[1], eye[2], cnt[0], cnt[1], cnt[2], 0.0, -1.0, 0.0);

  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

  curTime = timeGetTime();
   dt = (float)(curTime - lastTime) * 0.001;
    
 // dt = 0.033f;
  elapseTime += dt;
    
  lastTime = curTime;


  // ------------- Frame Rate ------
    
    
  fps ++;
  if(elapseTime >= 1.0)
  { 
	printf("fps = %d \n", fps);
	fps = 0;
	elapseTime = 0.0;
  }
     
      
  // -------------------------------


  //glPushMatrix();
  //glTranslated(0.0,-2.0,0.0);
  //drawFloor(10.0, 10.0, 10, 10);
  //glPushMatrix();
  //  

  // --------------- Particles -----------------

  for(int k = 0; k < num0; k++) 
    p[count+k].create();
  for(int i = 0; i < MAX_PARTICLE; i++) 
    p[i].show(flagShadow);
  for(int i = 0; i < MAX_PARTICLE; i++) 
    p[i].update(dt);
  for(int i = 0; i < MAX_PARTICLE; i++) 
    p[i].vAccel.x = accelX;

  count += num0;


  if(count >= MAX_PARTICLE) 
    count = 0;

  // -------------------------------




  // ----------------- Wave ------
    
    //waveElapseTime += dt;
    //makeWave(waveElapseTime);
    //drawWave();

  // -------------------------------

  glutSwapBuffers();
}

void resize(int w, int h)
{
  glViewport(0, 0, w, h);//
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(fovY, (double)w/(double)h, 0.1, 100.0);
  glMatrixMode(GL_MODELVIEW);
  width = w;
  height = h;
}

void setLight()
{
  float lightDiffuse0[] = {1.0f, 1.0f, 1.0f, 1.0f}; 
  float lightAmbient0[] = {1.0f, 1.0f, 1.0f, 1.0f}; 
  float lightSpecular0[] = {1.0, 1.0f, 1.0f, 1.0f}; 
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse0);
  glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient0);
  glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular0);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
}

void keyboard(unsigned char key, int x, int y)
{
  switch((unsigned char)key)
  {
  case 27://Esc
	  exit(0);
	  break;
  case 'R':
	  for(int i = 0; i <3 ;i++) lightPos[i] = lightPos0[i];
	  distC = distC0; thetaC = thetaC0; phiC = phiC0; fovY = fovY0;
	  setCamera();
	  break;
  case 'a':
  case 'A':
	  init();
	  break;
  case 'l':
	  flagLight = true;
	  break;
  default:
	  break;
  }
}

void special(int key, int x, int y)
{
  double d = 1.0;
  if(flagLight)
  {
		switch( key )
		{
		case GLUT_KEY_RIGHT:
			lightPos[0] += d;
			break;
		case GLUT_KEY_LEFT:
			lightPos[0] -= d;
			break;
		case GLUT_KEY_UP:
			if(glutGetModifiers() == 0) lightPos[1] += d;
			if(glutGetModifiers() == GLUT_ACTIVE_SHIFT) lightPos[2] -= d;
			break;
		case GLUT_KEY_DOWN:
			if(glutGetModifiers() == 0) lightPos[1] -= d;
			if(glutGetModifiers() == GLUT_ACTIVE_SHIFT) lightPos[2] += d;
			break;
		default:
			break;
		}
  }

  //accelX
  if(key == GLUT_KEY_F1) 
  {
		if(glutGetModifiers() == GLUT_ACTIVE_SHIFT) accelX -= 1.0; 
		else accelX += 1.0; 
		printf("accelX = %f \n", accelX);
  }
}


void mouse(int button, int state, int x, int y)
{
  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
	  xStart = x; yStart = y;
	  flagMouse = true;
	  if(x > width/4 && x < 3*width/4 && y > height/4 && y < 3*height/4)//dolly
	  {
		  distC -= 0.5; 
	  }
  }
  else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
  {
	  if(x > width/4 && x < 3*width/4 && y > height/4 && y < 3*height/4)//dolly
	  {
		  distC += 0.5; 
	  }
	  else if(( x < width/4 || x > 3*width/4) && (y > height/4 && y < 3*height/4))//pan
	  {
		  if(x < width/4 ) phiC -= 1.0;
		  else phiC += 1.0;
		  cnt[2] = eye[2] - distC * cos(pp * phiC) * cos(pp * thetaC);
		  cnt[0] = eye[0] - distC * sin(pp * phiC) * cos(pp * thetaC);
	  }
	  else if((x > width/4 && x < 3*width/4) && (y < height/4 || y > 3*height/4))//tilt
	  {
		  if( y < height/4)
			  thetaC += 1.0; 
		  else
			  thetaC -= 1.0;

		  cnt[2] = eye[2] - distC * cos(pp * thetaC) * cos(pp * phiC);
		  cnt[0] = eye[0] - distC * cos(pp * thetaC) * sin(pp * phiC);
		  cnt[1] = eye[1] - distC * sin(pp * thetaC);
	  }
	  else if(x < width/8 && y > 7*height/8) fovY -= 1.0;//zoom in
	  else if(x > 7*width/8 && y > 7*height/8) fovY += 1.0;//zoom out
  }
  else flagMouse = false;
  setCamera();
}

void motion(int x, int y)
{
  if(!flagMouse) return;

  if(cos(PI * thetaC /180.0) >= 0.0)
	phiC -= 0.5 * (double)(x - xStart);//tumble
  else
	phiC += 0.5 * (double)(x - xStart);//tumble

  thetaC += 0.5 * (double)(y - yStart);//crane
  setCamera();
  xStart = x;
  yStart = y;
}

void setCamera()
{
  double pp = PI / 180.0;
  eye[2] = cnt[2] + distC * cos(pp * phiC) * cos(pp * thetaC);//z
  eye[0] = cnt[0] + distC * sin(pp * phiC) * cos(pp * thetaC);//x
  eye[1] = cnt[1] + distC * sin(pp * thetaC);//y
  printf("eyeX=%f, eyeY=%f, eyeZ=%f \n", eye[0], eye[1], eye[2]);
  printf("cntX=%f, cntY=%f, cntZ=%f \n", cnt[0], cnt[1], cnt[2]);
  printf("phiC=%f, thetaC=%f, fovY=%f \n", phiC, thetaC, fovY);
  resize(width, height);
}

