//
//#include <Windows.h>
//#include <GL\glew.h>
//#include <GL\freeglut.h>
//#include <iostream>
//#include <math.h>
//
//using namespace std;
//
//class cubic
//{
//	public: double mypoint[8][3];
//
//	public: void initial(float j,float m)
//	{
//		
//		double defaultData[][3] = {
//			{ 0.0,0.0,0.0 },
//			{ 1.0,0.0,0.0 },
//			{ 1.0,1.0,0.0 },
//			{ 0.0,1.0,0.0 },
//			{ 0.0,0.0,1.0 },
//			{ 1.0,0.0,1.0 },
//			{ 1.0,1.0,1.0 },
//			{ 0.0,1.0,1.0 }
//		};
//
//		for (int i = 0; i < 9; i++)
//		{
//			mypoint[i][0] = (defaultData[i][0]*0.1)+j;
//			mypoint[i][1] = (defaultData[i][1]*0.1)+m;
//			mypoint[i][2] = (defaultData[i][2]*0.1);
//		}
//	}
//
//};
//
//
//GLdouble vertex[][3] = {
//	{ 0.0,0.0,0.0 },
//	{ 1.0,0.0,0.0 },
//	{ 1.0,1.0,0.0 },
//	{ 0.0,1.0,0.0 },
//	{ 0.0,0.0,1.0 },
//	{ 1.0,0.0,1.0 },
//	{ 1.0,1.0,1.0 },
//	{ 0.0,1.0,1.0 }
//};
//
//int face[][4] = {
//	{ 0,1,2,3 },
//	{ 1,5,6,2 },
//	{ 5,4,7,6 },
//	{ 4,0,3,7 },
//	{ 4,5,1,0 },
//	{ 3,2,6,7 }
//};
//
//GLdouble color[][3] = {
//	{ 1.0,0.0,0.0 },
//	{ 0.0,1.0,0.0 },
//	{ 0.0,0.0,1.0 },
//	{ 1.0,1.0,0.0 },
//	{ 1.0,0.0,1.0 },
//	{ 0.0,1.0,1.0 }
//};
//
//GLdouble normal[][3] = {
//	{ 0.0,0.0,-1.0 },
//	{ 1.0,0.0,0.0 },
//	{ 1.0,0.0,1.0 },
//	{ -1.0,0.0,0.0 },
//	{ 0.0,-1.0,0.0 },
//	{ 0.0,1.0,0.0 }
//};
//
//int start_end[][2] = {
//	{14,14},
//	{7,15},
//	{5,14},
//	{4,13},
//	{3,14},
//	{2,13},
//	{2,13},
//	{2,14},
//	{1,15},
//	{0,15},
//	{1,14},
//	{2,13},
//	{1,14},
//	{0,14},
//	{0,15},
//	{0,15},
//	{1,14},
//	{4,13},
//	{5,13},
//	{5,12},
//	{5,11},
//	{5,11},
//	{4,11},
//	{5,11}
//};
//
//double mycolor[][3] = {
//	{0,0,0},
//	{1,1,1},
//	{134.0f/255.0f,133.0f/255.0f,250.0/255.0f},
//	{86.0f/255.0f,84.0f/255.0f,216.0f/255.0f},
//	{73.0f/255.0f,69.0f/255.0f,163.0f/255.0f},
//	{20.0f/255.0f,23.0f/255.0f,90.0f/255.0f},
//	{241.0f/255.0f,207.0f/255.0f,0},
//	{200.0f/255.0f,139.0f/255.0f,35.0f/255.0f},
//	{255.0f/255.0f,161.0f/255.0f,122.0f/255.0f},
//	{236.0f/255.0f,34.0f/255.0f,34.0f/255.0f},
//	{231.0f/255.0f,166.0f/255.0f,18.0f/255.0f},
//	{153.0f/255.0f,102.0f/255.0f,0}
//};
//
//GLfloat light0pos[] = { 0.0,-1.5,1.0,1.0 };
//GLfloat light1pos[] = { 5.0,10.0,0.0,1.0 };
//
//GLfloat green[] = { 1.0,1.0,1.0,1.0 };
//GLfloat red[] = { 0.8,0.2,0.2,1.0 };
//
//cubic mybox[24][15];
//static double r = 0;
//
//void display(void)
//{
//
//	int i, j;
//
//
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	glLoadIdentity();
//	gluLookAt(1.0, 2.0, 5, 0.0, 0.0, 0.0, 0.0, 10.0, 0.0);
//
//	glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
//	glLightfv(GL_LIGHT1, GL_POSITION, light1pos);
//
//	glRotated(270, 0.2, 0.7, 1.0);
//	
//	//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, red);
//
//	//r = r +0.001;
//	for (int k = 0; k < 24; k++)
//	{
//		for(int m = start_end[k][0] ; m <= start_end[k][1] ; m++)
//		{
//			mybox[k][m].initial((k*0.1)-1,(m*0.1)-1);
//			
//			if(k == 1 && m == 10)
//			{
//
//			}
//			else
//			{  
//				int p=1;
//				glBegin(GL_QUADS);
//				switch(k)
//				{
//					case 0: {
//								switch(m)
//								{
//									case 14: p=0;
//								}
//							} break;
//					case 1: {
//								switch(m)
//								{
//									case 7:case 8:case 9: case 11: case 12: case 13: case 15: p=0; break;
//									case 14: p=2; break;
//								}
//							}break;
//					case 2: {
//								switch(m)
//								{
//									case 5:case 6:case 14: p=0;break;
//									case 7:case 11: p=3;break;
//									case 8:case 9: p=4;break;
//									case 10: p=5; break;
//									case 12:case 13: p=2;break;
//								}break;
//							}break;
//					case 3: {
//								switch(m)
//								{
//									case 4: case 13: p=0;break;
//									case 5: case 6: p=2;break;
//									case 7: case 8: case 12: p=3;break;
//									case 9: case 10: p=4; break;
//									case 11: p=5; break;
//								}
//							}break;
//					case 4:{
//								switch(m)
//								{
//									case 3:case 14: p=0;break;
//									case 4:case 6:case 13: p=2;break;
//									case 5: p=1;break;
//									case 7:case 8: p=3; break;
//									case 9:case 11:case 12: p=4;break;
//									case 10: p=5; break;
//								}
//						   }break;
//					case 5:{
//								switch(m)
//								{
//									case 2: case 13: p=0;break;
//									case 4: case 5: case 12: p=2;break;
//									case 3:case 6: case 7:case 8: p=3;break;
//									case 9:case 11: p=4;break;
//									case 10: p=5;break;
//								}
//						   }break;
//					case 6:{
//								switch(m)
//								{
//									case 2: case 13 : p=0;break;
//									case 3: case 4: case 5: case 12: p=3;break;
//									case 8: case 9: case 10: p=4; break;
//									case 11: p=5;break;
//									case 6: case 7: p=6;break;
//								}
//						   }break;
//					case 7:{
//								switch(m)
//								{
//									case 2: case 13: case 14: p=0;break;
//									case 3: case 4: p=3;break;
//									case 5: case 6: p=6;break;
//									case 7: case 8: case 11: p=4; break;
//									case 9: case 10 : case 12: p=5;break;
//								}
//						   }break;
//					case 8:{
//								switch(m)
//								{
//									case 1: case 2: case 12: case 15: case 13: p=0; break;
//									case 3: p=3;break;
//									case 14: p=2;break;
//									case 4: case 5: case 6: case 7: case 9: case 10: case 11: p=4;break;
//									case 8 : p=5;break;
//								}
//						   }break;
//					case 9:{
//								switch(m)
//								{
//									case 0: case 2: case 4 : case 5: case 6 : case 7: case 11: case 15: p =0; break;
//									case 1: case 12: p=2;break;
//									case 13: p = 3;break;
//									case 3: case 10: case 14: p=4;break;
//									case 8: case 9: p=7;break;
//								}
//						   }break;
//					case 10:{
//								switch(m)
//								{
//									case 1: case 3: case 4: case 9: case 10: case 11: case 14: p=0;break;
//									case 2: case 12: p=3;break;
//									case 13: p=4;break;
//									case 5: case 6: case 7: case 8: p=7;break;
//								}
//							}break;
//					case 11:{
//								switch(m)
//								{
//									case 2: case 5: case 8: case 10: case 12: case 13: p=0;break;
//									case 3: case 11: p=4;break;
//									case 4: case 9: p=5;break;
//									case 6: case 7: p=8;break;
//								}
//							}break;
//					case 12:{
//								switch(m)
//								{
//									case 1: case 2: case 3: case 5: case 6: case 7 :case 11: case 14: p=0;break;
//									case 4: case 8: case 12: p=4;break;
//									case 10: p=5;break;
//									case 9: case 13: p=3;break;
//								}
//							}break;
//					case 13:{
//								switch(m)
//								{
//									case 0: case 3: case 10: case 11: case 9: case 14: p=0;break;
//									case 1: case 2: p=8;break;
//									case 5: case 7: p=2;break;
//									case 4: case 8: p=3;break;
//									case 6: p=4;break;
//									case 12: case 13: p=5;break;
//								}
//							}break;
//					case 14:{
//								switch(m)
//								{
//									case 0: case 4: case 8: case 11: case 15: p=0;break;
//									case 1: case 2: case 9: case 10: p=8;break;
//									case 3: p=4;break;
//									case 6: p=5;break;
//									case 5: case 7: case 12: case 14: p=3;break;
//									case 13: p=2;break;
//								}
//							}break;
//					case 15:{
//								switch(m)
//								{
//									case 0: case 4: case 5: case 8: case 15: p=0; break;
//									case 1: case 2: p=7;break;
//									case 9: case 10: p=8;break;
//									case 13: case 14: p=9;break;
//									case 3: p=4;break;
//									case 6: case 7: case 12: p=5;break;
//									case 11: p=3;break;
//								}
//							}break;
//					case 16:{
//								switch(m)
//								{
//									case 1: case 2: case 3: case 4: case 8: case 14: p=0;break;
//									case 5: p=2;break;
//									case 6: case 11: case 13: p=4;break;
//									case 7: case 12: p=5;break;
//									case 9: case 10: p=7;break;
//								}
//							}break;
//					case 17:{
//								switch(m)
//								{
//									case 4: case 6: case 9: case 10: case 11: case 12: case 13: p=0;break;
//									case 5: p=3;break;
//									case 7: p=4;break;
//									case 8: p=9;break;
//								}
//							}break;
//					case 18:{
//								switch(m)
//								{
//									case 5: case 6: case 10: case 13: p=0;break;
//									case 7: p=3;break;
//									case 8: p=9;break;
//									case 9: case 11: p=4;break;
//									case 12: p=5;break;
//								}
//							}break;
//					case 19:{
//								switch(m)
//								{
//									case 5: case 12: p=0;break;
//									case 6: p=2;break;
//									case 7:case 8:case 9: p=5;break;
//									case 10: p=4;break;
//									case 11: p=5;break;
//								}
//							}break;
//
//					case 20:{
//								switch(m)
//								{
//									case 5: case 11: p=0;break;
//									case 8: p=2;break;
//									case 7: case 9: p=3;break;
//									case 10: p=4;break;
//									case 6: p=5;break;
//								}
//							}break;
//					case 21:{
//								switch(m)
//								{
//									case 5:case 11: p=0;break;
//									case 8: p=2;break;
//									case 9: p=3;break;
//									case 10: p=4;break;
//									case 6: p=10;break;
//									case 7: p=5;break;
//								}
//							}break;
//					case 22:{
//								switch(m)
//								{
//									case 4: case 11: p=0;break;
//									case 5: case 7: p=10;break;
//									case 6: p=6;break;
//									case 10: p=11;break;
//									case 8: p=5;break;
//									case 9: p=4;break;
//								}
//							}break;
//					case 23:{
//								p=0;break;
//							}break;
//				}
//				
//				for (j = 0;j < 6;j++) {
//					glColor3dv(mycolor[p]);
//					//glNormal3dv(normal[j]);
//					for (i = 0; i < 4;i++) {
//						glVertex3dv(mybox[k][m].mypoint[face[j][i]]);
//					}
//				}
//				glEnd();
//			}
//		}
//	}
//
//	glutSwapBuffers();
//
//}
//
//void init()
//{
//
//	glClearColor(0.0, 0.6, 0.6, 0.0);
//	//glEnable(GL_DEPTH_TEST);
//	//glEnable(GL_CULL_FACE);
//	//glCullFace(GL_FRONT);
//
//	//glEnable(GL_LIGHTING);
//	//glEnable(GL_LIGHT0);
//	glEnable(GL_LIGHT1);
//	glLightfv(GL_LIGHT1, GL_DIFFUSE, green);
//}
//
////void display(void)
////{
////
////	int i, j;
////	static int r = 0;
////
////	glClear(GL_COLOR_BUFFER_BIT);
////
////	glLoadIdentity();
////	gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
////	glRotated((double)r, 0.0, 1.0, 0.0);
////	glColor3d(1.0, 1.0, 1.0);
////	for (int k = 0; k < 1; k++)
////	{
////		mybox[k].initial(k);
////		glBegin(GL_QUADS);
////		for (j = 0;j < 6;j++) {
////			glNormal3dv(normal[j]);
////			for (i = 0; i < 4;i++) {
////				glVertex3dv(mybox[k].mypoint[face[j][i]]);
////			}
////		}
////		glEnd();
////	}
////
////	glutSwapBuffers();
////
////
////}
//
////void init()
////{
////
////	glClearColor(0.0, 0.0, 0.0, 0.0);
////
////}
//
//void reshape(int w, int h)
//{
//	glViewport(0, 0, w, h);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);
//
//	glMatrixMode(GL_MODELVIEW);
//
//}
//
//int main(int argc, char** argv)
//{
//
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//	glutInitWindowSize(500, 500);
//	glutInitWindowPosition(0, 0);
//	glutCreateWindow("Cecil :: FFIV");
//	glutDisplayFunc(display);
//	glutReshapeFunc(reshape);
//	init();
//	glutMainLoop();
//
//}