
#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

#include "myPrimitive.h"  

using namespace std;


static float   camera_yaw = 0.0f;
static float   camera_pitch = -20.0f;
static float   camera_distance = 10.0f;


static int     drag_mouse_r = 0;
static int     drag_mouse_l = 0;
static int     drag_mouse_m = 0;
static int     last_mouse_x, last_mouse_y;


static int     win_width, win_height;

static float mat_ambient[6][4] = {
	{ 0.0, 0.0, 0.0, 1.0 },			        // Black Plastic
	{ 0.329412, 0.223529, 0.027451, 1.0 },	//  Brass		
	{ 0.2125,0.1275,0.054,1.0 },			  // Bronze
	{ 0.25,0.25,0.25,1.0 },					  //Chrome
	{ 0.191125,0.0735,0.0225,1.0 },			  //Copper
	{ 0.24725,0.1995,0.0745,1.0 }				  //Gold
};
static float mat_diffuse[6][4] = {
	{ 0.01, 0.01, 0.01, 1.0 },
	{ 0.780392, 0.568627, 0.113725, 1.0 },
	{ 0.714,0.4284,0.18144,1.0 },
	{ 0.4,0.4,0.4,1.0 },
	{ 0.7038,0.27048,0.0828,1.0 },
	{ 0.75164,0.60648,0.22648,1.0 }
};

static float mat_specular[6][4] = {
	{ 0.5, 0.5, 0.5, 1.0 },
	{ 0.992157, 0.941176, 0.807843, 1.0 },
	{ 0.393548,0.271906,0.166721,1.0 },
	{ 0.774597,0.774597,0.774597,1.0 },
	{ 0.256777,0.137622,0.086014,1.0 },
	{ 0.628281,0.555802,0.366065,1.0 }
};

static float mat_shininess[6][1] = {
	{ 32.0 },
	{ 27.8974 },
	{ 25.6 },
	{ 76.8 },
	{ 12.8 },
	{ 51.2 }
};



void drawObject(void) {

	//	glutSolidSphere(1.0, 10, 10);

	//---------------------------- Sphere ------------------------
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient[3]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse[3]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular[3]);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess[3]);

	glPushMatrix();
	glTranslatef(3.0, 1.0, 0.0);
	drawSphere(1.0, 30, 30);
	glPopMatrix();

	//---------------------------- Cylinder ------------------------
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient[2]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse[2]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular[2]);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess[2]);

	glPushMatrix();
	glTranslatef(0.0, 7.5, 4.0);
	glRotatef(-90.0, 1, 0, 0);
	drawCylinder(0.1, 0.1, 1.0, 20, 20);
	glPopMatrix();

	//---------------------------- Spring ------------------------
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient[5]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse[5]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular[5]);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess[5]);

	glPushMatrix();
	glTranslatef(0.0, 0.4, 4.0);
	glRotatef(-90.0, 1, 0, 0);
	drawSpring(0.1, 1.0, 6.0, 20, 20, 8);
	glPopMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient[5]);

	//---------------------------- Tea Cup ------------------------
	float x=-1.0f;
	float nx =0.2,ny = -0.2;
	float cs[][2] = {
		//{ 0.0, 0.4 },{ 0.3, 0.5 },{ 0.4, 3.5 },{ 0.5, 3.0 },{ 0.3, 0.4 },
		//{ 0.25, 0.2 },{ 0.25, 0.15 },{ 0.5, 0.1 },{ 0.5, 0.0 },{ 0.0, 0.0 }
		{(1+x)*nx,(2+x)*ny},
		{(9+x)*nx,(2+x)*ny},
		{(9+x)*nx,(7+x)*ny},
		{(7+x)*nx,(9+x)*ny},
		{(7+x)*nx,(11+x)*ny},
		{(4+x)*nx,(14+x)*ny},
		{(4+x)*nx,(27+x)*ny},
		{(5.5+x)*nx,(28+x)*ny},
		{(4+x)*nx,(29+x)*ny},
		{(4+x)*nx,(38+x)*ny},
		{(7+x)*nx,(39+x)*ny},
		{(7+x)*nx,(40+x)*ny},
		{(8+x)*nx,(42+x)*ny},
		//{(14+x)*nx,(44+x)*ny},
		{(18+x)*nx,(42.1+x)*ny},
		{(1+x)*nx,(42.1+x)*ny},


	};



	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse[5]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular[5]);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess[5]);
	glPushMatrix();
	glTranslatef(0.0,0, 4.0);
	glRotatef(90.0, 1, 0, 0);
	drawRevolution(cs, 10, 100);
	glPopMatrix();


		//---------------------------- Torus ------------------------
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient[3]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse[3]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular[3]);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess[3]);

	glPushMatrix();
	glTranslatef(8.0, 8.0, 0.0);
	glRotatef(90.0, 1, 0, 0);
	drawTorus(0.2, 1.0, 20, 20);
	glPopMatrix();
}

void  display(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -camera_distance);
	glRotatef(-camera_pitch, 1.0, 0.0, 0.0);
	glRotatef(-camera_yaw, 0.0, 1.0, 0.0);
	glTranslatef(0.0, -0.5, 0.0);


	glPushMatrix();
	drawFloor(100, 100, 10, 10);
	glPopMatrix();

	drawObject();

	glutSwapBuffers();
}


void  reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (double)w / h, 1, 500);
	win_width = w;
	win_height = h;
}

void  mouse(int button, int state, int mx, int my)
{
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
		drag_mouse_l = 1;
	else if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP))
		drag_mouse_l = 0;
	if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN))
		drag_mouse_r = 1;
	else if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_UP))
		drag_mouse_r = 0;

	if ((button == GLUT_MIDDLE_BUTTON) && (state == GLUT_DOWN))
		drag_mouse_m = 1;
	else if ((button == GLUT_MIDDLE_BUTTON) && (state == GLUT_UP))
		drag_mouse_m = 0;

	glutPostRedisplay();

	last_mouse_x = mx;
	last_mouse_y = my;
}

void  motion(int mx, int my)
{
	if (drag_mouse_r)
	{
		camera_yaw -= (mx - last_mouse_x) * 1.0;
		if (camera_yaw < 0.0)
			camera_yaw += 360.0;
		else if (camera_yaw > 360.0)
			camera_yaw -= 360.0;

		camera_pitch -= (my - last_mouse_y) * 1.0;
		if (camera_pitch < -90.0)
			camera_pitch = -90.0;
		else if (camera_pitch > 90.0)
			camera_pitch = 90.0;
	}
	if (drag_mouse_l)
	{
		camera_distance += (my - last_mouse_y) * 0.2;
		if (camera_distance < 2.0)
			camera_distance = 2.0;
	}

	last_mouse_x = mx;
	last_mouse_y = my;

	glutPostRedisplay();
}

void  keyboard(unsigned char key, int mx, int my)
{

}

void  idle(void)
{
	glutPostRedisplay();
}

void  initEnvironment(void)
{
	float  light0_position[] = { 10.0, 10.0, 10.0, 0.0 };
	float  light0_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	float  light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	float  light0_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glEnable(GL_NORMALIZE);

	//  glShadeModel(GL_FLAT);
	glShadeModel(GL_SMOOTH);

	glClearColor(0.5, 0.5, 0.8, 0.0);
}


int  main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	glutInitWindowSize(640, 640);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("3D Primitive shapes");

	initEnvironment();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}


